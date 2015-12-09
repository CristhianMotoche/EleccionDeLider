#include <mpi.h>
#include <stdio.h>
#include "process.h"
#include "function.h"

#define N 8
#define F 1

int main(int arg, char *argv[]){
  int r, p, i;
  int id = F;
  MPI_Init(&arg, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &r);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  if(r == 0){
    printf("Envio desde rank: %d\n", r);
    MPI_Send(&id, 1, MPI_INT, r+1, r, MPI_COMM_WORLD);
  }
  for(i = 1; i < N - 1; i++){
    if(r == i){
      printf("Esperando desde rank: %d\n", r);
      MPI_Recv(&id, 1, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Envio desde rank: %d\n", r);
      MPI_Send(&id, 1, MPI_INT, r+1, r, MPI_COMM_WORLD);
    }
  }
  if(r == N - 1){
    printf("Envio desde rank: %d\n", r);
  }
  MPI_Finalize();
  return 0;
}
