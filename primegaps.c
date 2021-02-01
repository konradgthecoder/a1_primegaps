/* primegaps.c -- Parallel Largest Prime Gap In Interval, v1.0
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
#include <stdbool.h>
#include "mpi.h"

main(int argc, char** argv) {
	int	my_rank;	/* My process rank		*/
	int	p;		/* The number of processes	*/
	int	a = 0;		/* Left interval boundary	*/
	int	b = 1000000000;	/* Right interval boundary	*/
	int	local_a;	/* Left boundary my process	*/
	int	local_b;	/* Right boundary my process	*/
	int	local_n;	/* Size of my interval		*/
	int	gap;		/* Largest gap			*/
	int	x;		/* First prime			*/
	int	y;		/* Consecutive prime		*/
	int 	source;		/* Process sending data		*/
	int 	dest = 0;	/* All messages go to 0		*/
	int 	tag = 0;
	
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

	/* Index of my left boundary */
	local_a = my_rank * (b / p) + min(my_rank, b % p);
	
	/* Testing boundaries */
	printf("I am process %d, my left bound is: %d, my right bound is: %d.\n", my_rank, local_a, local_b);
	
	/* Shut down MPI */
	MPI_Finalize();
} /* main */

bool isPrime(
	int current_index	/* in */) {
	
	/* TODO: Code function that returns True if current_index
	 * 	is prime, False otherwise.
	 */
}

int min(
	int i,			/* in */
	int j			/* in */) {
        /*Abhis change*/
	return i < j ? i : j;
}

