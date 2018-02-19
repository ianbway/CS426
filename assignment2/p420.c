// Ian Braudaway
// CS426-001 Assignment 2
// Problem 4.20, Uses 3.20 Implementation

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MIN_PID 300
#define MAX_PID 5000

int map[MAX_PID-MIN_PID];

int allocate_map(void);

int allocate_pid(void);

void release_pid(int);

void *allocate_pid_wrapper(void*);

// Creates and initializes a data structure
// for representing pids; returns—1 if unsuccessful, 1 if successful
int
allocate_map(void)
{	
	int i;

	for(i = MIN_PID; i < MAX_PID+1; i++) 
	{
  		map[i] = 0;   
	}

	printf("Map allocated.\n");

	return 1;
}

// Allocates and returns a pid; returns—
// 1 if unable to allocate a pid (all pids are in use)
int
allocate_pid(void)
{
	int i;

	for(i = MIN_PID; i < MAX_PID+1; i++) 
	{
		
		// If slot open, allocate pid and return number
		if(map[i] == 0) 
		{
			map[i] = 1;
			printf("PID at index %d allocated.\n", i);
			return i;
		}
	}

	// else return 1 if cannot allocate
	return 1;
}

// Releases a pid
void
release_pid(int pid)
{
	// release a pid by setting slot to 0
	map[pid] = 0;

	printf("PID %d released.\n", pid);
}

// wrapper for pthread_create call
void *
allocate_pid_wrapper(void *args)
{
	int randInt = rand() % 7;      // returns a pseudo-random integer between 0 and 7

    int retval = allocate_pid(); // allocate pid

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

	size_t i;

	for(i=0;i<100;i++) 
	{
		pthread_t thr;
    	pthread_create(&thr,NULL,allocate_pid_wrapper,NULL);
	}

	// give time for threads to release
	sleep(10);

	return 0;
}