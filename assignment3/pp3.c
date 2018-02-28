// Ian Braudaway
// CS426-001 Assignment 3
// Chapter 5 Project 3 - Producer Consumer Problem

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "buffer.h"

/* the buffer */ 
buffer_item buffer[BUFFER_SIZE];

int insert_item(buffer_item);
int remove_item(buffer_item);
void *producer_wrapper(void *);
void *consumer_wrapper(void *);

int 
insert_item(buffer_item item) 
{ 
	/* insert item into buffer return 0 if successful, otherwise return -1 indicating an error condition */ 
	if (buffer[BUFFER_SIZE] == 0)
	{
		buffer[BUFFER_SIZE] = item;
		return 0;
	}

	else if (buffer[BUFFER_SIZE] != 0)
	{

	}

	else
	{
		printf("Error. Could not add item to the back.\n"):
		return -1;
	}
} 

int 
remove_item(buffer_item *item) 
{ 
	/* remove an object from buffer placing it in item return 0 if successful, otherwise return -1 indicating an error condition */ 
	if (buffer[0])
	{
		item = buffer[0];
		return 0;
	}
	
	else
	{
		printf("Error. Could not remove item from front.\n"):
		return -1;
	}
} 

void *
producer_wrapper(void *param) 
{ 
	buffer_item item;
	while (true) 
	{ 
		/* sleep for a random period of time */ 
		randInt = rand();
		sleep(randInt); 

		// call insert item
		int retval = insert_item(item);

		/* generate a random number */ 
		item = rand(); 
		if (retval) 
		{
			fprintf("report error condition"); 
		}

		else 
		{
			printf("producer produced %d\n", item);
		}
	}

	// formatting return val for pthread
    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
} 

void *
consumer_wrapper(void *param) 
{ 
	buffer_item item;
	while (true) 
	{ 
		/* sleep for a random period of time */ 
		randInt = rand();
		sleep(randInt); 

		// call remove item
		int retval = remove_item(&item); 

		if (retval)
		{
			fprintf("report error condition"); 
		} 
			
		else 
		{
			printf("consumer consumed %d\n", item);
		}
	}

	// formatting return val for pthread
    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

int
main(int argc, char *argv[])
{

	/* 1. Get command line arguments argv[1],argv[2],argv[3] */ 
	/* 2. Initialize buffer */ 
	/* 3. Create producer thread(s) */ 
	/* 4. Create consumer thread(s) */ 
	/* 5. Sleep */ 
	/* 6. Exit */

	// Step 1
	int sleepTime = argv[1];
	int prodThreads = argv[2];
	int consThreads = argv[3];

	// Step 2
	int i;
	for (i = 0; i < BUFFER_SIZE; i++)
	{
		buffer[i] = 0;
	}

	// Step 3
	int j;
	for (j = 0; j < prodThreads; j++)
	{
		pthread_t prodThr;
    	pthread_create(&prodThr,NULL,producer_wrapper,NULL);
	}

	// Step 4
	int k;
	for (k = 0; k < consThreads; k++)
	{
		pthread_t consThr;
    	pthread_create(&consThr,NULL,consumer_wrapper,NULL);
	}

	// Step 5
	sleep(sleepTime);

	// Step 6
	return 0;
}