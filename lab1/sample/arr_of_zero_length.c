#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test{
    char name[16];
    char args[0][16];
};

int main()
{
    printf("sizeof(struct test) %d\n", sizeof(struct test));
    struct test *a = (struct test*)malloc(sizeof(struct test) + 1*sizeof(char)*16);
    char str[] = "this is a string.\n";
    char *tok = strtok(str, " \t\n\r");
    for(int i = 0; tok; i++){
        struct test *tmp = (struct test*)realloc(a, sizeof(struct test) + i*sizeof(char)*16);
        if(!tmp){ fprintf(stderr, "cannot resize\n"); return -1;}
        a = tmp;
        snprintf(&((char*)a->name)[16*i], 16, "%s", tok);
        tok = strtok(NULL, " \t\n\r");
    }

    printf("name %s\n", a->name);
    printf("args[0] %s\n", a->args[0]);
    printf("args[1] %s\n", a->args[1]);
    printf("args[2] %s\n", a->args[2]);
    return 0;
}
