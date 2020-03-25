#ifndef __BUILTIN_H__
#define __BUILTIN_H__

#include "shell.h"

#define Reg(name) {#name, _##name}
#define Decl(name)\
    void _##name(shell_t*)


typedef struct builtin_t builtin_t;
struct builtin_t{
    char *name;
    void (*func)(shell_t*);
};

Decl(cat);
Decl(cd);
Decl(chmod);
Decl(echo);
Decl(find);
Decl(help);
Decl(id);
Decl(mkdir);
Decl(pwd);
Decl(rm);
Decl(rmdir);
Decl(stat);
Decl(touch);
Decl(umask);

static const builtin_t builtinCmd[] = {
    Reg(cat), Reg(cd), Reg(chmod), Reg(echo), 
    Reg(find), Reg(help), Reg(id), Reg(mkdir), Reg(pwd),
    Reg(rm), Reg(rmdir), Reg(stat), Reg(touch), Reg(umask),
};


#endif
