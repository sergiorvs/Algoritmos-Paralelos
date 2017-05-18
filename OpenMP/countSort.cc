#include <iostream>
#include <omp.h>
#include <time.h>
#include <cstdlib>

using namespace std;

int numthreads = 500;


//********************************Paralelisado*********************************************
void countSort(int a[],int n)
{
    int i, j, count;
    int *temp;
    temp= new int[n];

    #pragma omp parallel for shared(a, n, temp) private(i, j, count)num_threads(numthreads)
        for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }

    #pragma omp parallel for shared(a, n, temp) private(i)num_threads(numthreads)
    for (i = 0; i < n; i++)
        a[i] = temp[i];

    free(temp);
}
//********************************Sin Paralelizar********************************************
void Count_sort (int a [], int n ) {
    int i , j , count;
    int* temp;
    temp= new int[n];
    for (i = 0; i < n ; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a [i])
                count++;
            else if ( a[j ] == a[i] && j < i)
                count++;
        temp [count] = a [i];
    }
    for (i = 0; i < n; i++)
        a[i] = temp[i];
    free(temp );
	}

//*****************************Para Libreria qsort******************************************

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
////////////////////////////////////////////////////////////////////////////////////////////

void igualar(int a[] ,int b[],int n)
{
	int i;
	for(i=0;i<n;i++){
		a[i]=b[i];
	}
}

int main()
{

    /******************Time Variables*********************************/
    clock_t time;
    //int n = 1000;
    int n;
    cin>>n;
    int* lista,*listas,*listal;

    lista= new int[n];listas= new int[n];listal= new int[n];
    for (int i = 0; i < n; i++)
    {
        lista[i] = rand()%n;

    }
    igualar(listas,lista,n);
    igualar(listal,lista,n);

    time = clock();
    countSort(lista,n);
    time = clock() - time;

    cout<<"El Tiempo Paralelo es: "<<(((float)time)/CLOCKS_PER_SEC)<<endl;

    time = clock();
    Count_sort(listas,n);
    time = clock() - time;

    cout<<"El Tiempo Secuencial es: "<<(((float)time)/CLOCKS_PER_SEC)<<endl;

    time = clock();
    qsort(listal,n,sizeof(int),cmpfunc);
    time = clock() - time;

    cout<<"El Tiempo con la libreria es: "<<(((float)time)/CLOCKS_PER_SEC)<<endl;

    return 0;
}


/*
a)If we try to parallelize the for i loop (the outer loop), which variables should be private and which should be shared?

Las variables a y n deben ser compartidas, ya que sería necesario acceder a la variable a y tener acceso a su tamaño. 
La variable temporal también sería compartida, ya que cada posición del array sólo sería escrita por un solo hilo.
Las variables i, j, count deberían ser privadas.

b)If we parallelize the for i loop using the scoping you specified in the previous part, are there any loop-carried dependences? Explain your answer.

No, no habría ninguna dependencia entre las iteraciones, ya que no sería necesario tener acceso a una información de otra 
iteración durante la ejecución del código.
Además, la variable temporal se puede escribir por los subprocesos sin generar problemas de competencia.

c)Can we parallelize the call to memcpy ? Can we modify the code so that this part of the function will be parallelizable?

	void Count sort (int a [], int n ) {
	int i , j , count ;
	int∗ temp = malloc ( n ∗sizeof(int));
	for ( i = 0; i < n ; i ++) {
	    count = 0;
	    for ( j = 0; j < n ; j ++)
	        if ( a [ j ] < a [ i ])
	            count ++;
	        else if ( a [ j ] == a [ i ] && j < i )
	            count ++;
	    temp [ count ] = a [ i ];
	}
	memcpy ( a , temp , n ∗sizeof(int));
	free ( temp );
	}

Sí, la llamada al memcpy también podría ser paralelizada. La única preocupación sería en relación con el tamaño de n que no debería ser el mismo. 
Además, el primer y el segundo argumento de la función memcpy, debería ser punteros para elementos del array desde el que debería comenzar la escritura.

	#pragma omp parallel for shared(a, n, temp) private(i)num_threads(numthreads)
	    for (i = 0; i < n; i++)
	        a[i] = temp[i];


*/