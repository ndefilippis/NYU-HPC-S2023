#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Scan A array and write result into prefix_sum array;
// use long data type to avoid overflow


void scan_seq(long* prefix_sum, const long* A, long n) {
  if (n == 0) return;
  prefix_sum[0] = 0;
  for (long i = 1; i < n; i++) {
    prefix_sum[i] = prefix_sum[i-1] + A[i-1];
  }
}

void scan_mpi(long* prefix_sum, const long* A, long n, int rank, int size) {
  if (n == 0) return;
  long correction = 0;
  for (long i = 0; i < n; i++) {
    prefix_sum[i] = correction;
    correction += A[i];
  }
  long* offsets = (long *)malloc(sizeof(long) * size);
  MPI_Allgather(&correction, 1, MPI_LONG, offsets, 1, MPI_LONG, MPI_COMM_WORLD);
  
  long offset = 0;
  for(int i = 0; i < rank; i++){
    offset += offsets[i];
  }
  for(int i = 0; i < n; i++){
    prefix_sum[i] = prefix_sum[i] + offset;
  }
}


int main(int argc, char** argv) {
  int rank;
  int size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  long N = 10000000;
  long N_sub = N / size;

  long* A, *A_sub, *B0, *B1, *B1_sub;
  
  A_sub = (long *) malloc(N_sub * sizeof(long));
  B1_sub = (long*) malloc(N_sub * sizeof(long));
  
  if(!rank) {
    A = (long*) malloc(N * sizeof(long));
    B0 = (long*) malloc(N * sizeof(long));
    B1 = (long*) malloc(N * sizeof(long));
    for (long i = 0; i < N; i++) A[i] = rand();
    for (long i = 0; i < N; i++) B0[i] = 0;
    for (long i = 0; i < N; i++) B1[i] = 0;
  }
  for (long i = 0; i < N_sub; i++) B1_sub[i] = 0;
 
  MPI_Scatter(A, N_sub, MPI_LONG, A_sub, N_sub, MPI_LONG, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  
  double tt = MPI_Wtime();
  if(!rank){
    scan_seq(B0, A, N);
    printf("sequential-scan = %fs\n", MPI_Wtime() - tt);
  }

  tt = MPI_Wtime();
  scan_mpi(B1_sub, A_sub, N_sub, rank, size);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Gather(B1_sub, N_sub, MPI_LONG, B1, N_sub, MPI_LONG, 0, MPI_COMM_WORLD);

  if(!rank) printf("parallel-scan   = %fs\n", MPI_Wtime() - tt);

  if(!rank) {
    long err = 0;
    for (long i = 0; i < N; i++) err = std::max(err, std::abs(B0[i] - B1[i]));
    printf("error = %ld\n", err);
  }

  if(!rank) {
    free(A);
    free(B0);
    free(B1);
  }
  free(A_sub);
  free(B1_sub);

  MPI_Finalize();
  return 0;
}
