#include <stdio.h>
#include <cstdlib>
#include <mpi.h>
#include <iostream>

double time_pingpong(int proc0, int proc1, long Nrepeat, long Nsize, MPI_Comm comm) {
  int rank;
  MPI_Comm_rank(comm, &rank);

  char* msg = (char*) malloc(Nsize);
  for (long i = 0; i < Nsize; i++) msg[i] = 42;

  MPI_Barrier(comm);
  double tt = MPI_Wtime();
  for (long repeat  = 0; repeat < Nrepeat; repeat++) {
    MPI_Status status;
    if (repeat % 2 == 0) { // even iterations

      if (rank == proc0)
        MPI_Send(msg, Nsize, MPI_CHAR, proc1, repeat, comm);
      else if (rank == proc1)
        MPI_Recv(msg, Nsize, MPI_CHAR, proc0, repeat, comm, &status);
    }
    else { // odd iterations

      if (rank == proc0)
        MPI_Recv(msg, Nsize, MPI_CHAR, proc1, repeat, comm, &status);
      else if (rank == proc1)
        MPI_Send(msg, Nsize, MPI_CHAR, proc0, repeat, comm);
    }
  }
  tt = MPI_Wtime() - tt;

  free(msg);
  return tt;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  if (argc < 3) {
    printf("Usage: mpirun ./pingpong <process-rank0> <process-rank1>\n");
    abort();
  }
  int proc0 = atoi(argv[1]);
  int proc1 = atoi(argv[2]);

  int rank, size;
  char hostname[256];
  int host_length;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
  MPI_Get_processor_name(hostname, &host_length);


  printf("Rank %d/%d running on %s.\n", rank, size, hostname);

  long Nrepeat = 100000;
  double tt = time_pingpong(proc0, proc1, Nrepeat, 1, comm);
  if (!rank) printf("pingpong latency: %e ms\n", tt/Nrepeat * 1000);

  Nrepeat = 100000;
  long Nsize = 100000;
  tt = time_pingpong(proc0, proc1, Nrepeat, Nsize, comm);
  if (!rank) printf("pingpong bandwidth: %e GB/s\n", (Nsize*Nrepeat)/tt/1e9);

  MPI_Finalize();
}

