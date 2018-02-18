// Ian Braudaway
// CS426-001 Assignment 2
// Problem 3.20, Implementation File

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "assign2_320.h"

// Creates and initializes a data structure
// for representing pids; returns—1 if unsuccessful, 1 if successful
int
allocate_map(void)
{	
	int i;

	for(i = 0; i < MAX_PID-MIN_PID+1; i++) 
	{
  		map[i] = 0;   
	}

	return 1;
}

// Allocates and returns a pid; returns—
// 1 if unable to allocate a pid (all pids are in use)
int
allocate_pid(void)
{
	int i;

	for(i = 0; i < MAX_PID-MIN_PID+1; i++) 
	{
		
		// If slot open, allocate pid and return number
		if(map[i] == 0) 
		{
			map[i] = 1;
			return i + MIN_PID;
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
	map[MIN_PID + pid] = 0;
}