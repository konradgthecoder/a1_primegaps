#!/bin/bash
#SBATCH --account=def-ikotsire
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=4
#SBATCH --mem-per-cpu=2048M
#SBATCH --time=0-00:05
srun ./primegaps
