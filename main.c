#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "process.h"
#include "function.h"

#define N 8

int main(int arg, char *argv[]){
  int r, p, i;
  int id = 0;
  int x[2];
  int y[2];
  MPI_Init(&arg, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &r);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  srand(time(NULL));
  id = function(r, rand()%100);

  // First step: send the id with the rank to campare with the other process
  // First process
  if(r == 0){
    x[0] = id;
    x[1] = r;
    printf("Envio desde rank: %d. Con id: %d\n", x[1], x[0]);
    MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
  }
  // Middle process
  for(i = 1; i < N - 1; i++){
    if(r == i){
      y[0] = id;
      y[1] = r;
      printf("Envio desde rank: %d. Con id: %d\n", y[1], y[0]);
      MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if(y[0] > x[0]){
        printf("Cambio");
        MPI_Send(&y, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
      }
      else{
        printf("Se mantiene");
        MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
      }
    }
  }
  // Last process
  if(r == N - 1){
    MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Repección r: %d. Con id: %d\n", x[1], x[0]);
  }
  // Second step: send the id with the rank of the lider
  // First process
  if(r == 0){
    x[0] = id;
    x[1] = r;
    printf("Envio desde rank: %d. Con id: %d\n", x[1], x[0]);
    MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
  }
  // Middle process
  for(i = 1; i < N - 1; i++){
    if(r == i){
      y[0] = id;
      y[1] = r;
      printf("Envio desde rank: %d. Con id: %d\n", y[1], y[0]);
      MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if(y[0] > x[0]){
        printf("Cambio");
        MPI_Send(&y, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
      }
      else{
        printf("Se mantiene");
        MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
      }
    }
  }
  // Last process
  if(r == N - 1){
    MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Repección r: %d. Con id: %d\n", x[1], x[0]);
  }
  MPI_Finalize();
  return 0;
}
