#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv) {
    int rank, ranksent, size, source, dest, tag, i;
    MPI_Status status;
    char hostname[1024];  // Buffer 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > 1) {
        if (rank != 0) {
            dest = 0;
            tag = 0;

            gethostname(hostname, sizeof(hostname));

            MPI_Send(&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
            MPI_Send(hostname, 1024, MPI_CHAR, dest, tag, MPI_COMM_WORLD);

        } else {
            for (i = 1; i < size; i++) {
                MPI_Recv(&ranksent, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

                char received_hostname[1024];
                MPI_Recv(received_hostname, 1024, MPI_CHAR, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &status);

                printf("Dane od procesu o randze %d: %d (i=%d), hostname: %s\n",
                       status.MPI_SOURCE, ranksent, i, received_hostname);
            }
        }
    } else {
        printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
    }

    MPI_Finalize();

    return 0;
}
