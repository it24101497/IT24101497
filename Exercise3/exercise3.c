#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000 /* 10,000,000 iterations */

int main(int argc, char** argv) {
    int rank, size;
    long long local_count = 0;
    long long total_count = 0;
    double x, y, pi;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Divide the 10,000,000 iterations among the processes */
    long long chunk_size = N / size;
    
    /* Ensure the last process picks up any remainder */
    if (rank == size - 1) {
        chunk_size += (N % size);
    }

    /* Seed the random number generator differently for each process */
    srand(time(NULL) + rank);

    double start_time = MPI_Wtime();

    /* Monte Carlo Method: Generate random points and check if they fall inside the circle */
    for (long long i = 0; i < chunk_size; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if ((x * x + y * y) <= 1.0) {
            local_count++;
        }
    }

    /* Combine all the local counts into the total_count at the root process */
    MPI_Reduce(&local_count, &total_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    /* Root process calculates Pi and prints the result */
    if (rank == 0) {
        pi = 4.0 * (double)total_count / (double)N;
        printf("  Total Throws   : %d\n", N);
        printf("  Calculated Pi  : %f\n", pi);
        printf("  Time Taken     : %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
