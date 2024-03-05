#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sched.h>

int main(int argc, char *argv[])
{
    pid_t tid = syscall(SYS_gettid);

    if (argc > 1) {
        printf("PID %d -", tid);
        for (int i = 1; i < argc; i++) {
            printf(" %s", argv[i]);
        }
        printf("\n");
    } else {
        printf("PID %d - Brak argumentów\n", tid);
    }

    return 0;
}