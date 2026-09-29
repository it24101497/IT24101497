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

    /* Divide the iterations */
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

    /* Communication using MPI_Send and MPI_Recv with MPI_ANY_SOURCE */
    if (rank == 0) {
        total_count = local_count;
        long long recv_count;
        
        /* Root receives from all other processes using MPI_ANY_SOURCE */
        for (int i = 1; i < size; i++) {
            MPI_Recv(&recv_count, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            total_count += recv_count;
            // Optional: You could print status.MPI_SOURCE here to see which rank finished first!
        }
    } else {
        /* Workers send their local counts to the root */
        MPI_Send(&local_count, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }

    double end_time = MPI_Wtime();

    if (rank == 0) {
        pi = 4.0 * (double)total_count / (double)N;
        printf("  Total Throws   : %d\n", N);
        printf("  Calculated Pi  : %f\n", pi);
        printf("  Time Taken     : %f seconds\n", end_time - start_time);
        printf("  (Calculated using MPI_ANY_SOURCE)\n");
    }

    MPI_Finalize();
    return 0;
}
