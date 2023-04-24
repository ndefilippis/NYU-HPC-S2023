#!/bin/bash

#SBATCH --job-name=ping-pong
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=2GB
#SBATCH --time=01:00:00
#SBATCH --verbose
#SBATCH --output=pingpong.out

module purge 
module load intel/19.1.2
module load openmpi/intel/4.0.5

mpirun ./pingpong 0 1
