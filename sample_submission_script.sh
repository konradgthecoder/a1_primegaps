#!/bin/bash
#SBATCH --account=def-ikotsire
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH --mem-per-cpu=5G
#SBATCH --time=0-01:05
srun ./primegaps
