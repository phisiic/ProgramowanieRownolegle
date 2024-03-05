#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

typedef struct{
  double a;
  double b; 
  double dx;
  double id;
} obszar;

double wynik;
double *tablica;

double funkcja ( double x );

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);

void* calka_podobszar_w(void* arg_wsk);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w){

  //printf("a %lf, b %lf, dx %lf\n", a, b, dx);

  double calka_suma_local = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości
  pthread_t watki[l_w];
  obszar struktury[l_w];

  // tworzenie wątków
  tablica = malloc(sizeof(obszar) * l_w);
  for(int i = 0; i < l_w; i++)
  {
    struktury[i].a = ((b-a) / l_w) * i;
    struktury[i].b = ((b-a) / l_w) * (i+1);
    struktury[i].dx = dx;
    struktury[i].id = i;
    pthread_create(&watki[i], NULL, calka_podobszar_w, &struktury[i]);
  }

  // oczekiwanie na zakończenie pracy wątków
  for(int i = 0; i < l_w; i++)
  {
    pthread_join(watki[i], NULL);
  }

  for(int i = 0; i < l_w; i++)
  {
    calka_suma_local += tablica[i];
  }

  return(calka_suma_local);
}



void* calka_podobszar_w(void* arg_wsk){

  double a_local, b_local, dx;
  // rozpakowanie danych przesłanych do wątku
  obszar lokal = *(obszar *)arg_wsk;
  a_local = lokal.a;
  b_local = lokal.b;
  dx = lokal.dx;
  int my_id = lokal.id; // skąd pobierany?
  printf("\nWątek %d: a_local %lf, b_local %lf, dx %lf\n", 
	 my_id, a_local, b_local, dx);
  // wywołanie zadania do wykonania: całkowanie w zadanym przedziale 
  // calka = calka_sekw(a_local, b_local, dx);
  // (trzeba także dodać prototyp na początku pliku)
  
// zadanie w funkcji calka_sekw jest równoważne obliczeniom:
  int N_local = ceil((b_local-a_local)/dx);
  double dx_adjust_local = (b_local-a_local)/N_local;
  printf("a_local %lf, b_local %lf, dx_adjust_local %lf, n_local %d\n", 
	 a_local, b_local, dx_adjust_local, N_local);
  int i;
  double calka = 0.0;
  for(i=0; i<N_local; i++){
    double x1 = a_local + i*dx_adjust_local;
    calka += 0.5*dx_adjust_local*(funkcja(x1)+funkcja(x1+dx_adjust_local));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);
  }
  tablica[my_id] = calka;
}
