/**********************************************************************
 * Point-to-point communication using MPI
 *
 **********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int rank, size;
  double a, b;
  MPI_Request request;
MPI_Status status;
  MPI_Init(&argc, &argv);               /* Initialize MPI               */
  MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get the number of processors */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get my number                */
  
  a = 100.0 + (double) rank;  /* Different a on different processors */

  /* Exchange variable a, notice the send-recv order */
  if (rank == 0) {
    MPI_Isend(&a, 1, MPI_DOUBLE, 1, 111, MPI_COMM_WORLD,&request);
    MPI_Irecv(&b, 1, MPI_DOUBLE, 2, 333, MPI_COMM_WORLD, &request);
  } else if (rank==1) {
    MPI_Isend(&a, 1, MPI_DOUBLE, 2, 222, MPI_COMM_WORLD,&request);
    MPI_Irecv(&b, 1, MPI_DOUBLE, 0, 111, MPI_COMM_WORLD, &request);
  } else if (rank==2) {
    MPI_Isend(&a, 1, MPI_DOUBLE, 0, 333, MPI_COMM_WORLD,&request);
    MPI_Irecv(&b, 1, MPI_DOUBLE, 1, 222, MPI_COMM_WORLD, &request);
  }
  MPI_Wait(&request,&status);
  printf("Processor %d got %f \n",rank, b);
  MPI_Finalize(); 

  return 0;
}

