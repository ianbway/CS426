// Ian Braudaway
// Assignment 2 Testing Problem 3.20

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "assign2_320.h"

int 
main(void)
{
	allocate_map();
	int pid = allocate_pid();
	fprintf(stdout, "Allocated PID: %d \n", pid);
	release_pid(pid);

	int i;
	for (i=300; i<5001; i++)
	{
		int pid = allocate_pid();
		fprintf(stdout, "Allocated PID: %d \n", pid);
	}

	return 0;
}