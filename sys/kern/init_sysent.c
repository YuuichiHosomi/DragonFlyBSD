/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $DragonFly: src/sys/kern/init_sysent.c,v 1.21 2005/01/14 02:20:22 dillon Exp $
 * created from DragonFly: src/sys/kern/syscalls.master,v 1.15 2004/12/29 02:40:02 dillon Exp 
 */

#include "opt_compat.h"

#include <sys/param.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>

#define AS(name) ((sizeof(struct name) - sizeof(struct sysmsg) - sizeof(union usrmsg)) / sizeof(register_t))

#ifdef COMPAT_43
#define compat(n, name) n, (sy_call_t *)__CONCAT(o,name)
#else
#define compat(n, name) 0, (sy_call_t *)nosys
#endif

/* The casts are bogus but will do for now. */
struct sysent sysent[] = {
	{ 0, (sy_call_t *)nosys },			/* 0 = syscall */
	{ AS(sys_exit_args), (sy_call_t *)sys_exit },	/* 1 = exit */
	{ 0, (sy_call_t *)fork },			/* 2 = fork */
	{ AS(read_args), (sy_call_t *)read },		/* 3 = read */
	{ AS(write_args), (sy_call_t *)write },		/* 4 = write */
	{ AS(open_args), (sy_call_t *)open },		/* 5 = open */
	{ AS(close_args), (sy_call_t *)close },		/* 6 = close */
	{ AS(wait_args), (sy_call_t *)wait4 },		/* 7 = wait4 */
	{ compat(AS(ocreat_args),creat) },		/* 8 = old creat */
	{ AS(link_args), (sy_call_t *)link },		/* 9 = link */
	{ AS(unlink_args), (sy_call_t *)unlink },	/* 10 = unlink */
	{ 0, (sy_call_t *)nosys },			/* 11 = obsolete execv */
	{ AS(chdir_args), (sy_call_t *)chdir },		/* 12 = chdir */
	{ AS(fchdir_args), (sy_call_t *)fchdir },	/* 13 = fchdir */
	{ AS(mknod_args), (sy_call_t *)mknod },		/* 14 = mknod */
	{ AS(chmod_args), (sy_call_t *)chmod },		/* 15 = chmod */
	{ AS(chown_args), (sy_call_t *)chown },		/* 16 = chown */
	{ AS(obreak_args), (sy_call_t *)obreak },	/* 17 = break */
	{ AS(getfsstat_args), (sy_call_t *)getfsstat },	/* 18 = getfsstat */
	{ compat(AS(olseek_args),lseek) },		/* 19 = old lseek */
	{ 0, (sy_call_t *)getpid },			/* 20 = getpid */
	{ AS(mount_args), (sy_call_t *)mount },		/* 21 = mount */
	{ AS(unmount_args), (sy_call_t *)unmount },	/* 22 = unmount */
	{ AS(setuid_args), (sy_call_t *)setuid },	/* 23 = setuid */
	{ SYF_MPSAFE | 0, (sy_call_t *)getuid },	/* 24 = getuid */
	{ SYF_MPSAFE | 0, (sy_call_t *)geteuid },	/* 25 = geteuid */
	{ AS(ptrace_args), (sy_call_t *)ptrace },	/* 26 = ptrace */
	{ AS(recvmsg_args), (sy_call_t *)recvmsg },	/* 27 = recvmsg */
	{ AS(sendmsg_args), (sy_call_t *)sendmsg },	/* 28 = sendmsg */
	{ AS(recvfrom_args), (sy_call_t *)recvfrom },	/* 29 = recvfrom */
	{ AS(accept_args), (sy_call_t *)accept },	/* 30 = accept */
	{ AS(getpeername_args), (sy_call_t *)getpeername },	/* 31 = getpeername */
	{ AS(getsockname_args), (sy_call_t *)getsockname },	/* 32 = getsockname */
	{ AS(access_args), (sy_call_t *)access },	/* 33 = access */
	{ AS(chflags_args), (sy_call_t *)chflags },	/* 34 = chflags */
	{ AS(fchflags_args), (sy_call_t *)fchflags },	/* 35 = fchflags */
	{ 0, (sy_call_t *)sync },			/* 36 = sync */
	{ AS(kill_args), (sy_call_t *)kill },		/* 37 = kill */
	{ compat(AS(ostat_args),stat) },		/* 38 = old stat */
	{ 0, (sy_call_t *)getppid },			/* 39 = getppid */
	{ compat(AS(olstat_args),lstat) },		/* 40 = old lstat */
	{ AS(dup_args), (sy_call_t *)dup },		/* 41 = dup */
	{ 0, (sy_call_t *)pipe },			/* 42 = pipe */
	{ 0, (sy_call_t *)getegid },			/* 43 = getegid */
	{ AS(profil_args), (sy_call_t *)profil },	/* 44 = profil */
	{ AS(ktrace_args), (sy_call_t *)ktrace },	/* 45 = ktrace */
	{ 0, (sy_call_t *)nosys },			/* 46 = obsolete freebsd3_sigaction */
	{ SYF_MPSAFE | 0, (sy_call_t *)getgid },	/* 47 = getgid */
	{ 0, (sy_call_t *)nosys },			/* 48 = obsolete freebsd3_sigprocmask */
	{ AS(getlogin_args), (sy_call_t *)getlogin },	/* 49 = getlogin */
	{ AS(setlogin_args), (sy_call_t *)setlogin },	/* 50 = setlogin */
	{ AS(acct_args), (sy_call_t *)acct },		/* 51 = acct */
	{ 0, (sy_call_t *)nosys },			/* 52 = obsolete freebsd3_sigpending */
	{ AS(sigaltstack_args), (sy_call_t *)sigaltstack },	/* 53 = sigaltstack */
	{ AS(ioctl_args), (sy_call_t *)ioctl },		/* 54 = ioctl */
	{ AS(reboot_args), (sy_call_t *)reboot },	/* 55 = reboot */
	{ AS(revoke_args), (sy_call_t *)revoke },	/* 56 = revoke */
	{ AS(symlink_args), (sy_call_t *)symlink },	/* 57 = symlink */
	{ AS(readlink_args), (sy_call_t *)readlink },	/* 58 = readlink */
	{ AS(execve_args), (sy_call_t *)execve },	/* 59 = execve */
	{ SYF_MPSAFE | AS(umask_args), (sy_call_t *)umask },	/* 60 = umask */
	{ AS(chroot_args), (sy_call_t *)chroot },	/* 61 = chroot */
	{ compat(AS(ofstat_args),fstat) },		/* 62 = old fstat */
	{ compat(AS(getkerninfo_args),getkerninfo) },	/* 63 = old getkerninfo */
	{ compat(0,getpagesize) },			/* 64 = old getpagesize */
	{ AS(msync_args), (sy_call_t *)msync },		/* 65 = msync */
	{ 0, (sy_call_t *)vfork },			/* 66 = vfork */
	{ 0, (sy_call_t *)nosys },			/* 67 = obsolete vread */
	{ 0, (sy_call_t *)nosys },			/* 68 = obsolete vwrite */
	{ AS(sbrk_args), (sy_call_t *)sbrk },		/* 69 = sbrk */
	{ AS(sstk_args), (sy_call_t *)sstk },		/* 70 = sstk */
	{ compat(AS(ommap_args),mmap) },		/* 71 = old mmap */
	{ AS(ovadvise_args), (sy_call_t *)ovadvise },	/* 72 = vadvise */
	{ AS(munmap_args), (sy_call_t *)munmap },	/* 73 = munmap */
	{ AS(mprotect_args), (sy_call_t *)mprotect },	/* 74 = mprotect */
	{ AS(madvise_args), (sy_call_t *)madvise },	/* 75 = madvise */
	{ 0, (sy_call_t *)nosys },			/* 76 = obsolete vhangup */
	{ 0, (sy_call_t *)nosys },			/* 77 = obsolete vlimit */
	{ AS(mincore_args), (sy_call_t *)mincore },	/* 78 = mincore */
	{ AS(getgroups_args), (sy_call_t *)getgroups },	/* 79 = getgroups */
	{ AS(setgroups_args), (sy_call_t *)setgroups },	/* 80 = setgroups */
	{ SYF_MPSAFE | 0, (sy_call_t *)getpgrp },	/* 81 = getpgrp */
	{ AS(setpgid_args), (sy_call_t *)setpgid },	/* 82 = setpgid */
	{ AS(setitimer_args), (sy_call_t *)setitimer },	/* 83 = setitimer */
	{ compat(0,wait) },				/* 84 = old wait */
	{ AS(swapon_args), (sy_call_t *)swapon },	/* 85 = swapon */
	{ AS(getitimer_args), (sy_call_t *)getitimer },	/* 86 = getitimer */
	{ compat(AS(gethostname_args),gethostname) },	/* 87 = old gethostname */
	{ compat(AS(sethostname_args),sethostname) },	/* 88 = old sethostname */
	{ 0, (sy_call_t *)getdtablesize },		/* 89 = getdtablesize */
	{ AS(dup2_args), (sy_call_t *)dup2 },		/* 90 = dup2 */
	{ 0, (sy_call_t *)nosys },			/* 91 = getdopt */
	{ AS(fcntl_args), (sy_call_t *)fcntl },		/* 92 = fcntl */
	{ AS(select_args), (sy_call_t *)select },	/* 93 = select */
	{ 0, (sy_call_t *)nosys },			/* 94 = setdopt */
	{ AS(fsync_args), (sy_call_t *)fsync },		/* 95 = fsync */
	{ AS(setpriority_args), (sy_call_t *)setpriority },	/* 96 = setpriority */
	{ AS(socket_args), (sy_call_t *)socket },	/* 97 = socket */
	{ AS(connect_args), (sy_call_t *)connect },	/* 98 = connect */
	{ compat(AS(accept_args),accept) },		/* 99 = old accept */
	{ AS(getpriority_args), (sy_call_t *)getpriority },	/* 100 = getpriority */
	{ compat(AS(osend_args),send) },		/* 101 = old send */
	{ compat(AS(orecv_args),recv) },		/* 102 = old recv */
	{ 0, (sy_call_t *)nosys },			/* 103 = obsolete freebsd3_sigreturn */
	{ AS(bind_args), (sy_call_t *)bind },		/* 104 = bind */
	{ AS(setsockopt_args), (sy_call_t *)setsockopt },	/* 105 = setsockopt */
	{ AS(listen_args), (sy_call_t *)listen },	/* 106 = listen */
	{ 0, (sy_call_t *)nosys },			/* 107 = obsolete vtimes */
	{ compat(AS(osigvec_args),sigvec) },		/* 108 = old sigvec */
	{ compat(AS(osigblock_args),sigblock) },	/* 109 = old sigblock */
	{ compat(AS(osigsetmask_args),sigsetmask) },	/* 110 = old sigsetmask */
	{ 0, (sy_call_t *)nosys },			/* 111 = obsolete freebsd3_sigsuspend */
	{ compat(AS(osigstack_args),sigstack) },	/* 112 = old sigstack */
	{ compat(AS(orecvmsg_args),recvmsg) },		/* 113 = old recvmsg */
	{ compat(AS(osendmsg_args),sendmsg) },		/* 114 = old sendmsg */
	{ 0, (sy_call_t *)nosys },			/* 115 = obsolete vtrace */
	{ SYF_MPSAFE | AS(gettimeofday_args), (sy_call_t *)gettimeofday },	/* 116 = gettimeofday */
	{ AS(getrusage_args), (sy_call_t *)getrusage },	/* 117 = getrusage */
	{ AS(getsockopt_args), (sy_call_t *)getsockopt },	/* 118 = getsockopt */
	{ 0, (sy_call_t *)nosys },			/* 119 = resuba */
	{ AS(readv_args), (sy_call_t *)readv },		/* 120 = readv */
	{ AS(writev_args), (sy_call_t *)writev },	/* 121 = writev */
	{ AS(settimeofday_args), (sy_call_t *)settimeofday },	/* 122 = settimeofday */
	{ AS(fchown_args), (sy_call_t *)fchown },	/* 123 = fchown */
	{ AS(fchmod_args), (sy_call_t *)fchmod },	/* 124 = fchmod */
	{ compat(AS(recvfrom_args),recvfrom) },		/* 125 = old recvfrom */
	{ AS(setreuid_args), (sy_call_t *)setreuid },	/* 126 = setreuid */
	{ AS(setregid_args), (sy_call_t *)setregid },	/* 127 = setregid */
	{ AS(rename_args), (sy_call_t *)rename },	/* 128 = rename */
	{ compat(AS(otruncate_args),truncate) },	/* 129 = old truncate */
	{ compat(AS(oftruncate_args),ftruncate) },	/* 130 = old ftruncate */
	{ AS(flock_args), (sy_call_t *)flock },		/* 131 = flock */
	{ AS(mkfifo_args), (sy_call_t *)mkfifo },	/* 132 = mkfifo */
	{ AS(sendto_args), (sy_call_t *)sendto },	/* 133 = sendto */
	{ AS(shutdown_args), (sy_call_t *)shutdown },	/* 134 = shutdown */
	{ AS(socketpair_args), (sy_call_t *)socketpair },	/* 135 = socketpair */
	{ AS(mkdir_args), (sy_call_t *)mkdir },		/* 136 = mkdir */
	{ AS(rmdir_args), (sy_call_t *)rmdir },		/* 137 = rmdir */
	{ AS(utimes_args), (sy_call_t *)utimes },	/* 138 = utimes */
	{ 0, (sy_call_t *)nosys },			/* 139 = obsolete 4.2 sigreturn */
	{ AS(adjtime_args), (sy_call_t *)adjtime },	/* 140 = adjtime */
	{ compat(AS(ogetpeername_args),getpeername) },	/* 141 = old getpeername */
	{ compat(0,gethostid) },			/* 142 = old gethostid */
	{ compat(AS(osethostid_args),sethostid) },	/* 143 = old sethostid */
	{ compat(AS(ogetrlimit_args),getrlimit) },	/* 144 = old getrlimit */
	{ compat(AS(osetrlimit_args),setrlimit) },	/* 145 = old setrlimit */
	{ compat(AS(okillpg_args),killpg) },		/* 146 = old killpg */
	{ 0, (sy_call_t *)setsid },			/* 147 = setsid */
	{ AS(quotactl_args), (sy_call_t *)quotactl },	/* 148 = quotactl */
	{ compat(0,quota) },				/* 149 = old quota */
	{ compat(AS(getsockname_args),getsockname) },	/* 150 = old getsockname */
	{ 0, (sy_call_t *)nosys },			/* 151 = sem_lock */
	{ 0, (sy_call_t *)nosys },			/* 152 = sem_wakeup */
	{ 0, (sy_call_t *)nosys },			/* 153 = asyncdaemon */
	{ 0, (sy_call_t *)nosys },			/* 154 = nosys */
	{ AS(nfssvc_args), (sy_call_t *)nosys },	/* 155 = nfssvc */
	{ compat(AS(ogetdirentries_args),getdirentries) },	/* 156 = old getdirentries */
	{ AS(statfs_args), (sy_call_t *)statfs },	/* 157 = statfs */
	{ AS(fstatfs_args), (sy_call_t *)fstatfs },	/* 158 = fstatfs */
	{ 0, (sy_call_t *)nosys },			/* 159 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 160 = nosys */
	{ AS(getfh_args), (sy_call_t *)getfh },		/* 161 = getfh */
	{ AS(getdomainname_args), (sy_call_t *)getdomainname },	/* 162 = getdomainname */
	{ AS(setdomainname_args), (sy_call_t *)setdomainname },	/* 163 = setdomainname */
	{ AS(uname_args), (sy_call_t *)uname },		/* 164 = uname */
	{ AS(sysarch_args), (sy_call_t *)sysarch },	/* 165 = sysarch */
	{ AS(rtprio_args), (sy_call_t *)rtprio },	/* 166 = rtprio */
	{ 0, (sy_call_t *)nosys },			/* 167 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 168 = nosys */
	{ AS(semsys_args), (sy_call_t *)semsys },	/* 169 = semsys */
	{ AS(msgsys_args), (sy_call_t *)msgsys },	/* 170 = msgsys */
	{ AS(shmsys_args), (sy_call_t *)shmsys },	/* 171 = shmsys */
	{ 0, (sy_call_t *)nosys },			/* 172 = nosys */
	{ AS(pread_args), (sy_call_t *)pread },		/* 173 = pread */
	{ AS(pwrite_args), (sy_call_t *)pwrite },	/* 174 = pwrite */
	{ 0, (sy_call_t *)nosys },			/* 175 = nosys */
	{ AS(ntp_adjtime_args), (sy_call_t *)ntp_adjtime },	/* 176 = ntp_adjtime */
	{ 0, (sy_call_t *)nosys },			/* 177 = sfork */
	{ 0, (sy_call_t *)nosys },			/* 178 = getdescriptor */
	{ 0, (sy_call_t *)nosys },			/* 179 = setdescriptor */
	{ 0, (sy_call_t *)nosys },			/* 180 = nosys */
	{ AS(setgid_args), (sy_call_t *)setgid },	/* 181 = setgid */
	{ AS(setegid_args), (sy_call_t *)setegid },	/* 182 = setegid */
	{ AS(seteuid_args), (sy_call_t *)seteuid },	/* 183 = seteuid */
	{ 0, (sy_call_t *)nosys },			/* 184 = lfs_bmapv */
	{ 0, (sy_call_t *)nosys },			/* 185 = lfs_markv */
	{ 0, (sy_call_t *)nosys },			/* 186 = lfs_segclean */
	{ 0, (sy_call_t *)nosys },			/* 187 = lfs_segwait */
	{ AS(stat_args), (sy_call_t *)stat },		/* 188 = stat */
	{ AS(fstat_args), (sy_call_t *)fstat },		/* 189 = fstat */
	{ AS(lstat_args), (sy_call_t *)lstat },		/* 190 = lstat */
	{ AS(pathconf_args), (sy_call_t *)pathconf },	/* 191 = pathconf */
	{ AS(fpathconf_args), (sy_call_t *)fpathconf },	/* 192 = fpathconf */
	{ 0, (sy_call_t *)nosys },			/* 193 = nosys */
	{ AS(__getrlimit_args), (sy_call_t *)getrlimit },	/* 194 = getrlimit */
	{ AS(__setrlimit_args), (sy_call_t *)setrlimit },	/* 195 = setrlimit */
	{ AS(getdirentries_args), (sy_call_t *)getdirentries },	/* 196 = getdirentries */
	{ AS(mmap_args), (sy_call_t *)mmap },		/* 197 = mmap */
	{ 0, (sy_call_t *)nosys },			/* 198 = __syscall */
	{ AS(lseek_args), (sy_call_t *)lseek },		/* 199 = lseek */
	{ AS(truncate_args), (sy_call_t *)truncate },	/* 200 = truncate */
	{ AS(ftruncate_args), (sy_call_t *)ftruncate },	/* 201 = ftruncate */
	{ AS(sysctl_args), (sy_call_t *)__sysctl },	/* 202 = __sysctl */
	{ AS(mlock_args), (sy_call_t *)mlock },		/* 203 = mlock */
	{ AS(munlock_args), (sy_call_t *)munlock },	/* 204 = munlock */
	{ AS(undelete_args), (sy_call_t *)undelete },	/* 205 = undelete */
	{ AS(futimes_args), (sy_call_t *)futimes },	/* 206 = futimes */
	{ AS(getpgid_args), (sy_call_t *)getpgid },	/* 207 = getpgid */
	{ 0, (sy_call_t *)nosys },			/* 208 = newreboot */
	{ AS(poll_args), (sy_call_t *)poll },		/* 209 = poll */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 210 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 211 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 212 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 213 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 214 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 215 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 216 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 217 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 218 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)lkmnosys },	/* 219 = lkmnosys */
	{ AS(__semctl_args), (sy_call_t *)__semctl },	/* 220 = __semctl */
	{ AS(semget_args), (sy_call_t *)semget },	/* 221 = semget */
	{ AS(semop_args), (sy_call_t *)semop },		/* 222 = semop */
	{ 0, (sy_call_t *)nosys },			/* 223 = semconfig */
	{ AS(msgctl_args), (sy_call_t *)msgctl },	/* 224 = msgctl */
	{ AS(msgget_args), (sy_call_t *)msgget },	/* 225 = msgget */
	{ AS(msgsnd_args), (sy_call_t *)msgsnd },	/* 226 = msgsnd */
	{ AS(msgrcv_args), (sy_call_t *)msgrcv },	/* 227 = msgrcv */
	{ AS(shmat_args), (sy_call_t *)shmat },		/* 228 = shmat */
	{ AS(shmctl_args), (sy_call_t *)shmctl },	/* 229 = shmctl */
	{ AS(shmdt_args), (sy_call_t *)shmdt },		/* 230 = shmdt */
	{ AS(shmget_args), (sy_call_t *)shmget },	/* 231 = shmget */
	{ AS(clock_gettime_args), (sy_call_t *)clock_gettime },	/* 232 = clock_gettime */
	{ AS(clock_settime_args), (sy_call_t *)clock_settime },	/* 233 = clock_settime */
	{ AS(clock_getres_args), (sy_call_t *)clock_getres },	/* 234 = clock_getres */
	{ 0, (sy_call_t *)nosys },			/* 235 = timer_create */
	{ 0, (sy_call_t *)nosys },			/* 236 = timer_delete */
	{ 0, (sy_call_t *)nosys },			/* 237 = timer_settime */
	{ 0, (sy_call_t *)nosys },			/* 238 = timer_gettime */
	{ 0, (sy_call_t *)nosys },			/* 239 = timer_getoverrun */
	{ AS(nanosleep_args), (sy_call_t *)nanosleep },	/* 240 = nanosleep */
	{ 0, (sy_call_t *)nosys },			/* 241 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 242 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 243 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 244 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 245 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 246 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 247 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 248 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 249 = nosys */
	{ AS(minherit_args), (sy_call_t *)minherit },	/* 250 = minherit */
	{ AS(rfork_args), (sy_call_t *)rfork },		/* 251 = rfork */
	{ AS(openbsd_poll_args), (sy_call_t *)openbsd_poll },	/* 252 = openbsd_poll */
	{ 0, (sy_call_t *)issetugid },			/* 253 = issetugid */
	{ AS(lchown_args), (sy_call_t *)lchown },	/* 254 = lchown */
	{ 0, (sy_call_t *)nosys },			/* 255 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 256 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 257 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 258 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 259 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 260 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 261 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 262 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 263 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 264 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 265 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 266 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 267 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 268 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 269 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 270 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 271 = nosys */
	{ AS(getdents_args), (sy_call_t *)getdents },	/* 272 = getdents */
	{ 0, (sy_call_t *)nosys },			/* 273 = nosys */
	{ AS(lchmod_args), (sy_call_t *)lchmod },	/* 274 = lchmod */
	{ AS(lchown_args), (sy_call_t *)lchown },	/* 275 = netbsd_lchown */
	{ AS(lutimes_args), (sy_call_t *)lutimes },	/* 276 = lutimes */
	{ AS(msync_args), (sy_call_t *)msync },		/* 277 = netbsd_msync */
	{ AS(nstat_args), (sy_call_t *)nstat },		/* 278 = nstat */
	{ AS(nfstat_args), (sy_call_t *)nfstat },	/* 279 = nfstat */
	{ AS(nlstat_args), (sy_call_t *)nlstat },	/* 280 = nlstat */
	{ 0, (sy_call_t *)nosys },			/* 281 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 282 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 283 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 284 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 285 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 286 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 287 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 288 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 289 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 290 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 291 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 292 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 293 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 294 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 295 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 296 = nosys */
	{ AS(fhstatfs_args), (sy_call_t *)fhstatfs },	/* 297 = fhstatfs */
	{ AS(fhopen_args), (sy_call_t *)fhopen },	/* 298 = fhopen */
	{ AS(fhstat_args), (sy_call_t *)fhstat },	/* 299 = fhstat */
	{ AS(modnext_args), (sy_call_t *)modnext },	/* 300 = modnext */
	{ AS(modstat_args), (sy_call_t *)modstat },	/* 301 = modstat */
	{ AS(modfnext_args), (sy_call_t *)modfnext },	/* 302 = modfnext */
	{ AS(modfind_args), (sy_call_t *)modfind },	/* 303 = modfind */
	{ AS(kldload_args), (sy_call_t *)kldload },	/* 304 = kldload */
	{ AS(kldunload_args), (sy_call_t *)kldunload },	/* 305 = kldunload */
	{ AS(kldfind_args), (sy_call_t *)kldfind },	/* 306 = kldfind */
	{ AS(kldnext_args), (sy_call_t *)kldnext },	/* 307 = kldnext */
	{ AS(kldstat_args), (sy_call_t *)kldstat },	/* 308 = kldstat */
	{ AS(kldfirstmod_args), (sy_call_t *)kldfirstmod },	/* 309 = kldfirstmod */
	{ AS(getsid_args), (sy_call_t *)getsid },	/* 310 = getsid */
	{ AS(setresuid_args), (sy_call_t *)setresuid },	/* 311 = setresuid */
	{ AS(setresgid_args), (sy_call_t *)setresgid },	/* 312 = setresgid */
	{ 0, (sy_call_t *)nosys },			/* 313 = obsolete signanosleep */
	{ AS(aio_return_args), (sy_call_t *)aio_return },	/* 314 = aio_return */
	{ AS(aio_suspend_args), (sy_call_t *)aio_suspend },	/* 315 = aio_suspend */
	{ AS(aio_cancel_args), (sy_call_t *)aio_cancel },	/* 316 = aio_cancel */
	{ AS(aio_error_args), (sy_call_t *)aio_error },	/* 317 = aio_error */
	{ AS(aio_read_args), (sy_call_t *)aio_read },	/* 318 = aio_read */
	{ AS(aio_write_args), (sy_call_t *)aio_write },	/* 319 = aio_write */
	{ AS(lio_listio_args), (sy_call_t *)lio_listio },	/* 320 = lio_listio */
	{ 0, (sy_call_t *)yield },			/* 321 = yield */
	{ AS(thr_sleep_args), (sy_call_t *)thr_sleep },	/* 322 = thr_sleep */
	{ AS(thr_wakeup_args), (sy_call_t *)thr_wakeup },	/* 323 = thr_wakeup */
	{ AS(mlockall_args), (sy_call_t *)mlockall },	/* 324 = mlockall */
	{ 0, (sy_call_t *)munlockall },			/* 325 = munlockall */
	{ AS(__getcwd_args), (sy_call_t *)__getcwd },	/* 326 = __getcwd */
	{ AS(sched_setparam_args), (sy_call_t *)sched_setparam },	/* 327 = sched_setparam */
	{ AS(sched_getparam_args), (sy_call_t *)sched_getparam },	/* 328 = sched_getparam */
	{ AS(sched_setscheduler_args), (sy_call_t *)sched_setscheduler },	/* 329 = sched_setscheduler */
	{ AS(sched_getscheduler_args), (sy_call_t *)sched_getscheduler },	/* 330 = sched_getscheduler */
	{ 0, (sy_call_t *)sched_yield },		/* 331 = sched_yield */
	{ AS(sched_get_priority_max_args), (sy_call_t *)sched_get_priority_max },	/* 332 = sched_get_priority_max */
	{ AS(sched_get_priority_min_args), (sy_call_t *)sched_get_priority_min },	/* 333 = sched_get_priority_min */
	{ AS(sched_rr_get_interval_args), (sy_call_t *)sched_rr_get_interval },	/* 334 = sched_rr_get_interval */
	{ AS(utrace_args), (sy_call_t *)utrace },	/* 335 = utrace */
	{ 0, (sy_call_t *)nosys },			/* 336 = obsolete freebsd4_sendfile */
	{ AS(kldsym_args), (sy_call_t *)kldsym },	/* 337 = kldsym */
	{ AS(jail_args), (sy_call_t *)jail },		/* 338 = jail */
	{ 0, (sy_call_t *)nosys },			/* 339 = pioctl */
	{ SYF_MPSAFE | AS(sigprocmask_args), (sy_call_t *)sigprocmask },	/* 340 = sigprocmask */
	{ AS(sigsuspend_args), (sy_call_t *)sigsuspend },	/* 341 = sigsuspend */
	{ AS(sigaction_args), (sy_call_t *)sigaction },	/* 342 = sigaction */
	{ AS(sigpending_args), (sy_call_t *)sigpending },	/* 343 = sigpending */
	{ AS(sigreturn_args), (sy_call_t *)sigreturn },	/* 344 = sigreturn */
	{ 0, (sy_call_t *)nosys },			/* 345 = sigtimedwait */
	{ 0, (sy_call_t *)nosys },			/* 346 = sigwaitinfo */
	{ AS(__acl_get_file_args), (sy_call_t *)__acl_get_file },	/* 347 = __acl_get_file */
	{ AS(__acl_set_file_args), (sy_call_t *)__acl_set_file },	/* 348 = __acl_set_file */
	{ AS(__acl_get_fd_args), (sy_call_t *)__acl_get_fd },	/* 349 = __acl_get_fd */
	{ AS(__acl_set_fd_args), (sy_call_t *)__acl_set_fd },	/* 350 = __acl_set_fd */
	{ AS(__acl_delete_file_args), (sy_call_t *)__acl_delete_file },	/* 351 = __acl_delete_file */
	{ AS(__acl_delete_fd_args), (sy_call_t *)__acl_delete_fd },	/* 352 = __acl_delete_fd */
	{ AS(__acl_aclcheck_file_args), (sy_call_t *)__acl_aclcheck_file },	/* 353 = __acl_aclcheck_file */
	{ AS(__acl_aclcheck_fd_args), (sy_call_t *)__acl_aclcheck_fd },	/* 354 = __acl_aclcheck_fd */
	{ AS(extattrctl_args), (sy_call_t *)extattrctl },	/* 355 = extattrctl */
	{ AS(extattr_set_file_args), (sy_call_t *)extattr_set_file },	/* 356 = extattr_set_file */
	{ AS(extattr_get_file_args), (sy_call_t *)extattr_get_file },	/* 357 = extattr_get_file */
	{ AS(extattr_delete_file_args), (sy_call_t *)extattr_delete_file },	/* 358 = extattr_delete_file */
	{ AS(aio_waitcomplete_args), (sy_call_t *)aio_waitcomplete },	/* 359 = aio_waitcomplete */
	{ AS(getresuid_args), (sy_call_t *)getresuid },	/* 360 = getresuid */
	{ AS(getresgid_args), (sy_call_t *)getresgid },	/* 361 = getresgid */
	{ 0, (sy_call_t *)kqueue },			/* 362 = kqueue */
	{ AS(kevent_args), (sy_call_t *)kevent },	/* 363 = kevent */
	{ 0, (sy_call_t *)nosys },			/* 364 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 365 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 366 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 367 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 368 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 369 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 370 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 371 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 372 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 373 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 374 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 375 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 376 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 377 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 378 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 379 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 380 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 381 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 382 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 383 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 384 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 385 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 386 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 387 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 388 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 389 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 390 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 391 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 392 = nosys */
	{ AS(sendfile_args), (sy_call_t *)sendfile },	/* 393 = sendfile */
	{ 0, (sy_call_t *)nosys },			/* 394 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 395 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 396 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 397 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 398 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 399 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 400 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 401 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 402 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 403 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 404 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 405 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 406 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 407 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 408 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 409 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 410 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 411 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 412 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 413 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 414 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 415 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 416 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 417 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 418 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 419 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 420 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 421 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 422 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 423 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 424 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 425 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 426 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 427 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 428 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 429 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 430 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 431 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 432 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 433 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 434 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 435 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 436 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 437 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 438 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 439 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 440 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 441 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 442 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 443 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 444 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 445 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 446 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 447 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 448 = nosys */
	{ 0, (sy_call_t *)nosys },			/* 449 = nosys */
	{ AS(varsym_set_args), (sy_call_t *)varsym_set },	/* 450 = varsym_set */
	{ AS(varsym_get_args), (sy_call_t *)varsym_get },	/* 451 = varsym_get */
	{ AS(varsym_list_args), (sy_call_t *)varsym_list },	/* 452 = varsym_list */
	{ AS(upc_register_args), (sy_call_t *)upc_register },	/* 453 = upc_register */
	{ AS(upc_control_args), (sy_call_t *)upc_control },	/* 454 = upc_control */
	{ AS(caps_sys_service_args), (sy_call_t *)caps_sys_service },	/* 455 = caps_sys_service */
	{ AS(caps_sys_client_args), (sy_call_t *)caps_sys_client },	/* 456 = caps_sys_client */
	{ AS(caps_sys_close_args), (sy_call_t *)caps_sys_close },	/* 457 = caps_sys_close */
	{ AS(caps_sys_put_args), (sy_call_t *)caps_sys_put },	/* 458 = caps_sys_put */
	{ AS(caps_sys_reply_args), (sy_call_t *)caps_sys_reply },	/* 459 = caps_sys_reply */
	{ AS(caps_sys_get_args), (sy_call_t *)caps_sys_get },	/* 460 = caps_sys_get */
	{ AS(caps_sys_wait_args), (sy_call_t *)caps_sys_wait },	/* 461 = caps_sys_wait */
	{ AS(caps_sys_abort_args), (sy_call_t *)caps_sys_abort },	/* 462 = caps_sys_abort */
	{ AS(caps_sys_getgen_args), (sy_call_t *)caps_sys_getgen },	/* 463 = caps_sys_getgen */
	{ AS(caps_sys_setgen_args), (sy_call_t *)caps_sys_setgen },	/* 464 = caps_sys_setgen */
	{ AS(exec_sys_register_args), (sy_call_t *)exec_sys_register },	/* 465 = exec_sys_register */
	{ AS(exec_sys_unregister_args), (sy_call_t *)exec_sys_unregister },	/* 466 = exec_sys_unregister */
	{ AS(sys_checkpoint_args), (sy_call_t *)sys_checkpoint },	/* 467 = sys_checkpoint */
	{ AS(mountctl_args), (sy_call_t *)mountctl },	/* 468 = mountctl */
	{ AS(umtx_sleep_args), (sy_call_t *)umtx_sleep },	/* 469 = umtx_sleep */
	{ AS(umtx_wakeup_args), (sy_call_t *)umtx_wakeup },	/* 470 = umtx_wakeup */
};
