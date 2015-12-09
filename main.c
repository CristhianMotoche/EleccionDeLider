#include <mpi.h>
#include <stdio.h>
#include "process.h"
#include "function.h"

int main(int arg, char *argv[]){
  int r, p;
  MPI_Init(&arg, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &r);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  while(1){
    if(r == 0){
      printf("Copiar un nuevo archivo\n");
      cliente();
    }
    else if (r == 1){
      int empezarUno = 1;
      MPI_Recv(&empezarUno, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(&empezarUno, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
      servidor("ri2.txt", 1);
    }
    else if (r == 2){
      int empezarDos;
      MPI_Recv(&empezarDos, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      servidor("ri2-2.txt", 2);
    }
  }
  MPI_Finalize();
  return 0;
}
