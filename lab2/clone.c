#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna = 0;

#define ROZMIAR_STOSU 1024 * 64

int funkcja_watku(void *argument)
{
    char **args = (char **)argument;
    zmienna_globalna++;

    execv("./program", args);

    // Jeśli execv się nie powiedział
    printf("Proces potomny nie wykonal programu\n");

    return 0;
}

int main(int argc, char *argv[])
{
    void *stos;
    pid_t pid;
    int i;
    
    //Argumenty dla "program"
    char **args = malloc((argc + 1) * sizeof(char *));
    for (int j = 0; j < argc; j++)
    {
        args[j] = argv[j];
    }
    args[argc] = NULL; // Musi być NULL-terminated

    inicjuj_czas();
    stos = malloc(ROZMIAR_STOSU);
    if (stos == 0)
    {
        printf("Proces nadrzędny - błąd alokacji stosu\n");
        exit(1);
    }

    for (i = 0; i < 1000; i++)
    {
        pid = clone(&funkcja_watku, (void *)stos + ROZMIAR_STOSU,
                     CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, args);

        waitpid(pid, NULL, __WCLONE);
    }
    drukuj_czas();

    free(stos);
    free(args);

    return 0;
}
