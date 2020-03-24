#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>

#include "shell.h"
#include "builtins.h"
void shell()
{
    shell_t sh = {
        .prompt = "sis$",
        .parse = parse_cmd,
        .list = NULL,
        .exec = exec_cmd,
        .status = true,
        .init = init_cmd,
        .release = release_cmd,
    };

    sh.init(&sh);
    while(sh.status){
        sh.parse(&sh);
        sh.exec(&sh);
    }

fin:
    sh.release(&sh);
    exit(errno);
}

void parse_cmd(shell_t *sh)
{
    char input[len], whiteSpace[] = "\t\n\r ";
    char *tok = NULL;
    cmd_t *cmd = sh->list;

    pout("%s ", sh->prompt);
    fgets(input, len, stdin);

    tok = strtok(input, whiteSpace);
    for(int i = 0; tok != NULL; i++){
        cmd_t *tmp = realloc(cmd, sizeof(cmd_t) + i*sizeof(char*));
        if(!tmp){
            perr("[error] Cannot resize!\n");
            return;
        }
        cmd = tmp;
        ((char**)cmd)[i] = tok;
        tok = strtok(NULL, whiteSpace);
    }
}

void exec_cmd(shell_t *sh)
{
    if(!sh->list)
        return;
}
void init_cmd(shell_t *sh)
{
    sh->list = (cmd_t*)calloc(1, sizeof(cmd_t));
    
}
void release_cmd(shell_t *sh)
{
    free(sh->list);
}
