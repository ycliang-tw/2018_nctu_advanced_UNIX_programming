#ifndef __BUILTIN_H__
#define __BUILTIN_H__

#include "shell.h"

#define Reg(name) {#name, name}
#define Decl(name)\
    void name(cmd_t*)


typedef struct builtin_t builtin_t;
struct builtin_t{
    char *name;
    void (*func)(cmd_t*);
};

Decl(_cat);
Decl(_cd);
Decl(_chmod);
Decl(_echo);
Decl(_find);
Decl(_help);
Decl(_id);
Decl(_mkdir);
Decl(_pwd);
Decl(_rm);
Decl(_rmdir);
Decl(_stat);
Decl(_touch);
Decl(_umask);

static const builtin_t builtinCmd[] = {
    Reg(_cat), Reg(_cd), Reg(_chmod), Reg(_echo), 
    Reg(_find), Reg(_help), Reg(_id), Reg(_mkdir), Reg(_pwd),
    Reg(_rm), Reg(_rmdir), Reg(_stat), Reg(_touch), Reg(_umask),
};

int check_arg_cnt(cmd_t *, int);

#endif
