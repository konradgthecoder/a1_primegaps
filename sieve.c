#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 200

int *num_list;

void sieve(){
	num_list[0] = -1;
	num_list[1] = -1;
	num_list[2] = 0;
	for(int i = 2; i <= sqrt(MAX); i++){
		if(num_list[i] == 0){
			//prime_line[i] = 1;
			for(int j = 2; (i*j) <= MAX; j++){
				num_list[i*j] = 1;
			}
		}
	}

}

int main(){

	num_list = calloc((MAX+1),sizeof(int));

	sieve();

	for(int i = 2; i <= MAX; i++){
		if(!num_list[i]){
			printf("integer: %d , %d\n",i, num_list[i]);
		}
	}

}