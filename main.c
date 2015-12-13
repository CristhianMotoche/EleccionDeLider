#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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
        printf("Rank: %d. Con id: %d\n", x[1], x[0]);
        MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
    }
    // Middle processes
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
        if(y[0] > x[0]){
            printf("El líder es: %d. Con id: %d. Soy el proceso: %d\n", y[1], y[0], r);
            MPI_Send(&y, 2, MPI_INT, 0, r, MPI_COMM_WORLD);
        }
        else{
            printf("El líder es: %d. Con id: %d. Soy el proceso: %d\n", x[1], x[0], r);
            MPI_Send(&x, 2, MPI_INT, 0, r, MPI_COMM_WORLD);
        }
    }

    // Second step: send the id with the rank of the lider
    // Firt process
    if(r == 0){
        MPI_Recv(&x, 2, MPI_INT, N-1, N-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("El líder es: %d. Con id: %d. Soy el proceso: %d\n", x[1], x[0], r);
        MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
    }
    // Middle processes
    for(i = 1; i < N - 1; i++){
        if(r == i){
            MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("El líder es: %d. Con id: %d. Soy el proceso: %d\n", x[1], x[0], r);
            MPI_Send(&x, 2, MPI_INT, r+1, r, MPI_COMM_WORLD);
        }
    }
    // Last process
    if(r == N - 1){
        MPI_Recv(&x, 2, MPI_INT, r-1, r-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Fin");
    }
    MPI_Finalize();
    return 0;
}
