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

void *
allocate_pid_wrapper(void)
{
    int retval = allocate_pid();
    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

int 
main(void)
{
	allocate_map();

	srand(time(NULL));   // should only be called once
	int randInt = rand();      // returns a pseudo-random integer between 0 and RAND_MAX

	pthread_t thr;
	size_t i;

	for(i=0;i<10;i++) 
	{
    	pthread_create(&thr,NULL,allocate_pid_wrapper(),NULL);
    	sleep(randInt);
    	release_pid(i);
	}

	return 0;
}