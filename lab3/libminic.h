#ifndef __LIBMINIC_H__
#define __LIBMINIC_H__		/* avoid reentrant */
#define pause() _pause()
#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGILL		 4
#define SIGTRAP		 5
#define SIGABRT		 6
#define SIGIOT		 6
#define SIGBUS		 7
#define SIGFPE		 8
#define SIGKILL		 9
#define SIGUSR1		10
#define SIGSEGV		11
#define SIGUSR2		12
#define SIGPIPE		13
#define SIGALRM		14
#define SIGTERM		15
#define SIGSTKFLT	16
#define SIGCHLD		17
#define SIGCONT		18
#define SIGSTOP		19
#define SIGTSTP		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGURG		23
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTALRM	26
#define SIGPROF		27
#define SIGWINCH	28
#define SIGIO		29
#define SIGPOLL		SIGIO
/*
#define SIGLOST		29
*/
#define SIGPWR		30
#define SIGSYS		31
#define	SIGUNUSED	31

/* These should not be considered constants from userland.  */
#define SIGRTMIN	32
#define SIGRTMAX	_NSIG


#define SIG_BLOCK		0
#define SIG_UNBLOCK		1
#define SIG_SETMASK		2


typedef void _restorefn_t(void);
typedef _restorefn_t* _sigrestore_t;
typedef void _signalfn_t(int);
typedef _signalfn_t* _sighandler_t;

typedef unsigned long sigset_t;
typedef long long size_t;

typedef struct jmp_buf_s {
	long long reg[8];
	sigset_t mask;
} jmp_buf[1];

struct sigaction {
	_sighandler_t		sa_handler;
	unsigned long		sa_flags;
	_sigrestore_t		sa_restorer;
	sigset_t			sa_mask;
};

/* syscall */
int sys_read(unsigned int fd, char *buf, size_t count);
int sys_write(unsigned int fd, const char *buf, size_t count);
int sys_rt_sigaction(int sig, const struct sigaction *act, struct sigaction *oact, size_t sigsetsize);
int sys_rt_sigprocmask(int how, sigset_t *nset, sigset_t *oset, size_t sigsetsize);
void sys_rt_sigreturn();
int sys_pause();
int sys_nanosleep(struct timespec *rqtp, struct timespec *rmtp);
int sys_exit(int error_code);
int sys_alarm(unsigned int seconds);

/* user function */
unsigned int	sleep(unsigned int seconds);
long			write(unsigned int fd, const char *buf, size_t count);
int				setjmp(jmp_buf jb);
void			longjmp(jmp_buf jb, int val);
int				sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int  			sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
unsigned int	alarm(unsigned int seconds);
int 			pause();
void 			exit(int status);

#endif	/* __LIBMINIC_H__ */
