#include "libsys.h"

int main() {
	char s[] = "sleeping for 5s ...\n";
	char m[] = "hello, world!\n";
	sys_write(1, s, sizeof(s));
	sleep(5);
	sys_write(1, m, sizeof(m));
	return 0;	
}

