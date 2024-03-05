#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18

int main ()
{
  double a[WYMIAR];

#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // pętla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  // pÄtla do modyfikacji - docelowo rĂłwnolegĹa w OpenMP
  double suma_parallel=0.0;

  //zadanie 3
// #pragma omp parallel for default(none) reduction(+:suma_parallel) shared(a) ordered

  //zadanie 4
// liczbę wątków można próbować określić jawnie poprzez:
//  użycie klauzuli num_threads w dyrektywie parallel, np.:
// #pragma omp parallel num_threads(10)
//  wywołanie procedury omp_set_num_threads, np.:
// omp_set_num_threads(10);
//  ustalenie zmiennej środowiskowej OMP_NUM_THREADS,np.:
// $ export OMP_NUM_THREADS=10

// #pragma omp parallel for default(none) reduction(+:suma_parallel) shared(a) ordered num_threads(4)

// omp_set_num_threads(4);
// #pragma omp parallel for default(none) reduction(+:suma_parallel) shared(a) ordered

//#pragma omp parallel for default(none) reduction(+:suma_parallel) shared(a) ordered

//zadanie 5.1
// #pragma omp parallel for default(none) schedule(static, 3) reduction(+:suma_parallel) shared(a) num_threads(4) ordered

//zadanie 5.2
// #pragma omp parallel for default(none) schedule(static) reduction(+:suma_parallel) shared(a) num_threads(4) ordered

//zadanie 5.3
// #pragma omp parallel for default(none) schedule(dynamic, 2) reduction(+:suma_parallel) shared(a) num_threads(4) ordered

//zadanie 5.4
#pragma omp parallel for default(none) schedule(dynamic) reduction(+:suma_parallel) shared(a) num_threads(4) ordered

  for(int i=0;i<WYMIAR;i++) {
    // int id_w = omp_get_thread_num();
    // ...
      suma_parallel += a[i];
      // ...
#pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i, omp_get_thread_num()); 
  }

  printf("\nSuma wyrazów tablicy równolegle (z klauzula - ....: %lf\n",
	 suma_parallel);

}