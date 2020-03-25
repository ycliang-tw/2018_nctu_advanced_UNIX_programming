#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>

#include "builtins.h"
#include "shell.h"


void _help(shell_t *sh)
{
	pout("\tcat {file}:              Display content of {file}.\n");
	pout("\tcd {dir}:                Switch current working directory to {dir}.\n");
	pout("\tchmod {mode} {file/dir}: Change the mode (permission) of a file or directory.\n");
	pout("\t                         {mode} is an octal number.\n");
	pout("\techo {str} [filename]:   Display {str}. If [filename] is given,\n");
	pout("\t                         open [filename] and append {str} to the file.\n");
	pout("\texit:                    Leave the shell.\n");
	pout("\tfind [dir]:              List files/dirs in the current working directory\n");
	pout("\t                         or [dir] if it is given.\n");
	pout("\t                         Minimum outputs contatin file type, size, and name.\n");
	pout("\thelp:                    Display help message.\n");
	pout("\tid:                      Show current euid and egid number.\n");
	pout("\tmkdir {dir}:             Create a new directory {dir}.\n");
	pout("\tpwd:                     Print the current working directory.\n");
	pout("\trm {file}:               Remove a file.\n");
	pout("\trmdir {dir}:             Remove an empty directory.\n");
	pout("\tstat {file/dir}:         Display detailed information of the given file/dir.\n");
	pout("\ttouch {file}:            Create {file} if it does not exist,\n");
	pout("\t                         or update its access and modification timestamp.\n");
	pout("\tumask {mode}:            Change the umask of the current session.\n");
}

void _id(shell_t *sh)
{
    uid_t euid = geteuid();
    gid_t egid = getegid();
    pout("euid: %u, egid: %u\n", euid, egid);
}

void _pwd(shell_t *sh)
{
    char *cwd = NULL;
    pout("%s\n", getcwd(cwd, 0));
}

void _cat(shell_t *sh)
{
    int i = 0, fd = 0, size = 0;
    char content[1024];
    cmd_t *cmd = sh->list;

    for(i = 0; i < cmd->argsCnt; i++){
        if((fd = open(cmd->args[i], O_RDONLY)) < 0){
            perr("[error] Cannot open file\n");
            continue;
        }
        while((size = read(fd, content, 1024)) != 0){
            write(1, content, size);
        }
        close(fd);
    }
    if(i == 0){
        perr("[error] Missing file input\n");
    }
}

void _cd(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    char *path = getenv("HOME");
    if(cmd->argsCnt == 1)
        path = cmd->args[0];
    else if(cmd->argsCnt > 2)
        perr("[error] Too many arguments\n");
    
    if(chdir(path) == -1)
        perr("[error] Cannot change directory\n");
}

void _chmod(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    if(cmd->argsCnt < 2){
        perr("[error] Missing argument\n");
        return;
    }
    
    unsigned int mode = strtoul(cmd->args[0], NULL, 8);
    if(chmod(cmd->args[1], mode) < 0)
        perr("[error] %s\n", strerror(errno));
}

void _echo(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    if(cmd->argsCnt == 2){
        int fd = open(cmd->args[1], O_WRONLY | O_APPEND);
        if(fd < 0){
            perr("[error] Cannot open file\n");
        }else{
            dprintf(fd, "%s\n", cmd->args[0]);
        }
    }else if(cmd->argsCnt == 1){
        pout("%s\n", cmd->args[0]);
    }
}

void _find(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    char path[len*len] = {};
    DIR *dp = NULL;
    struct dirent *dirEntry = NULL;
    struct stat dirEntryStat;

    if(cmd->argsCnt == 0)
        getcwd(path, len*len);
    else if(cmd->argsCnt == 1)
        snprintf(path, strlen(cmd->args[0]), "%s", cmd->args[0]);
    else
        perr("[error] Too many arguments\n");
    
    if(!(dp = opendir(path))){
        perr("[error] %s\n", strerror(errno));
        return;
    }

    pout("file type\t\t\tsize\t\t\tname\n\n");
    while(dirEntry = readdir(dp)){
        stat(dirEntry->d_name, &dirEntryStat); 
        switch(dirEntry->d_type){
            case DT_REG:
                pout("file"); break;
            case DT_DIR:
                pout("dir."); break;
            case DT_FIFO:
                pout("fifo"); break;
            case DT_SOCK:
                pout("socket"); break;
            case DT_CHR:
                pout("c device"); break;
            case DT_BLK:
                pout("b device"); break;
            case DT_LNK:
                pout("sym. link"); break;
            default:
                pout("unknown"); break;
        }
        printf("\t\t\t\t%ld\t\t\t%s\n", dirEntryStat.st_size, dirEntry->d_name);
    }
    closedir(dp);
}

void _mkdir(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    for(int i = 0; i < cmd->argsCnt; i++){
        if(mkdir(cmd->args[i], 0777) < 0)
            perr("[error] %s\n", strerror(errno));
    }
}

void _rm(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    for(int i = 0; i < cmd->argsCnt; i++){
        if(remove(cmd->args[0]) < 0)
            perr("[error] %s\n", strerror(errno));
    }
}

void _rmdir(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    for(int i = 0; i < cmd->argsCnt; i++){
        if(rmdir(cmd->args[i]) < 0)
            perr("[error] %s\n", strerror(errno));
    } 
}

void _stat(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    for(int i = 0; i < cmd->argsCnt; i++){
        struct stat fileStat;
        if(stat(cmd->args[i], &fileStat) < 0){
            perr("[error] %s\n", strerror(errno));
            continue;
        }
        pout("hard link count \t uid \t gid \t block size \t block count \t\n");
        pout("%lu \t\t\t %d \t %d \t %ld \t\t %ld \n", fileStat.st_nlink, fileStat.st_uid, fileStat.st_gid, fileStat.st_size, fileStat.st_blksize);
        pout("\nlast modification time: %slast access time: %s", ctime(&fileStat.st_mtime), ctime(&fileStat.st_atime));

    }
}

void _touch(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    for(int i = 0; i < cmd->argsCnt; i++){
        if(access(cmd->args[i], F_OK) == -1){
            if(creat(cmd->args[i], 0666) == -1)
                perr("[error] %s\n", strerror(errno));
        }else{
            if(utimensat(AT_FDCWD, cmd->args[i], NULL, 0) == -1)
                perr("[error] %s\n", strerror(errno));
        }
    }
}
void _umask(shell_t *sh)
{
    cmd_t *cmd = sh->list;
    if(cmd->argsCnt < 1){
        perr("[error] Missing argument\n");
        return;
    }
    mode_t mode = strtoul(cmd->args[0], NULL, 8);
    umask(mode);
}

#ifdef debug
int main(){
    shell_t *sh = (shell_t*)malloc(sizeof(shell_t));
    sh->list = (cmd_t*)malloc(sizeof(cmd_t) + 3*sizeof(char*));
    cmd_t *test = sh->list;
    test->cmd = "_find";
    test->argsCnt = 1;
    test->args[0] = "djg";
    test->args[1] = "text.txt";
    test->args[2] = NULL;

    _find(sh);
}
#endif
