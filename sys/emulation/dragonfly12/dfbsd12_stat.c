/*-
 * Copyright (c) 2005 The DragonFly Project.  All rights reserved.
 * 
 * This code is derived from software contributed to The DragonFly Project
 * by Joerg Sonnenberger <joerg@bec.de>.
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
 *
 * $DragonFly: src/sys/emulation/dragonfly12/dfbsd12_stat.c,v 1.1 2005/08/02 13:03:54 joerg Exp $
 */

#include "opt_compatdf12.h"

#include <sys/param.h>
#include <sys/kern_syscall.h>
#include <sys/mount.h>
#include <sys/nlookup.h>
#include <sys/proc.h>
#include <sys/stat.h>
#include <sys/sysproto.h>
#include <sys/systm.h>
#include <sys/thread.h>
#include <sys/vnode.h>
#include <emulation/dragonfly12/stat.h>

static void
cvtstat(struct dfbsd12_stat *oldstat, struct stat *newstat)
{
	bzero(oldstat, sizeof(oldstat));

	oldstat->st_dev = newstat->st_dev;
	oldstat->st_ino = newstat->st_ino;	/* truncation */
	oldstat->st_mode = newstat->st_mode;
	oldstat->st_nlink = newstat->st_nlink;	/* truncation */
	oldstat->st_uid = newstat->st_uid;
	oldstat->st_gid = newstat->st_gid;
	oldstat->st_rdev = newstat->st_rdev;
	oldstat->st_atimespec = newstat->st_atimespec;
	oldstat->st_mtimespec = newstat->st_mtimespec;
	oldstat->st_ctimespec = newstat->st_ctimespec;
	oldstat->st_size = newstat->st_size;
	oldstat->st_blocks = newstat->st_blocks;
	oldstat->st_blksize = newstat->st_blksize;
	oldstat->st_flags = newstat->st_flags;
	oldstat->st_gen = newstat->st_gen;
}

/*
 * stat_args(char *path, struct dfbsd12_stat *ub)
 *
 * Get file status; this version follows links.
 */
int
dfbsd12_stat(struct dfbsd12_stat_args *uap)
{
	struct nlookupdata nd;
	struct dfbsd12_stat ost;
	struct stat st;
	int error;

	error = nlookup_init(&nd, uap->path, UIO_USERSPACE, NLC_FOLLOW);
	if (error == 0) {
		error = kern_stat(&nd, &st);
		if (error == 0) {
			cvtstat(&ost, &st);
			error = copyout(&ost, uap->ub, sizeof(ost));
		}
	}
	nlookup_done(&nd);
	return (error);
}

/*
 * lstat_args(char *path, struct dfbsd12_stat *ub)
 *
 * Get file status; this version does not follow links.
 */
int
dfbsd12_lstat(struct dfbsd12_lstat_args *uap)
{
	struct nlookupdata nd;
	struct dfbsd12_stat ost;
	struct stat st;
	int error;

	error = nlookup_init(&nd, uap->path, UIO_USERSPACE, 0);
	if (error == 0) {
		error = kern_stat(&nd, &st);
		if (error == 0) {
			cvtstat(&ost, &st);
			error = copyout(&ost, uap->ub, sizeof(ost));
		}
	}
	nlookup_done(&nd);
	return (error);
}

/*
 * fhstat_args(struct fhandle *u_fhp, struct dfbsd12_stat *sb)
 */
int
dfbsd12_fhstat(struct dfbsd12_fhstat_args *uap)
{
	struct thread *td = curthread;
	struct dfbsd12_stat osb;
	struct stat sb;
	fhandle_t fh;
	struct mount *mp;
	struct vnode *vp;
	int error;

	/*
	 * Must be super user
	 */
	error = suser(td);
	if (error)
		return (error);
	
	error = copyin(uap->u_fhp, &fh, sizeof(fhandle_t));
	if (error)
		return (error);

	if ((mp = vfs_getvfs(&fh.fh_fsid)) == NULL)
		return (ESTALE);
	if ((error = VFS_FHTOVP(mp, &fh.fh_fid, &vp)))
		return (error);
	error = vn_stat(vp, &sb, td);
	vput(vp);
	if (error)
		return (error);
	cvtstat(&osb, &sb);
	error = copyout(&osb, uap->sb, sizeof(osb));
	return (error);
}

/*
 * dfbsd12_fstat_args(int fd, struct dfbsd12_stat *sb)
 */
int
dfbsd12_fstat(struct dfbsd12_fstat_args *uap)
{
	struct dfbsd12_stat ost;
	struct stat st;
	int error;

	error = kern_fstat(uap->fd, &st);

	if (error == 0) {
		cvtstat(&ost, &st);
		error = copyout(&ost, uap->sb, sizeof(ost));
	}
	return (error);
}
