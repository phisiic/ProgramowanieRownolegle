#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sched.h>
//#include <linux/sched.h>

#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
    int zmienna_lokalna = *(int *) argument;

  //ID wątku
    pid_t tid = syscall(SYS_gettid);

    for (int i = 0; i < 100000; i++)
    {
        zmienna_lokalna++;
        zmienna_globalna++;
    }

    printf("Wątek %d - Zmienna lokalna: %d\n", tid, zmienna_lokalna);
    printf("Wątek %d - Zmienna globalna: %d\n", tid, zmienna_globalna);

    return 0;
}

int main()
{

  void *stos1, *stos2;
  pid_t pid1, pid2;
  int i; 
  int zmienna_lok = 0;
  

  stos1 = malloc( ROZMIAR_STOSU );
  stos2 = malloc( ROZMIAR_STOSU );
  if (stos1 == 0 || stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

    pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void *)&zmienna_lok);
    pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void *)&zmienna_lok);

    waitpid(pid1, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);

    printf("Main - Zmienna lokalna: %d\n", zmienna_lok);
  printf("Main - Zmienna globalna: %d\n",zmienna_globalna);
  
  free( stos1 );
  free( stos2 );

  return 0;
}
