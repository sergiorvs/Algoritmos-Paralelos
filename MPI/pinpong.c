#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  MPI_Status status;
  int num=10;
  int rank, size, tag, next, from;
  int cont=0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 

  tag = 0;
  next = (rank + 1) % size;
  from = (rank + size - 1) % size;


  if (rank == 0) {
    printf("El proceso %d envio el mensaje %d al proceso %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, tag, MPI_COMM_WORLD); 
  }

  do {

    MPI_Recv(&num, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);
    printf("El proceso %d ha recibido el mensaje %d\n\n", rank, num);

    if (rank == 0) {
      --num;
      cont++;
      printf("(%d)\n\n",cont);
    }

    printf("El proceso %d envio el mensaje %d al proceso %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
  } while (num > 0);
  printf("Proceso %d termina\n", rank);


  
  //esperando..
  if (rank == 0)
    MPI_Recv(&num, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);

  MPI_Finalize();
  return 0;

}
 
