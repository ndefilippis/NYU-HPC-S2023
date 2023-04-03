#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// Scan A array and write result into prefix_sum array;
// use long data type to avoid overflow
void scan_seq(long* prefix_sum, const long* A, long n) {
  if (n == 0) return;
  prefix_sum[0] = 0;
  for (long i = 1; i < n; i++) {
    prefix_sum[i] = prefix_sum[i-1] + A[i-1];
  }
}

void scan_omp(long* prefix_sum, const long* A, long n) {
  int p = omp_get_max_threads();
  int t;
  long i;
  long partial_sum;
  long offset;
  long* correction = (long *) malloc(p * sizeof(long));
  correction[0] = 0;

  #pragma omp parallel private(i, t, partial_sum, offset)
  {
    p = omp_get_num_threads();
    t = omp_get_thread_num();

    partial_sum = 0;
    #pragma omp for schedule(static) nowait
    for (i = 0; i < n; i++){
      prefix_sum[i] = partial_sum;
      partial_sum += A[i];
    }
    correction[t] = partial_sum;
    #pragma omp barrier

    offset = 0;
    for(i = 0; i < t; i++){
      offset += correction[i];
    }
    
    #pragma omp for schedule(static)
    for (i = 0; i < n; i++) {
      prefix_sum[i] += offset;
    }
  }
  free(correction);
}

int main() {
  long N = 10000000;
  long* A = (long*) malloc(N * sizeof(long));
  long* B0 = (long*) malloc(N * sizeof(long));
  long* B1 = (long*) malloc(N * sizeof(long));
  for (long i = 0; i < N; i++) A[i] = rand();
  for (long i = 0; i < N; i++) B1[i] = 0;
  
  double tt = omp_get_wtime();
  scan_seq(B0, A, N);
  printf("sequential-scan = %fs\n", omp_get_wtime() - tt);

  tt = omp_get_wtime();
  scan_omp(B1, A, N);
  printf("parallel-scan   = %fs\n", omp_get_wtime() - tt);

  long err = 0;
  for (long i = 0; i < N; i++) err = std::max(err, std::abs(B0[i] - B1[i]));
  printf("error = %ld\n", err);

  free(A);
  free(B0);
  free(B1);
  return 0;
}
