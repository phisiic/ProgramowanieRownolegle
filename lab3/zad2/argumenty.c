#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 // Liczba wątków

void *funkcja_watku(void *arg_wsk) {
    int data = *(long int*) arg_wsk;
    pthread_t thread_id = pthread_self(); // Pobieranie systemowego ID wątku

    // Wypisywanie informacji o wątku
    printf("Systemowy ID: %ld, Przesłany ID: %d\n", thread_id, data);

    pthread_exit(NULL);
}

int main() {
    pthread_t tid[NUM_THREADS], tid2[NUM_THREADS];
    int nr_w[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++)
    {
        nr_w[i] = i;
        pthread_create(&tid[i], NULL, funkcja_watku, &nr_w[i]);
    }
    
    // Oczekiwanie na zakończenie wątków
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("Wszystkie wątki zakończyły pracę.\n");
    pthread_exit(NULL);
    return 0;
}
