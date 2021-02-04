/* primegaps.c -- Parallel Largest Prime Gap In Interval, v1.1
 *
 * Input: None.
 * Output: The largest gap between two consecutive integers,
 *	x & y given the interval [a, b].
 *
 * Algorithm:
 *	1.	Each process calculates its interval.
 *	2.	Each process finds all primes in its interval
 *		and populates a data structure holding their
 *		values.
 *	3a.	Each process != 0 sends its list to 0.
 *	3b.	Process 0 loops through the final list
 *		to find the largest gap between two consecutive
 *		values. List must be sorted.
 *
 * Notes:
 *	1.	a, b are hardcoded.
 *	2.	Number of processes (p) evenly divides the
*		rightmost boundary of [a, b].
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

const int MAX = 100000000;

struct Primes {
	int * primes_list;
	int count;
};

int main(int argc, char** argv) {
	int	my_rank;	/* My process rank		*/
	int	p;		/* The number of processes	*/
	int	a = 0;		/* Left interval boundary	*/
	int	b = MAX;	/* Right interval boundary	*/
	int	local_a;	/* Left boundary my process	*/
	int	local_b;	/* Right boundary my process	*/
	int	local_n;	/* Size of my interval		*/
	int	max_gap = 0;	/* Maximum gap			*/
	int 	prime1;		/* First prime			*/
	int	prime2;		/* Second prime			*/
	int	gap;		/* Largest gap			*/
	int	x;		/* First prime			*/
	int	y;		/* Consecutive prime		*/
	int 	l_prime1;	/* Local prime 1		*/
	int 	l_prime2;	/* Local prime 2		*/
	int	l_left_bound;	/* Local left bound prime	*/
	int	l_right_bound;	/* Local right bound prime	*/
	int 	source;		/* Process sending data		*/
	int 	dest = 0;	/* All messages go to 0		*/
	int 	tag = 0;
	struct	Primes local_primes;
	struct	Primes global_primes;
	int 	cur_local_gap = 0;	
	int 	max_local_gap = 0;
	int *num_list;
	MPI_Status status;
    
	/* Find out whether current index is a prime */
	bool isPrime(int current_index, int * num_list);

	/* Function to determine the minimum of two values */
	int min(int i, int j);

	/* Start up MPI */
	MPI_Init(&argc, &argv);

	/* Get my process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out how many process are being used */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	/* n is the same for all processes */
	local_n = b/p;

	/* Index of my boundaries */
	local_a = my_rank * (b / p) + min(my_rank, b % p);
	local_b = local_a + local_n;

	/* Initialize local_primes */
	local_primes.count = 0;
	local_primes.primes_list = (int *) malloc(sizeof(int) * MAX);
    	
	/* Initialize num_list (list of primes) */
	num_list = calloc((MAX+1),  sizeof(int));  	
	num_list[0] = -1;
	num_list[1] = -1;
	num_list[2] = 0;
	for(int i = 2; i <= sqrt(MAX); i++){
		if(num_list[i] == 0){
			for(int j = 2; (i*j) <= MAX; j++){
				num_list[i*j] = 1;
			}
		}
	}
	
	/* Loop through local range and populate prime_list  */
	int c = 0;
	for (int i = local_a; i<local_b; i++) {
		
		/* Appending to local_primes if current number is prime */
		if (isPrime(i, num_list)) {
			local_primes.primes_list[c] = i;
			c++;
			local_primes.count++;
		}
	}
	/* Find largest local_gap */
	int k = 1;
	for (int i = 0; i < local_primes.count - 1; i++) {
		cur_local_gap = local_primes.primes_list[k] - local_primes.primes_list[i];
		if (cur_local_gap > max_local_gap) {
			max_local_gap = cur_local_gap;
			l_prime1 = local_primes.primes_list[i];
			l_prime2 = local_primes.primes_list[k];
		}		
		k++;
	}

	/* Store local left and right bounds of local_primes */
	l_left_bound = local_primes.primes_list[0];
	l_right_bound = local_primes.primes_list[local_primes.count-1];


	/* Merge all processor outputs into one array */
	if (my_rank == 0) {
		
		/* Populate processor 0 output to global list */
		global_primes.primes_list = (int *) malloc(sizeof(int) * MAX);
		global_primes.primes_list[0] = local_primes.primes_list[local_primes.count-1];
		global_primes.count = 1;
		int i = 0;
		/* Receive primes, gaps, and boundaries from p > 0 */
		for (source = 1; source < p; source++) {
			tag = 0;
			MPI_Recv(&l_left_bound, 1, MPI_INT, 
					source, tag, MPI_COMM_WORLD, &status);
			
			tag = 1;
			MPI_Recv(&l_right_bound, 1, MPI_INT, 
					source, tag, MPI_COMM_WORLD, &status);
			
			tag = 2;
			MPI_Recv(&local_primes.count, 1, MPI_INT, source, tag, 
					MPI_COMM_WORLD, &status);

			tag = 3;
			MPI_Recv(&max_local_gap, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
			
			tag = 4;
			MPI_Recv(&l_prime1, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
			
			tag = 5;
			MPI_Recv(&l_prime2, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
			
			/* Populate global_primes with boundary primes */
			i = global_primes.count;
			global_primes.primes_list[i] = l_left_bound;
			i++;
			global_primes.count++;
			global_primes.primes_list[i] = l_right_bound;
			global_primes.count++;

			/* Update max_gap */
			if (max_local_gap > max_gap) {
				max_gap = max_local_gap;
				prime1 = l_prime1;
				prime2 = l_prime2;
			}
		}
	}
	
	/* Send output to dest */
	else {
		tag = 0;
		MPI_Send(&l_left_bound, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		tag = 1;
		MPI_Send(&l_right_bound, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		tag = 2;
		MPI_Send(&local_primes.count, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		tag = 3;
		MPI_Send(&max_local_gap, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		tag = 4;
		MPI_Send(&l_prime1, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		tag = 5;
		MPI_Send(&l_prime2, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
		free(local_primes.primes_list);
	}
	
	/* Print final results */
	if (my_rank == 0) {
		int j = 1;
		int tmp = 0;
		int cur_gap = 0;
		/* Handling boundary case */
		for (int i = 0; i < global_primes.count - 1; i+=2) {
			cur_gap = global_primes.primes_list[j] - global_primes.primes_list[i];
			if (cur_gap > max_gap) {
				max_gap = cur_gap;
				prime1 = global_primes.primes_list[i];
				prime2 = global_primes.primes_list[j];
			}
			j+=2;
			tmp++;
		}
		/* Output */
		printf("Max gap: %d. Between %d and %d.\n", max_gap, prime1, prime2);
		free(global_primes.primes_list);
	}

	/* Shut down MPI */
	MPI_Finalize();
} /* main */

bool isPrime(
	int current_index,	/* in */
	int * num_list		/* in */) {

	if (current_index == 0 || current_index == 1) return false;

	if (num_list[current_index] == 0){
		return true;
	}
	
	return false;


    
    /*
	int i = 2;

	while (i*i <= current_index) {
		if (current_index % i == 0) {
			return false;
		}
		i += 1;
	}
	return true;*/

	
}

int min(
	int i,			/* in */
	int j			/* in */) {

	return i < j ? i : j;
}
