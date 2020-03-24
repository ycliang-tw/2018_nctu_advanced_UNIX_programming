#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "builtins.h"
#include "shell.h"

void _help(cmd_t* cmd)
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

void _id(cmd_t *cmd)
{
    uid_t euid = geteuid();
    gid_t egid = getegid();
    pout("euid: %u, egid: %u\n", euid, egid);
}

void _pwd(cmd_t *cmd)
{
    char *cwd = NULL;
    pout("%s\n", getcwd(cwd, 0));
}

void _cat(cmd_t *cmd)
{
    int i = 0, fd = 0, size = 0;
    char content[1024];
    for(i = 0; cmd->args[i] != NULL; i++){
        pout("%s\n", cmd->args[i]);
        if((fd = open(cmd->args[i], O_RDONLY)) < 0){
            perr("[error] Cannot open file\n");
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

void _cd(cmd_t *cmd)
{
    if(cmd->args[0] == NULL){
        chdir(getenv("HOME"));
    }else if(cmd->args[1] == NULL){
        if(chdir(cmd->args[0]) == -1)
            perr("[error] Cannot change directory\n");
    }else{
        perr("[error] Too many arguments\n"); 
    }
}

void _chmod(cmd_t *cmd){}
void _echo(cmd_t *cmd){}
void _find(cmd_t *cmd){}
void _mkdir(cmd_t *cmd){}
void _rm(cmd_t *cmd){}
void _rmdir(cmd_t *cmd){}
void _stat(cmd_t *cmd){}
void _touch(cmd_t *cmd){}
void _umask(cmd_t *cmd){}

int main(){
    cmd_t *test = (cmd_t*)malloc(sizeof(cmd_t) + 3*sizeof(char*));
    test->cmd = "_cd";
    test->args[0] = "bin";
    test->args[1] = NULL;
    test->args[2] = NULL;

    _cd(test);
    _pwd(test);
}
