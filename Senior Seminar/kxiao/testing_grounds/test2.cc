#include <iostream>
#include <string.h>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[])
{
  //cout << "hi" << endl;
  //char message[20];
  int myrank;
  MPI_Status status;
  bool check[2];
  check[0] = false;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  if (myrank == 1) /* code for process zero */{
    MPI_Recv(check, 1, MPI_C_BOOL, 0, 99,MPI_COMM_WORLD, &status);
    if (check[0]) {
      cout << "check[0] = " << check[0] << endl;
      cout << "true = " << true << endl;
      cout << "false = " << false << endl;
      cout << "It worked backwards" << endl;
    }
  }
  if (myrank == 0) /* code for process zero */
    {
      check[0] = true;
      //      check = true;
      MPI_Send(check, 1, MPI_C_BOOL, 1, 99, MPI_COMM_WORLD);
      cout << "message sent!" << endl;
    }
  
  MPI_Finalize();
  return 0;
}
