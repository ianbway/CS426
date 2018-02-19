// Ian Braudaway
// CS426-001 Assignment 2
// Problem 3.20, Implementation File

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MIN_PID 300
#define MAX_PID 5000

int map[MAX_PID-MIN_PID];

int allocate_map(void);

int allocate_pid(void);

void release_pid(int);

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

int 
main(void)
{
	allocate_map();
	allocate_pid();
	release_pid(300);

	allocate_pid();
	allocate_pid();
	allocate_pid();
	allocate_pid();
	allocate_pid();
	allocate_pid();
	allocate_pid();
	allocate_pid();
	release_pid(300);
	release_pid(301);
	release_pid(302);

	allocate_pid();

	int i;
	for (i=300; i<5000; i++)
	{
		allocate_pid();
	}

	return 0;
}