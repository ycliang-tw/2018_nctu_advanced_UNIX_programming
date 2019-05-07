#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

static char err_o[] = "Error opening file.\n";
static char err_w[] = "Error writing to stdout.\n";

int main(int argc, char *argv[]) {
	int fd = 0, rlen;
	char buf[4096];
	if(argc > 1) {
		if((fd = open(argv[1], 0 /*O_RDONLY*/, 0)) < 0) {
			write(2, err_o, sizeof(err_o));
			return -1;
		}
	}
	while((rlen = read(fd, buf, sizeof(buf))) > 0) {
		if(write(1, buf, rlen) < 0) {
			write(2, err_w, sizeof(err_w));
			return -2;
		}
	}
	close(fd);
	return 0;
}

