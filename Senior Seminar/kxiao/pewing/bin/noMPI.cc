#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
  int myrank;
  //char hostname[256];

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  for (int i = 0; i<2, i++ {
      
      if (myrank == 0) {
	cout << "Rank 0 speaking" << endl;
	
      }
      else {
	
	
      }
    }
  cout << "Rank: " << myrank << endl;
  MPI_Finalize();

  return 0;
}

