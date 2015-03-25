#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;


void printArray(int *array[], int numElements){
  for (int i = 0; i < numElements; i++){
    cout << array[i][0] << " ";
  }
  cout << "" << endl;
}



int pascalc(int i, int j){
  if(j == 0 || j == i){
    return 1;
  }else{
    return pascalc(i-1, j) + pascalc(i-1, j-1);
  }
}


void pascal(int rows){

  for(int i = 0; i < rows; i++){
    int row[i+1];
    for(int j = 0; j < (i+1); j++){
      row[j] = pascalc(i, j);
    }
    MPI_Send(row, i+1, MPI_INT, 1, i, MPI_COMM_WORLD);
    //    printArray(row, i + 1);
  }
  
}


int main(int argc, char **argv){
  int rank;
  int ROWS = 27;
  char hostname[256];
  int flip = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  gethostname(hostname, 255);

  if (rank == 0){
    // ROWS++;
    // MPI_Send(&ROWS, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    pascal(ROWS);
    // flip++;
    // MPI_Send(&flip, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

  }
  if (rank == 1){
    int *pyramid[ROWS];
    int zero[3];
    zero[0] = 0;
    zero[1] = 0;
    zero[2] = 0;
    for(int i = 0; i < ROWS; i++){
      pyramid[i] = zero;
    }
    for(int i = 0; i < ROWS; i++){
      int row[i+1];
      MPI_Recv(&row, i+1, MPI_INT, 0, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      // printArray(row, i+1);
      pyramid[i] = row;
      printArray(pyramid, ROWS);
    }


    // MPI_Recv(&flip, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // MPI_Recv(&ROWS, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // cout << "Process number: " << rank << " on host " << hostname << endl;
    // cout << "ROWS: " << ROWS << endl;
    // cout << flip << endl;
  }


 



  MPI_Finalize();

  return 0;
}
