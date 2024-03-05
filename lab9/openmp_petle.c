#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];
  int tid_matrix[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwĂłjna pÄtla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

  // podwĂłjna pÄtla - docelowo rĂłwnolegle
  double suma_parallel=0.0; int i,j;

  // //zadanie 7.1
  // #pragma omp parallel for default(none) reduction(+:suma_parallel) schedule(static, 2) shared(a) private(j) ordered
  // for(i=0;i<WYMIAR;i++) {
  //   int id_w = omp_get_thread_num();
  //   //#pragma omp ordered
  //   for(j=0;j<WYMIAR;j++) {
  //     suma_parallel += a[i][j];
  //      #pragma omp ordered
  //     // dla dekompozycji 1D
  //     printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
  //     // dla dekompozycji 2D
  //     //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
  //   }
  //   // #pragma omp ordered
  //   printf("\n");
  // }

  //   //zadanie 7.2
  // for(i=0;i<WYMIAR;i++) {
  //   int id_w = omp_get_thread_num();
  //   #pragma omp parallel for default(none) schedule(dynamic) reduction(+:suma_parallel) shared(a, i) private(j) ordered
  //   for(j=0;j<WYMIAR;j++) {
  //     suma_parallel += a[i][j];
  //      #pragma omp ordered
  //     // dla dekompozycji 1D
  //     printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
  //     // dla dekompozycji 2D
  //     //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
  //   }
  //   #pragma omp ordered
  //   printf("\n");
  // }

  //zadanie 7.3
  #pragma omp parallel for default(none) reduction(+:suma_parallel) schedule(static) shared(a, tid_matrix) private(i, j) ordered 
  for(j=0;j<WYMIAR;j++) {
    int id_w = omp_get_thread_num();
    #pragma omp ordered
    for(i=0;i<WYMIAR;i++) {
      suma_parallel += a[i][j];
      tid_matrix[i][j] = id_w;
      printf("(%1d,%1d)-W_%1d", i, j, omp_get_thread_num()); 
    }
    printf("\n");
  }

  printf("ID wątku na poszczególnych indeksach:\n");
  for (i = 0; i < WYMIAR; i++)
  {
    for (j = 0; j < WYMIAR; j++)
    {
      printf("(%1d,%1d)-W_%1d ", i, j, tid_matrix[i][j]);
    }
    printf("\n");
  }

  //   //zadanie 7.2
  // for(i=0;i<WYMIAR;i++) {
  //   int id_w = omp_get_thread_num();
  //   #pragma omp parallel for default(none) schedule(dynamic) reduction(+:suma_parallel) shared(a, i) private(j) ordered
  //   for(j=0;j<WYMIAR;j++) {
  //     suma_parallel += a[i][j];
  //      #pragma omp ordered
  //     // dla dekompozycji 1D
  //     printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
  //     // dla dekompozycji 2D
  //     //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
  //   }
  //   #pragma omp ordered
  //   printf("\n");
  // }

  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}


// double suma_parallel=0.0; int i,j;

  // for(i = 0; i < WYMIAR; i++){
  //   double suma_tmp = 0.0;

  // #pragma omp parallel for default(none) shared(a,suma_parallel,i) private(j) firstprivate(suma_tmp) schedule(static) ordered
  //   for(j = 0; j < WYMIAR; j++){
  //     suma_tmp += a[i][j];

  //     #pragma omp ordered
  //     printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num());
  //     if(j == WYMIAR-1)
  //       printf("\n");
  //   }

  // #pragma omp atomic 
  //   suma_parallel += suma_tmp;
  // }
  

  // printf("Suma wyrazow tablicy rownolegle: %lf\n", suma_parallel);