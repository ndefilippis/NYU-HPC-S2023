#include <stdio.h>
#include <cstdlib>
#include <mpi.h>
#include <iostream>

double time_ring(long Nrepeat, int Nsize, MPI_Comm comm) {
  int rank, size;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  long* msg = (long*) malloc(Nsize * sizeof(long));
  for (int i = 0; i < Nsize; i++) msg[i] = 0;

  MPI_Barrier(comm);
  double tt = MPI_Wtime();
  msg[0] = rank;
  for (long repeat = 0; repeat < Nrepeat; repeat++) {
    MPI_Status status;
    if(rank == 0) {
    	MPI_Send(msg, Nsize, MPI_LONG, 1, 999, comm);
	MPI_Recv(msg, Nsize, MPI_LONG, size-1, 999, comm, &status);
	if(repeat == Nrepeat - 1) {
	  long expected = size * (size - 1) / 2 * Nrepeat;
	  printf("Message received, expected: %d, %d\n", msg[0], expected);
	}
    }
    else{
    	MPI_Recv(msg, Nsize, MPI_LONG, rank-1, 999, comm, &status);
	msg[0] = msg[0] + rank;
	MPI_Send(msg, Nsize, MPI_LONG, (rank+1) % size, 999, comm);
    }
  }
  tt = MPI_Wtime() - tt;

  free(msg);
  return tt;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size, host_length;
  char hostname[256];
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
  MPI_Get_processor_name(hostname, &host_length);
  printf("Rank %d/%d running on %s\n", rank, size, hostname);

  long Nrepeat;
  int Nsize = 2000000 / sizeof(long);
  if(argc < 2){
    Nrepeat = 1;
  }
  else{
    Nrepeat = atoi(argv[1]); 
  }
  double tt = time_ring(Nrepeat, Nsize, comm);
  if (!rank) printf("Time: %e ms\n", tt/Nrepeat * 1000);
  if (!rank) printf("Latency: %e ms\n", tt/Nrepeat/size * 1000);
  if (!rank) printf("Bandwith: %e Gb/s\n", Nrepeat*Nsize/size/tt/1e9);

  MPI_Finalize();
}

