#!/bin/bash -l
#SBATCH -A g2017012
#SBATCH -p node
#SBATCH -t 5:00
#SBATCH -N 1

module load gcc openmpi
mpirun  --map-by core ./integral2d


