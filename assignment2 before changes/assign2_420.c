// Ian Braudaway
// CS426-001 Assignment 2
// Problem 4.20, Uses 3.20 Implementation and Header files

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "assign2_320.h"

// wrapper for pthread_create call
void *
allocate_pid_wrapper()
{
	int randInt = rand();      // returns a pseudo-random integer between 0 and RAND_MAX

    int retval = allocate_pid(); // allocate pid

    fprintf(stdout, "Allocated PID: %d \n", retval);
    sleep(randInt); // sleep for random period of time, randInt being the random number
    release_pid(retval); // release pid
    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

int 
main(void)
{
	allocate_map();

	srand(time(NULL));   // should only be called once, this is to make randint

	pthread_t thr;
	size_t i;

	for(i=0;i<100;i++) 
	{
    	pthread_create(&thr,NULL,allocate_pid_wrapper,NULL);
	}

	return 0;
}