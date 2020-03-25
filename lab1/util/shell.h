#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdbool.h>

#define len 32

#define pout(fmt, ...) \
    fprintf(stdout, fmt, ##__VA_ARGS__)

#define perr(fmt, ...)\
    fprintf(stderr, fmt, ##__VA_ARGS__)

typedef struct shell_t shell_t;

typedef struct {
    int argsCnt;
    char name[len];
    char args[0][len];
}cmd_t;

struct shell_t{
    char prompt[len];
    cmd_t *list;
    bool status;
    void (*parse)(shell_t *);
    void (*exec)(shell_t *);
    void (*init)(shell_t *);
    void (*release)(shell_t *);
};


void shell();

void parse_cmd(shell_t *);
void exec_cmd(shell_t *);
void init_cmd(shell_t *);
void release_cmd(shell_t *);


#endif
