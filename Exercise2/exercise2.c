#include <mpi.h>
#include <stdio.h>

#define N 10000000

int main(int argc, char** argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Calculate the range of numbers for each process to add */
    long long chunk_size = N / size;
    long long start_num = rank * chunk_size + 1;
    
    /* Ensure the last process picks up any remainder */
    long long end_num = (rank == size - 1) ? N : start_num + chunk_size - 1;

    double start_time = MPI_Wtime();

    /* Each process calculates its own partial sum */
    long long local_sum = 0;
    for (long long i = start_num; i <= end_num; i++) {
        local_sum += i;
    }

    /* Reduce all local sums into the global sum on the root process */
    long long global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    /* Root process prints the result */
    if (rank == 0) {
        long long expected = (long long)N * (N + 1) / 2;
        printf("  Calculated Sum : %lld\n", global_sum);
        printf("  Expected Sum   : %lld\n", expected);
        printf("  Correct?       : %s\n", (global_sum == expected) ? "YES" : "NO");
        printf("  Time Taken     : %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
