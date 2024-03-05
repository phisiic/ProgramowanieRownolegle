#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float height;
} Person;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    Person osoba;    

    int rozm, rozm_pakietu;
    void* bufor;

    MPI_Pack_size(1, MPI_CHAR, MPI_COMM_WORLD, &rozm);
    rozm_pakietu = rozm;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozm);
    rozm_pakietu += rozm;
    MPI_Pack_size(1, MPI_FLOAT, MPI_COMM_WORLD, &rozm);
    rozm_pakietu += rozm;

    rozm_pakietu = 1000;

    bufor = malloc(rozm_pakietu);
    
    if(rank == 0){
        int pozycja = 0;
        snprintf(osoba.name, 50, "Marcin Pigon");
        osoba.age = 21;
        osoba.height = 185.5;

        MPI_Pack(osoba.name, 50, MPI_CHAR, bufor, rozm_pakietu, &pozycja, MPI_COMM_WORLD);
        MPI_Pack(&osoba.age, 1, MPI_INT, bufor, rozm_pakietu, &pozycja, MPI_COMM_WORLD);
        MPI_Pack(&osoba.height, 1, MPI_FLOAT, bufor, rozm_pakietu, &pozycja, MPI_COMM_WORLD);

        MPI_Send(bufor, pozycja, MPI_PACKED, next, 0, MPI_COMM_WORLD);

        printf("Proces %d wysłał:\n", rank);
        printf("Imię: %s\n", osoba.name);
        printf("Wiek: %d\n", osoba.age);
        printf("Wzrost: %f\n", osoba.height);
        printf("---------------------\n");
    }     
    

    else if (rank != 0 && rank <= size - 1) {
        MPI_Recv(bufor, rozm_pakietu, MPI_PACKED, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int pozycja = 0;
        MPI_Unpack(bufor, rozm_pakietu, &pozycja, osoba.name, 50, MPI_CHAR, MPI_COMM_WORLD);
        MPI_Unpack(bufor, rozm_pakietu, &pozycja, &osoba.age, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(bufor, rozm_pakietu, &pozycja, &osoba.height, 1, MPI_FLOAT, MPI_COMM_WORLD);

        // Wyświetlanie otrzymanych danych
        printf("Proces %d otrzymał:\n", rank);
        printf("Imię: %s\n", osoba.name);
        printf("Wiek: %d\n", osoba.age);
        printf("Wzrost: %f\n", osoba.height);
        printf("---------------------\n");

        osoba.age += rank;
        for(int i =0; i<rank; i++)
            strcat(osoba.name, "!");
        osoba.height -= size;

        MPI_Pack(osoba.name, 50, MPI_CHAR, bufor, rozm_pakietu, &pozycja, MPI_COMM_WORLD);
        MPI_Pack(&osoba.age, 1, MPI_INT, bufor, rozm_pakietu, &pozycja, MPI_COMM_WORLD);
        MPI_Pack(&osoba.height, 1, MPI_FLOAT, bufor, rozm_pakietu, &pozycja, MPI_COMM_WORLD);

        MPI_Send(bufor, pozycja, MPI_PACKED, next, 0, MPI_COMM_WORLD);

        printf("Proces %d wysłał:\n", rank);
        printf("Imię: %s\n", osoba.name);
        printf("Wiek: %d\n", osoba.age);
        printf("Wzrost: %f\n", osoba.height);
        printf("---------------------\n");
        
    }

    if(rank == 0){
            MPI_Recv(bufor, rozm_pakietu, MPI_PACKED, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int pozycja = 0;
            MPI_Unpack(bufor, rozm_pakietu, &pozycja, osoba.name, 50, MPI_CHAR, MPI_COMM_WORLD);
            MPI_Unpack(bufor, rozm_pakietu, &pozycja, &osoba.age, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(bufor, rozm_pakietu, &pozycja, &osoba.height, 1, MPI_FLOAT, MPI_COMM_WORLD);

            // Wyświetlanie otrzymanych danych
            printf("Proces %d otrzymał:\n", rank);
            printf("Imię: %s\n", osoba.name);
            printf("Wiek: %d\n", osoba.age);
            printf("Wzrost: %f\n", osoba.height);
            printf("---------------------\n");
        } 

    free(bufor);

    MPI_Finalize();
    return 0;
}
