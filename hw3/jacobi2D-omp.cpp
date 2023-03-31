// + Experiment with different optimization levels from -O0 to -O3 and report
//   the flop-rate and the bandwidth observed on your machine.
// + Specify the the compiler version (using the command: "g++ -v")
// + Try to find out the frequency, the maximum flop-rate and the maximum main
//   memory bandwidth for your processor.
// $ g++ -O3 -std=c++11 MMult0.cpp && ./a.out

#include <stdio.h>
#include <cmath>
#include "utils.h"
#if defined(_OPENMP)
#include <omp.h>
#endif

double Au_ij(double* u, long N, long i, long j) {
  double inv_h2 = (N+1)*(N+1);

  return inv_h2*(-   u[i-1 + N*j    ]
                 -   u[i   + N*(j-1)]
                 + 4*u[i   + N*j    ] 
                 -   u[i+1 + N*j    ] 
                 -   u[i   + N*(j+1)]);
}

double residual_norm(long N, double* u, double* f) {
  double residual = 0;

  #pragma omp parallel for reduction(+ : residual)
  for (long i = 1; i < N-1; i++) {
    for (long j = 1; j < N-1; j++) {
      double result = Au_ij(u, N, i, j) - f[i + N*j];
      residual += result * result;
    }
  }
  return sqrt(residual);
}

void jacobi(long N, double* u, double* f) {
  double h = 1.0/(N+1);
  double* u_old = (double*) malloc(N*N * sizeof(double));
  for (long i = 0; i < N*N; i++) u_old[i] = u[i]; // initialize u(k)
  
  #pragma omp parallel for
  for (long i = 1; i < N-1; i++) {
    for (long j = 1; j < N-1; j++) {
      double sum = u_old[i-1 + N*j    ] + 
                   u_old[i   + N*(j-1)] + 
                  u_old[i+1 + N*j    ] + 
                  u_old[i   + N*(j+1)];
      u[i + N*j] = (h*h*f[i+N*j] + sum)/4;
    }
  }

  free(u_old);
}

void inverse_solve(long N, double* u, double* f, long max_k) { 
  int k = 0;
  double res_orig = residual_norm(N, u, f);
  double res = res_orig;
  while (k < max_k && res >= 1e-4*res_orig) {
    jacobi(N, u, f);
    //printf("%f\n", res);
    k++;
    res = residual_norm(N, u, f);
  }
  printf("Original Residual: %2.10f\n", res_orig);
  printf("Iterations: %d\n", k);
  printf("Final Residual: %2.10f\n", res);
}

int main(int argc, char** argv) {
  long N = read_option<long>("-n", argc, argv);
  long max_k = read_option<long>("-N", argc, argv, "5000");

  double* u = (double*) malloc(N*N * sizeof(double));
  double* f = (double*) malloc(N*N * sizeof(double));
  double h = 1.0/(N+1);

  for (long i = 0; i < N*N; i++) u[i] = 0; // initialize u_0 = 0
  for (long i = 0; i < N*N; i++) f[i] = 1; // initialize f
  
  Timer t;
  printf("System size: %dx%d\n", N, N);
  t.tic();
  inverse_solve(N, u, f, max_k);
  
  printf("Time elapsed: %.5f\n", t.toc());

  free(u);
  free(f);
  return 0;
}

