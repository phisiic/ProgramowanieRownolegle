#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int message = 0;
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

        // Process 0 initializes the message
        if (rank == 0) {
            message = 0; // Initial value
            printf("Process %d initiated the relay with message %d to process %d\n", rank, message, next);
            MPI_Send(&message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        }

        if(rank != 0 && rank <= size - 1){
            // Receive the message from the previous process
            MPI_Recv(&message, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received message %d from process %d\n", rank, message, prev);
            
            // Modify the message
            message += 1;
        
            // Send the message to the next process
            MPI_Send(&message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
            printf("Process %d sent message %d to process %d\n", rank, message, next);

        }

        if (rank == 0) {
            MPI_Recv(&message, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d completed the relay. Final result: %d\n", rank, message);
        }

    MPI_Finalize();
    return 0;
}
