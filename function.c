#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "function.h"

#define SIZE 40

void servidor(char *filename, int tag){
  FILE *file;
  printf("%s", filename);
  file = fopen(filename, "r");
  char line[SIZE];
  while(fgets(line, sizeof line, file) != NULL){
    MPI_Send(&line, SIZE, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
  }
  fclose(file);
  line[0] = '\0';
  MPI_Send(&line, 1, MPI_INT, 0, 21, MPI_COMM_WORLD);
  printf("\nFin del paso de mensaje - SERVIDOR \n");
}
