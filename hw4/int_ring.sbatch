#!/bin/bash

#SBATCH --job-name=int_ring
#SBATCH --nodes=6
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=2GB 
#SBATCH --time=01:00:00 
#SBATCH --verbose
#SBATCH --output=int_ring.out

module purge 
module load  amber/openmpi/intel/20.06 

mpiexec ./int_ring 100000
