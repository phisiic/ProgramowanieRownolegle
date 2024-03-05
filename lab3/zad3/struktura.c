#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct  {
    int numer_indeksu;
    char imie[50];
    char nazwisko[50];
    int wiek;
    double srednia_ocen;
} Student;

void* funkcja_watku(void* argument)
{
    Student *student = (Student*) argument;
    Student kopia = *(Student*)argument;
    //Student kopia = *student;
    pthread_t thread_id = pthread_self(); // Pobieranie systemowego ID wątku
    student->numer_indeksu -= 1;
    student->wiek *= 2;
    student->srednia_ocen += 0.5;

    kopia.numer_indeksu -= 1;
    kopia.srednia_ocen += 0.5;
    kopia.wiek *= 1;

    printf("Wątek:%ld - Wsk - %s %s, Numer indeksu: %d, %d l., Średnia: %f\n", thread_id, student->imie, student->nazwisko, student->numer_indeksu, student->wiek, student->srednia_ocen);
    printf("Wątek:%ld - Lok - %s %s, Numer indeksu: %d, %d l., Średnia: %f\n", thread_id, kopia.imie, kopia.nazwisko, kopia.numer_indeksu, kopia.wiek, kopia.srednia_ocen);
    pthread_exit(NULL);
}

int main()
{
    Student s = {10832, "Michal", "Nowak", 23, 3.78};
    Student* student = &s;
    printf("Main przed działaniem wątków - %s %s, Numer indeksu: %d, %d l., Średnia: %f\n", student->imie, student->nazwisko, student->numer_indeksu, student->wiek, student->srednia_ocen);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, funkcja_watku, &s);
    pthread_create(&tid2, NULL, funkcja_watku, &s);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Main po wątkach - %s %s, Numer indeksu: %d, %d l., Średnia: %f\n", student->imie, student->nazwisko, student->numer_indeksu, student->wiek, student->srednia_ocen);
    pthread_exit(NULL);
}