#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "shell.h"


int main(int argc, char *argv[])
{
    /* seteuid setegid*/
    if(argc == 3){
        gid_t gid = strtoul(argv[2], NULL, 10);
        uid_t uid = strtoul(argv[1], NULL, 10);
        if(setegid(gid) < 0 || seteuid(uid) < 0){
            perror("[error: set euid egid]");
        }
    }else{
        pout("[warning] Incorrect number of arguments,");
        pout(" set default (euid,egid) to (0,0).\n");
    }
    /* execute interactive shell */
    shell();
    return 0;
}


