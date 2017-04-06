#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void)
{
	char greeting[MAX_STRING];
	int comm_sz;		//# de procesos
	int my_rank;		//proc id

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0) {
    	sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
    	MPI_Send(greeting, MAX_STRING, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }else{
    	 printf("Greetings from process %d of %d!\n", my_rank,comm_sz);
		 for (int q = 1; q < comm_sz; q++) {
			 MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			 printf("%s\n", greeting);
 			}

    }

MPI_Finalize();
return 0;

}

/*
What happens in the greetings program if, instead of strlen(greeting) + 1,
we use strlen(greeting) for the length of the message being sent by pro-
cesses 1, 2, . . . , comm sz−1? What happens if we use MAX STRING instead of
strlen(greeting) + 1? Can you explain these results?

Respuesta: 
-> El programa no sabria cuando es el final de la linea asi que sería bloqueado
-> Si se usara Max_String no pasaria nada porque el mensaje siempre estara dentro
de ese rango.

*/