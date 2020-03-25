#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mode_t mask, oldMask, fileMode = 0666, dirMode = 0777;
    oldMask = umask(0044);
    printf("old octal: %o\n", oldMask);

    fileMode = 0666 & ~oldMask;
    printf("~oldMask: %o\n", ~oldMask);
    printf("file mode octal: %o\n", fileMode);
    open("a.txt", O_CREAT, fileMode);
    open("c.txt", O_CREAT, 0666);
    
    mask = umask(oldMask);
    printf("mask octal: %o\n", mask);

    fileMode = 0666 & ~mask;
    printf("~mask octal: %o\n", ~mask);
    printf("file mode octal: %o\n", fileMode);
    open("b.txt", O_CREAT, fileMode);
    open("d.txt", O_CREAT, 0666);

    return 0;
}
