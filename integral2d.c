/**********************************************************************
 * This program evaluates a 2D integral using MPI/C
 *
 * Karl Ljungkvist
 * 2017-03-24
 **********************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <sys/time.h>

double timer() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

int main(int argc, char *argv[]) {
  int rank, size;
  const long int intervals = 100000L ; /* The sum is [globally]
                                         divided into this many
                                         intervals     */

  int chunk;             /* This many iterations will I do */
  int i, j, istart, istop;  /* Variables for the local loop   */
  double sum, dx, dy, globsum;
  double t;

  MPI_Init(&argc, &argv); /* Initialize MPI */

  MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get the number of processors */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get my number                */

  chunk  = intervals/size;       /* Number of intervals per processor */
  istart = rank*chunk+1;         /* Calculate start and stop indices  */
  istop  = (rank + 1)*chunk;     /* for the local loop                */
  if (rank == size-1 ) {
    istop = intervals;           /* Make sure the last processor      */
  }                              /* computes until the end            */


  if (rank == 0) {
    t = timer();
  }

  dx  = 1.0/intervals;
  dy  = 1.0/intervals;
  sum = 0.0;
  for (i = istart; i <= istop; i++) { /* The local loop */
    for(j=1; j<=intervals; ++j) {
      double x = dx*(i - 0.5);
      double y = dy*(j - 0.5);
      sum += dx*dy*4.0/(1.0 + x*x + y*y);
    }
  }

  /* COMPUTE THE FINAL RESULT ADDING THE PARTIAL SUMS */
  MPI_Reduce(&sum, &globsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  
  if (rank == 0) {
    t = timer() - t;
    printf("Integral is approx. %.16f\n",  globsum);
    printf("Time: %f s\n",  t);
  }


  MPI_Finalize(); /* Shut down and clean up MPI */

  return 0;
}

