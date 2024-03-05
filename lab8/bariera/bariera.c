#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int liczba_watkow;
static int licznik;

void bariera_init(int n) {
    liczba_watkow = n;
    licznik = 0;
}

void bariera(void) {
    pthread_mutex_lock(&mutex);

    licznik++;

    if (licznik < liczba_watkow) {
        pthread_cond_wait(&cond, &mutex);
    } else {
        licznik = 0;
        pthread_cond_broadcast(&cond);
    }

    pthread_mutex_unlock(&mutex);
}

void bariera() {
    pthread_mutex_lock(&mutex);
    licznik++;
    if(licznik < nr_threads)
    {
        pthread_cond_wait(&cond, &mutex);
    }
    else 
    {
        licznik = 0;
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);
}