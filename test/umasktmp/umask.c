#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(){
	creat("aaa", RWRWRW);
	umask(0000);
	if(creat("foo", RWRWRW) < 0){
		perror("foo error");
	}
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if(creat("bar", RWRWRW) < 0)
		perror("bar error");
	return 0;
}
