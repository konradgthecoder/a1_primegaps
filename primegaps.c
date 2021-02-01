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
#include "mpi.h"

#define MAX 100000

struct Primes {
	int primes_list[MAX];
	int count;
}

main(int argc, char** argv) {
	int	my_rank;	/* My process rank		*/
	int	p;		/* The number of processes	*/
	int	a = 0;		/* Left interval boundary	*/
	int	b = MAX;	/* Right interval boundary	*/
	int	local_a;	/* Left boundary my process	*/
	int	local_b;	/* Right boundary my process	*/
	int	local_n;	/* Size of my interval		*/
	int	gap;		/* Largest gap			*/
	int	x;		/* First prime			*/
	int	y;		/* Consecutive prime		*/
	int 	source;		/* Process sending data		*/
	int 	dest = 0;	/* All messages go to 0		*/
	int 	tag = 0;
	struct	Primes local_primes;
	struct	Primes global_primes;

	MPI_Status status;

	/* Find out whether current index is a prime */
	bool isPrime(int current_index);

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

	/* Loop through local range and populate prime_list  */
	int c = 0;
	for (int i = local_a; i<local_b; i++) {
		
		/* Appending to local_primes if current number is prime */
		if (isPrime(i)) {
			local_primes.primes_list[c] = i;
			c++;
			local_primes.count++;
		}
	}

	/* Merge all processor outputs into one array */
	if (my_rank == 0) {
		global_primes.count = 0;
		
		/* Populate processor 0 output to global list */
		for (int i = 0; i < local_primes.count; i++) {
			global_primes.primes_list[i] = local_primes.primes_list[i];
			global_primes.count++;
		}

		/* Populate remaining processor outputs to global list */
		for (source = 1; source < p; source++) {
			tag = 0;
			MPI_Recv(local_primes.primes_list, local_primes.count, MPI_INT, 
					source, tag, MPI_COMM_WORLD, &status);
			tag = 1;
			MPI_Recv(&local_primes.count, 1, MPI_INT, source, tag, 
					MPI_COMM_WORLD, &status);

			/* Populate global_primes */
			int i = global_primes.count;
			int j = 0;
			while (local_primes.primes_list[j]) {
				global_primes.primes_list[i] = local_primes.primes_list[j];
				i++;
				j++;
				global_primes.count++;
			}
		}
	}
	
	/* Send output to dest */
	else {
		tag = 0;
		MPI_Send(local_primes.primes_list, local_primes.count, MPI_INT, dest, tag, MPI_COMM_WORLD);
		tag = 1;
		MPI_Send(&local_primes.count, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	}
	
	/* Print final results */
	if (my_rank == 0) {
		for (int i = 0; i < global_primes.count; i++) {
			printf("%d, ", global_primes.primes_list[i]);
		}
		printf("\n");	
	}

	/* Shut down MPI */
	MPI_Finalize();
} /* main */

bool isPrime(
	int current_index	/* in */) {

	/* TODO: Code function that returns True if current_index
	 * 	is prime, False otherwise.
	 */
	int i;
	if (current_index <= 1) return false;
	for (i = 2; i < current_index; i++) {
		if (current_index % i == 0 && i != current_index) return false;
	}
	return true;
}

int min(
	int i,			/* in */
	int j			/* in */) {
	/* KONRAD CHANGE */
	return i < j ? i : j;
}

