#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define FilA 1000
#define ColFilAB 1000
#define ColB 1000

#define BlockSize 1000


struct Matrix
{
  int fil,col;
  int** mat;
  Matrix(int i,int j)
  {
    fil=i;col=j;
    mat=new int* [i];
    for(int k=0;k<col;k++)
    {
      mat[k]=new int[col];
    }
  }
  int operator ()(int i,int j)
  {
    return mat[i][j];
  }
  void operator()(int i,int j,int dato)
  {
    mat[i][j]=dato;
  }
  
  void printmatrix()
  {
    for(int i=0; i<fil;i++)
    {
        for(int j=0; j<col; j++)
        {
            cout <<"["<<mat[i][j]<<"] ";
        }
        cout<<endl;

    }
  }
};

Matrix Matres1(FilA,ColB);
//Matrix Matres2(FilA,ColB);

void Three_nested_loop(Matrix a,Matrix b)
{
  for (int i = 0; i < a.fil; i++)
  {
    for (int j = 0; j < b.col; j++)
    {
        for (int k = 0; k < b.fil; k++)
        {
          Matres1.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
        }
    }
  }
}
/*
void Six_nested_loops(Matrix a,Matrix b)
{
  for(int i1=0;i1<(ColFilAB/BlockSize);i1++)
  {
    for(int j1=0;j1<(ColFilAB/BlockSize);j1++)
    {
      for(int k1=0;k1<(ColFilAB/BlockSize);k1++)
      {
        for(int i=i1=0;i<i1+BlockSize;i++)
        {
          for(int j=j1=0;j<j1+BlockSize;j++)
          {
            for(int k=k1;k<k1+BlockSize;k++)
            {               
              Matres2.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
          }
        }
      }
    }
  }
}*/


int main()
{
  Matrix a(FilA,ColFilAB);
  Matrix b(ColFilAB,ColB);
  int cont=0;
  for(int i=0;i<FilA;i++)
  {
    for(int j=0;j<ColFilAB;j++)
    {
      cont++;
      a(i,j,cont);
    }
  }
  cont=0;
  for(int i=0;i<ColFilAB;i++)
  {
    for(int j=0;j<ColB;j++)
    {
      cont++;
      b(i,j,cont);
    }
  }
  
  Three_nested_loop(a,b);
 // Matres1.printmatrix();
  //cout<<"-------------------------------"<<endl;
  //Six_nested_loops(a,b);
  //Matres2.printmatrix();
  
  return 0;
}











