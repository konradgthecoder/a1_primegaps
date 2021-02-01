#!/bin/bash
#SBATCH --account=def-ikotsire
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=4
#SBATCH --mem-per-cpu=1024M
#SBATCH --time=0-00:01
srun ./primegaps
