/*
 * Copyright (c) 2010 The DragonFly Project.  All rights reserved.
 *
 * This code is derived from software contributed to The DragonFly Project
 * by Matthew Dillon <dillon@backplane.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of The DragonFly Project nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "hammer.h"

struct recover_dict {
	struct recover_dict *next;
	struct recover_dict *parent;
	int64_t	obj_id;
	uint8_t obj_type;
	uint8_t flags;
	uint16_t pfs_id;
	int64_t	size;
	char	*name;
};

#define DICTF_MADEDIR	0x01
#define DICTF_MADEFILE	0x02
#define DICTF_PARENT	0x04	/* parent attached for real */
#define DICTF_TRAVERSED	0x80

static void recover_top(char *ptr, hammer_off_t offset);
static void recover_elm(hammer_btree_leaf_elm_t leaf);
static struct recover_dict *get_dict(int64_t obj_id, uint16_t pfs_id);
static char *recover_path(struct recover_dict *dict);
static void sanitize_string(char *str);

static const char *TargetDir;
static int CachedFd = -1;
static char *CachedPath;

/*
 * XXX There is a hidden bug here while iterating zone-2 offset as
 * shown in an example below.
 *
 * If a volume was once used as HAMMER filesystem which consists of
 * multiple volumes whose usage has reached beyond the first volume,
 * and then later re-formatted only using 1 volume, hammer recover is
 * likely to hit assertion in get_buffer() due to having access to
 * invalid volume (vol1,2,...) from old filesystem data.
 *
 * |-----vol0-----|-----vol1-----|-----vol2-----| old filesystem
 * <-----------------------> used by old filesystem
 *
 * |-----vol0-----| new filesystem
 * <-----> used by new filesystem
 *        <-------> unused, invalid data from old filesystem
 *              <-> B-Tree nodes likely to point to vol1
 */

void
hammer_cmd_recover(const char *target_dir)
{
	struct buffer_info *data_buffer;
	struct volume_info *volume;
	hammer_off_t off;
	hammer_off_t off_end;
	char *ptr;
	int i;

	TargetDir = target_dir;

	if (mkdir(TargetDir, 0777) == -1) {
		if (errno != EEXIST) {
			perror("mkdir");
			exit(1);
		}
	}

	printf("Running raw scan of HAMMER image, recovering to %s\n",
		TargetDir);

	data_buffer = NULL;
	for (i = 0; i < HAMMER_MAX_VOLUMES; i++) {
		volume = get_volume(i);
		if (volume == NULL)
			continue;
		printf("Scanning volume %d size %s\n",
			volume->vol_no, sizetostr(volume->size));
		off = HAMMER_ENCODE_RAW_BUFFER(volume->vol_no, 0);
		off_end = off + HAMMER_VOL_BUF_SIZE(volume->ondisk);

		/*
		 * It should somehow implement reverse mapping from
		 * zone-2 to zone-X, so the command doesn't just try
		 * every zone-2 offset assuming it's a B-Tree node.
		 * Since we know most big-blocks are not for zone-8,
		 * we don't want to spend extra I/O for other zones
		 * as well as possible misinterpretation of nodes.
		 */
		while (off < off_end) {
			ptr = get_buffer_data(off, &data_buffer, 0);
			if (ptr)
				recover_top(ptr, off);
			off += HAMMER_BUFSIZE;
		}
	}
	rel_buffer(data_buffer);

	if (CachedPath) {
		free(CachedPath);
		close(CachedFd);
		CachedPath = NULL;
		CachedFd = -1;
	}
}

/*
 * Top level recovery processor.  Assume the data is a B-Tree node.
 * If the CRC is good we attempt to process the node, building the
 * object space and creating the dictionary as we go.
 */
static void
recover_top(char *ptr, hammer_off_t offset)
{
	hammer_node_ondisk_t node;
	hammer_btree_elm_t elm;
	int maxcount;
	int i;
	int isnode;
	char buf[HAMMER_BTREE_LEAF_ELMS + 1];

	for (node = (void *)ptr; (char *)node < ptr + HAMMER_BUFSIZE; ++node) {
		isnode = hammer_crc_test_btree(node);
		maxcount = hammer_node_max_elements(node->type);

		if (DebugOpt) {
			for (i = 0; i < node->count && i < maxcount; ++i)
				buf[i] = hammer_elm_btype(&node->elms[i]);
			buf[i] = '\0';
			if (!isnode && DebugOpt > 1)
				printf("%016jx -\n", offset);
			if (isnode)
				printf("%016jx %c %d %s\n",
					offset, node->type, node->count, buf);
		}
		offset += sizeof(*node);

		if (isnode && node->type == HAMMER_BTREE_TYPE_LEAF) {
			for (i = 0; i < node->count && i < maxcount; ++i) {
				elm = &node->elms[i];
				if (elm->base.btype == HAMMER_BTREE_TYPE_RECORD)
					recover_elm(&elm->leaf);
			}
		}
	}
}

static void
recover_elm(hammer_btree_leaf_elm_t leaf)
{
	struct buffer_info *data_buffer = NULL;
	struct recover_dict *dict;
	struct recover_dict *dict2;
	hammer_data_ondisk_t ondisk;
	hammer_off_t data_offset;
	struct stat st;
	int chunk;
	int len;
	int zfill;
	int64_t file_offset;
	uint16_t pfs_id;
	size_t nlen;
	int fd;
	char *name;
	char *path1;
	char *path2;

	/*
	 * Ignore deleted records
	 */
	if (leaf->delete_ts)
		return;
	if ((data_offset = leaf->data_offset) != 0)
		ondisk = get_buffer_data(data_offset, &data_buffer, 0);
	else
		ondisk = NULL;
	if (ondisk == NULL)
		goto done;

	len = leaf->data_len;
	chunk = HAMMER_BUFSIZE - ((int)data_offset & HAMMER_BUFMASK);
	if (chunk > len)
		chunk = len;

	if (len < 0 || len > HAMMER_XBUFSIZE || len > chunk)
		goto done;

	pfs_id = lo_to_pfs(leaf->base.localization);

	/*
	 * Note that meaning of leaf->base.obj_id differs depending
	 * on record type.  For a direntry, leaf->base.obj_id points
	 * to its parent inode that this entry is a part of, but not
	 * its corresponding inode.
	 */
	dict = get_dict(leaf->base.obj_id, pfs_id);

	switch(leaf->base.rec_type) {
	case HAMMER_RECTYPE_INODE:
		/*
		 * We found an inode which also tells us where the file
		 * or directory is in the directory hierarchy.
		 */
		if (VerboseOpt) {
			printf("inode %016jx:%05d found\n",
				(uintmax_t)leaf->base.obj_id, pfs_id);
		}
		path1 = recover_path(dict);

		/*
		 * Attach the inode to its parent.  This isn't strictly
		 * necessary because the information is also in the
		 * directory entries, but if we do not find the directory
		 * entry this ensures that the files will still be
		 * reasonably well organized in their proper directories.
		 */
		if ((dict->flags & DICTF_PARENT) == 0 &&
		    dict->obj_id != HAMMER_OBJID_ROOT &&
		    ondisk->inode.parent_obj_id != 0) {
			dict->flags |= DICTF_PARENT;
			dict->parent = get_dict(ondisk->inode.parent_obj_id,
						pfs_id);
			if (dict->parent &&
			    (dict->parent->flags & DICTF_MADEDIR) == 0) {
				dict->parent->flags |= DICTF_MADEDIR;
				path2 = recover_path(dict->parent);
				printf("mkdir %s\n", path2);
				mkdir(path2, 0777);
				free(path2);
				path2 = NULL;
			}
		}
		if (dict->obj_type == 0)
			dict->obj_type = ondisk->inode.obj_type;
		dict->size = ondisk->inode.size;
		path2 = recover_path(dict);

		if (lstat(path1, &st) == 0) {
			if (ondisk->inode.obj_type == HAMMER_OBJTYPE_REGFILE) {
				truncate(path1, dict->size);
				/* chmod(path1, 0666); */
			}
			if (strcmp(path1, path2)) {
				printf("Rename %s -> %s\n", path1, path2);
				rename(path1, path2);
			}
		} else if (ondisk->inode.obj_type == HAMMER_OBJTYPE_REGFILE) {
			printf("mkinode (file) %s\n", path2);
			fd = open(path2, O_RDWR|O_CREAT, 0666);
			if (fd > 0)
				close(fd);
		} else if (ondisk->inode.obj_type == HAMMER_OBJTYPE_DIRECTORY) {
			printf("mkinode (dir) %s\n", path2);
			mkdir(path2, 0777);
			dict->flags |= DICTF_MADEDIR;
		}
		free(path1);
		free(path2);
		break;
	case HAMMER_RECTYPE_DATA:
		/*
		 * File record data
		 */
		if (leaf->base.obj_id == 0)
			break;
		if (VerboseOpt) {
			printf("inode %016jx:%05d data %016jx,%d\n",
				(uintmax_t)leaf->base.obj_id,
				pfs_id,
				(uintmax_t)leaf->base.key - len,
				len);
		}

		/*
		 * Update the dictionary entry
		 */
		if (dict->obj_type == 0)
			dict->obj_type = HAMMER_OBJTYPE_REGFILE;

		/*
		 * If the parent directory has not been created we
		 * have to create it (typically a PFS%05d)
		 */
		if (dict->parent &&
		    (dict->parent->flags & DICTF_MADEDIR) == 0) {
			dict->parent->flags |= DICTF_MADEDIR;
			path2 = recover_path(dict->parent);
			printf("mkdir %s\n", path2);
			mkdir(path2, 0777);
			free(path2);
			path2 = NULL;
		}

		/*
		 * Create the file if necessary, report file creations
		 */
		path1 = recover_path(dict);
		if (CachedPath && strcmp(CachedPath, path1) == 0) {
			fd = CachedFd;
		} else {
			fd = open(path1, O_CREAT|O_RDWR, 0666);
		}
		if (fd < 0) {
			printf("Unable to create %s: %s\n",
				path1, strerror(errno));
			free(path1);
			break;
		}
		if ((dict->flags & DICTF_MADEFILE) == 0) {
			dict->flags |= DICTF_MADEFILE;
			printf("mkfile %s\n", path1);
		}

		/*
		 * And write the record.  A HAMMER data block is aligned
		 * and may contain trailing zeros after the file EOF.  The
		 * inode record is required to get the actual file size.
		 *
		 * However, when the inode record is not available
		 * we can do a sparse write and that will get it right
		 * most of the time even if the inode record is never
		 * found.
		 */
		file_offset = (int64_t)leaf->base.key - len;
		lseek(fd, (off_t)file_offset, SEEK_SET);
		while (len) {
			if (dict->size == -1) {
				for (zfill = chunk - 1; zfill >= 0; --zfill) {
					if (((char *)ondisk)[zfill])
						break;
				}
				++zfill;
			} else {
				zfill = chunk;
			}

			if (zfill)
				write(fd, ondisk, zfill);
			if (zfill < chunk)
				lseek(fd, chunk - zfill, SEEK_CUR);

			len -= chunk;
			data_offset += chunk;
			file_offset += chunk;
			ondisk = get_buffer_data(data_offset, &data_buffer, 0);
			if (ondisk == NULL)
				break;
			chunk = HAMMER_BUFSIZE -
				((int)data_offset & HAMMER_BUFMASK);
			if (chunk > len)
				chunk = len;
		}
		if (dict->size >= 0 && file_offset > dict->size) {
			ftruncate(fd, dict->size);
			/* fchmod(fd, 0666); */
		}

		if (fd == CachedFd) {
			free(path1);
		} else if (CachedPath) {
			free(CachedPath);
			close(CachedFd);
			CachedPath = path1;
			CachedFd = fd;
		} else {
			CachedPath = path1;
			CachedFd = fd;
		}
		break;
	case HAMMER_RECTYPE_DIRENTRY:
		nlen = len - HAMMER_ENTRY_NAME_OFF;
		if ((int)nlen < 0)	/* illegal length */
			break;
		if (ondisk->entry.obj_id == 0 ||
		    ondisk->entry.obj_id == HAMMER_OBJID_ROOT)
			break;
		name = malloc(nlen + 1);
		bcopy(ondisk->entry.name, name, nlen);
		name[nlen] = 0;
		sanitize_string(name);

		if (VerboseOpt) {
			printf("dir %016jx:%05d entry %016jx \"%s\"\n",
				(uintmax_t)leaf->base.obj_id,
				pfs_id,
				(uintmax_t)ondisk->entry.obj_id,
				name);
		}

		/*
		 * We can't deal with hardlinks so if the object already
		 * has a name assigned to it we just keep using that name.
		 */
		dict2 = get_dict(ondisk->entry.obj_id, pfs_id);
		path1 = recover_path(dict2);

		if (dict2->name == NULL)
			dict2->name = name;
		else
			free(name);

		/*
		 * Attach dict2 to its directory (dict), create the
		 * directory (dict) if necessary.  We must ensure
		 * that the directory entry exists in order to be
		 * able to properly rename() the file without creating
		 * a namespace conflict.
		 */
		if ((dict2->flags & DICTF_PARENT) == 0) {
			dict2->flags |= DICTF_PARENT;
			dict2->parent = dict;
			if ((dict->flags & DICTF_MADEDIR) == 0) {
				dict->flags |= DICTF_MADEDIR;
				path2 = recover_path(dict);
				printf("mkdir %s\n", path2);
				mkdir(path2, 0777);
				free(path2);
				path2 = NULL;
			}
		}
		path2 = recover_path(dict2);
		if (strcmp(path1, path2) != 0 && lstat(path1, &st) == 0) {
			printf("Rename %s -> %s\n", path1, path2);
			rename(path1, path2);
		}
		free(path1);
		free(path2);
		break;
	default:
		/*
		 * Ignore any other record types
		 */
		break;
	}
done:
	rel_buffer(data_buffer);
}

#define RD_HSIZE	32768
#define RD_HMASK	(RD_HSIZE - 1)

struct recover_dict *RDHash[RD_HSIZE];

static
struct recover_dict *
get_dict(int64_t obj_id, uint16_t pfs_id)
{
	struct recover_dict *dict;
	int i;

	if (obj_id == 0)
		return(NULL);

	i = crc32(&obj_id, sizeof(obj_id)) & RD_HMASK;
	for (dict = RDHash[i]; dict; dict = dict->next) {
		if (dict->obj_id == obj_id &&
		    dict->pfs_id == pfs_id) {
			break;
		}
	}
	if (dict == NULL) {
		dict = malloc(sizeof(*dict));
		bzero(dict, sizeof(*dict));
		dict->obj_id = obj_id;
		dict->pfs_id = pfs_id;
		dict->next = RDHash[i];
		dict->size = -1;
		RDHash[i] = dict;

		/*
		 * Always connect dangling dictionary entries to object 1
		 * (the root of the PFS).
		 *
		 * DICTF_PARENT will not be set until we know what the
		 * real parent directory object is.
		 */
		if (dict->obj_id != HAMMER_OBJID_ROOT)
			dict->parent = get_dict(HAMMER_OBJID_ROOT, pfs_id);
	}
	return(dict);
}

struct path_info {
	enum { PI_FIGURE, PI_LOAD } state;
	uint16_t pfs_id;
	char *base;
	char *next;
	int len;
};

static void recover_path_helper(struct recover_dict *, struct path_info *);

static
char *
recover_path(struct recover_dict *dict)
{
	struct path_info info;

	/* Find info.len first */
	bzero(&info, sizeof(info));
	info.state = PI_FIGURE;
	recover_path_helper(dict, &info);

	/* Fill in the path */
	info.pfs_id = dict->pfs_id;
	info.base = malloc(info.len);
	info.next = info.base;
	info.state = PI_LOAD;
	recover_path_helper(dict, &info);

	/* Return the path */
	return(info.base);
}

#define STRLEN_OBJID	22	/* "obj_0x%016jx" */
#define STRLEN_PFSID	8	/* "PFS%05d" */

static
void
recover_path_helper(struct recover_dict *dict, struct path_info *info)
{
	/*
	 * Calculate path element length
	 */
	dict->flags |= DICTF_TRAVERSED;

	switch(info->state) {
	case PI_FIGURE:
		if (dict->obj_id == HAMMER_OBJID_ROOT)
			info->len += STRLEN_PFSID;
		else if (dict->name)
			info->len += strlen(dict->name);
		else
			info->len += STRLEN_OBJID;
		++info->len;

		if (dict->parent &&
		    (dict->parent->flags & DICTF_TRAVERSED) == 0) {
			recover_path_helper(dict->parent, info);
		} else {
			info->len += strlen(TargetDir) + 1;
		}
		break;
	case PI_LOAD:
		if (dict->parent &&
		    (dict->parent->flags & DICTF_TRAVERSED) == 0) {
			recover_path_helper(dict->parent, info);
		} else {
			strcpy(info->next, TargetDir);
			info->next += strlen(info->next);
		}

		*info->next++ = '/';
		if (dict->obj_id == HAMMER_OBJID_ROOT) {
			snprintf(info->next, STRLEN_PFSID + 1,
				"PFS%05d", info->pfs_id);
		} else if (dict->name) {
			strcpy(info->next, dict->name);
		} else {
			snprintf(info->next, STRLEN_OBJID + 1,
				"obj_0x%016jx", (uintmax_t)dict->obj_id);
		}
		info->next += strlen(info->next);
		break;
	}
	dict->flags &= ~DICTF_TRAVERSED;
}

static
void
sanitize_string(char *str)
{
	while (*str) {
		if (!isprint(*str))
			*str = 'x';
		++str;
	}
}
