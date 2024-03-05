#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Rozmiar stosu powinien wynosić 10 000 000 * 4 (rozmiar int) = 40 000 000

#define ROZMIAR_STOSU1 1024
#define ROZMIAR_STOSU2 1024*1024
#define ROZMIAR_STOSU3 1024*1024*39 //40 000 000 / 1048576 = 38.14697265625 ~39

void* funkcja_watku(void * argument)
{
    int tab[10000000] = { 0 };
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    size_t rozmiar = ROZMIAR_STOSU3;

    pthread_attr_setstacksize(&attr, rozmiar);

    pthread_create(&tid, &attr, funkcja_watku, NULL);

    pthread_attr_destroy(&attr);

    pthread_join(tid, NULL);

    pthread_exit(NULL);

}