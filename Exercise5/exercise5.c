#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void)
{
    int rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char name[MPI_MAX_PROCESSOR_NAME];
    int len;
    MPI_Get_processor_name(name, &len);
    
    int x[10], y[10];

    /* 1. Allocate and attach a buffer for MPI_Bsend */
    int buffer_size = MPI_BSEND_OVERHEAD + 10 * sizeof(int);
    void* buffer = malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    if (rank == 1) {
        for (int r = 0; r < 10; r++) {
            x[r] = 10 * r;
        }

        printf("Sending message to computer 3 from computer 1 using Buffered Send (BSend)\n");
        /* 2. Use MPI_Bsend instead of MPI_Ssend */
        MPI_Bsend(x, 10, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    else if (rank == 3) {
        MPI_Recv(y, 10, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("In computer 3, the value of y is received:\n");
        for (int r = 0; r < 10; r++) {
            printf("%d ", y[r]);
        }
        printf("\n");
    }
    else {
        printf("Just a normal process from rank %d machine %s\n", rank, name);
    }

    /* 3. Detach and free the buffer before finalizing */
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    MPI_Finalize();
    return 0;
}
