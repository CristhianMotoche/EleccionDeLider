#include <stdio.h>
#include <mpi.h>
#include "process.h"

#define SIZE 40

void cliente(){
  FILE *file;
  char path_save[SIZE]; 
  char line[SIZE]; 
  int empezar = 1;

  printf("Archivo a guardar\n");
  scanf("%s", path_save);

  file = fopen(path_save, "w");
  MPI_Send(&empezar, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  line[0] = '-';
  while(line[0] != '\0'){
    MPI_Recv(&line, SIZE, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%s", line);
    fprintf(file, "%s", line);
  }
  line[0] = '-';
  while(line[0] != '\0'){
    MPI_Recv(&line, SIZE, MPI_CHAR, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%s", line);
    fprintf(file, "%s", line);
  }
  fclose(file);
  printf("\nFin del paso de mensaje - CLIENTE\n");
}
