#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>

#include "shell.h"
#include "builtins.h"

extern const builtin_t builtinCmd[];

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
    int i = 0;
    char input[len], whiteSpace[] = "\t\n\r ";
    char *tok = NULL;
    cmd_t *cmd = sh->list;

    pout("%s ", sh->prompt);
    fgets(input, len, stdin);

    tok = strtok(input, whiteSpace);
    for(i = 0; tok != NULL; i++){
        cmd_t *tmp = realloc(cmd, sizeof(cmd_t) + i*sizeof(char)*len);
        if(!tmp){ perr("[error] Cannot resize!\n"); return; }
        cmd = tmp;
        snprintf(&((char*)cmd->name)[i*len], len, "%s", tok);
        tok = strtok(NULL, whiteSpace);
    }
    cmd->argsCnt = i-1;
    sh->list = cmd;
}

void exec_cmd(shell_t *sh)
{
    int i = 0;
    int listLen = sizeof(builtinCmd)/sizeof(builtin_t);
    cmd_t *cmd = sh->list;
    if(!cmd) return;
    if(strcmp(cmd->name, "exit") == 0){
        sh->status = false;
        return;
    }
    
    for(i = 0; i < listLen; i++){
        if(strcmp(cmd->name, builtinCmd[i].name) == 0){
            builtinCmd[i].func(sh);
            break;
        }
    }

    if(i == listLen)
        perr("[error] Not supported command\n");
}

void init_cmd(shell_t *sh)
{
    sh->list = (cmd_t*)calloc(1, sizeof(cmd_t));
}

void release_cmd(shell_t *sh)
{
    free(sh->list);
}

#ifdef debug
int main()
{
    shell();
}
#endif
