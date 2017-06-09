#!/bin/bash -l
#SBATCH -A g2017012
#SBATCH -p node
#SBATCH -t 5:00
#SBATCH -N 2

module load gcc openmpi
mpirun -np 2  --map-by node ./pingpong

