#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <stdio.h>

void firstRound(int r, int id, int x[], int y[]){
  if(r == 0){
    x[0] = id;
    x[1] = r;
    printf("Rank: %d. Con id: %d\n", x[1], x[0]);
    MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
  }
  // Middle process
  for(i = 1; i < N - 1; i++){
    if(r == i){
      y[0] = id;
      y[1] = r;
      printf("Rank: %d. Con id: %d\n", y[1], y[0]);
      MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if(y[0] > x[0]){
        MPI_Send(&y, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
      }
      else{
        MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
      }
    }
  }
  // Last process
  if(r == N - 1){
    y[0] = id;
    y[1] = r;
    printf("Rank: %d. Con id: %d\n", y[1], y[0]);
    MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("El líder es: %d. Con id: %d. Soy el proceso: %d\n", x[1], x[0], r);
    MPI_Send(&x, 2, MPI_INT, 0, r, MPI_COMM_WORLD);
  }
}
