#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

int main(int argc, char** argv) {
    int rank, size;
    long long local_count = 0;
    long long total_count = 0;
    double x, y, pi;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long chunk_size = N / size;
    if (rank == size - 1) {
        chunk_size += (N % size);
    }

    srand(time(NULL) + rank);
    double start_time = MPI_Wtime();

    /* Monte Carlo Calculation */
    for (long long i = 0; i < chunk_size; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if ((x * x + y * y) <= 1.0) {
            local_count++;
        }
    }

    /* 1. Allocate and attach a buffer for MPI_Bsend */
    int buffer_size = MPI_BSEND_OVERHEAD + sizeof(long long);
    void* buffer = malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    /* Communication */
    if (rank == 0) {
        total_count = local_count;
        long long recv_count;
        
        for (int i = 1; i < size; i++) {
            MPI_Recv(&recv_count, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            total_count += recv_count;
        }
    } else {
        /* 2. Workers use MPI_Bsend to send their counts */
        MPI_Bsend(&local_count, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }

    /* 3. Detach and free the buffer */
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        pi = 4.0 * (double)total_count / (double)N;
        printf("  Total Throws   : %d\n", N);
        printf("  Calculated Pi  : %f\n", pi);
        printf("  Time Taken     : %f seconds\n", end_time - start_time);
        printf("  (Calculated using MPI_ANY_SOURCE and BSend)\n");
    }

    MPI_Finalize();
    return 0;
}
