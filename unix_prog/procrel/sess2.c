#include <stdio.h>
#include <unistd.h>

int main() {
	pid_t pid;
	printf("mypid = %u\n", getpid());
	if((pid = fork()) < 0) {
		perror("fork");
		return -1;
	}
	// parent
	if(pid > 0) {
		return 0;
	}
	// child
	if((pid = setsid()) < 0) {
		perror("child/setsid");
		return -1;
	}
	printf("child/setsid success: pid %u sid %u pgrp %u\n",
		getpid(), getsid(0), getpgrp());
	pause();
	return 0;
}

