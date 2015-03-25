#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
  int rank;
  char hostname[256];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  gethostname(hostname, 255);

  cout << "Process number: " << rank << "on host " << hostname << endl;

  // printf("Process number: %d on host %s\n", rank, hostname);

  MPI_Finalize();

  return 0;

}
