#ifndef __LIBSYS_H__
#define __LIBSYS_H__		/* avoid reentrant */

typedef char sigset_t;
typedef long long size_t;
typedef unsigned int mode_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;

struct timespec {
	long	tv_sec;		/* seconds */
	long	tv_nsec;	/* nanoseconds */
};

struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* microseconds */
};

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of DST correction */
};

int sys_read(unsigned int fd, char *buf, size_t count);
int sys_write(unsigned int fd, const char *buf, size_t count);
int sys_open(const char *filename, int flags, int mode);
int sys_close(unsigned int fd);
//int sys_stat(const char *filename, struct stat *statbuf);
int sys_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
int sys_mprotect(unsigned long start, size_t len, unsigned long prot);
int sys_munmap(unsigned long addr, size_t len);
//int sys_rt_sigaction(int sig, const struct sigaction *act, struct sigaction *oact, size_t sigsetsize);
//int sys_rt_sigprocmask(int how, sigset_t *nset, sigset_t *oset, size_t sigsetsize);
int sys_pipe(int *filedes);
int sys_dup(unsigned int filedes);
int sys_dup2(unsigned int oldfd, unsigned int newfd);
int sys_pause();
int sys_nanosleep(struct timespec *rqtp, struct timespec *rmtp);
int sys_fork();
int sys_exit(int error_code);
int sys_getcwd(char *buf, unsigned long size);
int sys_chdir(const char *filename);
int sys_rename(const char *oldname, const char *newname);
int sys_mkdir(const char *pathname, int mode);
int sys_rmdir(const char *pathname);
int sys_creat(const char *pathname, int mode);
int sys_link(const char *oldname, const char *newname);
int sys_unlink(const char *pathname);
int sys_readlink(const char *path, char *buf, int bufsz);
int sys_chmod(const char *filename, mode_t mode);
int sys_chown(const char *filename, uid_t user, gid_t group);
int sys_umask(int mask);
int sys_gettimeofday_(struct timeval *tv, struct timezone *tz);
int sys_getuid();
int sys_getgid();
int sys_setuid(uid_t uid);
int sys_setgid(gid_t gid);
int sys_geteuid();
int sys_getegid();
//int sys_rt_sigpending(sigset_t *set, size_t sigsetsize);
//int sys_rt_sigsuspend(sigset_t *unewset, size_t sigsetsize);

long sleep(long s);

#endif	/* __LIBSYS_H__ */
