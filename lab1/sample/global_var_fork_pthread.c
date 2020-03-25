#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int global = 10;
/*
int main()
{
    int pid = fork();
    if(pid == 0){   //parent
//        global = 20;
        sleep(1);
        printf("parent global: %d\n", global);
    }else if(pid > 0){ //child
        global = 30;
        printf("child global: %d\n", global);
    }else{
        fprintf(stderr, "[error] Cannot fork\n");
    }
}
*/

void *change()
{
    global = 20;
    printf("thread %d\n", global);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, change, NULL);
    pthread_join(tid, NULL);

    printf("main global %d\n", global);
    return 0;
}


