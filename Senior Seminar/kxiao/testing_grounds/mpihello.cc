#include <mpi.h>
#include <iostream>
#include <stdio.h>


using namespace std;

int *size;

int pascalc(int i, int j){
  if(j == 0 || j == i){
    return 1;
  }else{
    return pascalc(i-1, j) + pascalc(i-1, j-1);
  }
}

int* pascal(int rows){
  int array[rows];
  for(int i = 0; i < rows; i++){
    int row[i+1];
    for(int j = 0; j < (i+1); j++){
      row[j] = pascalc(i, j);
    }
    array[i] = *row;
    //MPI_Send(size, 5, MPI_INT, 1, 98, MPI_COMM_WORLD);
  }
  return array;
}


int main(int argc, char **argv)
{
  int rank;
  int test[5];
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if (rank == 0){
    
    for(int i = 0; i < 5; i++){
      test[i] = i;
    }

    MPI_Send(test, 5, MPI_INT, 1, 99, MPI_COMM_WORLD);
  }
  else if (rank == 1){
    
    //MPI_Recv(size, 1, MPI_INT, 0, 98, MPI_COMM_WORLD, &status);
    MPI_Recv(test, 5, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
    
    for (int i = 0; i < 5; i++){
      cout << test[i] << " ";
    }
    cout << "" << endl;
  }

  MPI_Finalize();
  return 0;

}
