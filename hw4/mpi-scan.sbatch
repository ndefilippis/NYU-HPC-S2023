#!/bin/bash

#SBATCH --job-name=mpi-scan
#SBATCH --nodes=10
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=2GB 
#SBATCH --time=01:00:00 
#SBATCH --verbose
#SBATCH --output=mpi-scan.out

module purge 
module load  amber/openmpi/intel/20.06 

mpiexec ./mpi-scan 10000000
