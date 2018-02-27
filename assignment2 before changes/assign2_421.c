// Ian Braudaway
// CS426-001 Assignment 2
// Problem 4.21

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int 
average(int *input)
{

	int c;
	for (c = 1; c < size; c++)
  	{
    	if (array[c] > maximum)
    	{
       	maximum  = array[c];
       	location = c+1;
    	}
	}
}

int 
maximum(int *input)
{

}

int 
minimum(int *input)
{

}

int 
main(int argc, char **argv)
{

	pthread_t thr;

	pthread_create(&thr,NULL,average,NULL);
	pthread_create(&thr,NULL,maximum,NULL);
	pthread_create(&thr,NULL,minimum,mNULL);
}