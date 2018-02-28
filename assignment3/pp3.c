// Ian Braudaway
// CS426-001 Assignment 3
// Chapter 5 Project 3 - Producer Consumer Problem

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "buffer.h"

/* the buffer */ 
buffer_item buffer[BUFFER_SIZE];

int buffSize = 0;

int insert_item(buffer_item);
int remove_item(buffer_item *);
void *producer_wrapper(void *);
void *consumer_wrapper(void *);

int 
insert_item(buffer_item item) 
{ 
	/* insert item into buffer return 0 if successful, otherwise return -1 indicating an error condition */ 

	int i;
	for (i = 0; i < BUFFER_SIZE; i++)
	{
		if (buffer[i] == 0)
		{
			buffer[i] = item;
			buffSize++;
			return 0;
		}

		else
		{
			printf("Error. Could not add item to the back.\n");
			return -1;
		}
	}
} 

int 
remove_item(buffer_item *item) 
{ 
	/* remove an object from buffer placing it in item return 0 if successful, otherwise return -1 indicating an error condition */ 
	if (buffer[0])
	{
		*item = buffer[0];
		buffer[0] = 0;
		buffSize--;

		int i;
		for (i = 0; i < BUFFER_SIZE; i++)
		{
			if ((buffer[i] == 0) && (buffer[i+1] != 0))
			{
				buffer[i] = buffer[i + 1];
				buffer[i + 1] = 0;
			}
		}

		return 0;
	}
	
	else
	{
		printf("Error. Could not remove item from front.\n");
		return -1;
	}
} 

void *
producer_wrapper(void *param) 
{ 
	long threadId = pthread_self();
	printf("%ld is producing\n", threadId);

	buffer_item item;
	int retval;

	while (1) 
	{ 
		/* sleep for a random period of time */ 
		int randInt = rand() % 5;
		sleep(randInt); 

		pthread_mutex_t mutex;
		/* create the mutex lock */
		pthread_mutex_init(&mutex,NULL);

		/* acquire the mutex lock */
		pthread_mutex_lock(&mutex);

		// call insert item
		retval = insert_item(item);
		printf("Buffer Size: %d Front: %d Back: %d \n", buffSize, buffer[0], buffer[buffSize]);

		/* release the mutex lock */
		pthread_mutex_unlock(&mutex);

		/* generate a random number */ 
		int item = rand(); 
		if (retval) 
		{
			printf("report error condition\n"); 
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
	long threadId = pthread_self();
	printf("%ld is consuming\n", threadId);

	buffer_item item;
	int retval;

	while (1) 
	{ 
		/* sleep for a random period of time */ 
		int randInt = rand() % 5;
		sleep(randInt); 

		pthread_mutex_t mutex;
		/* create the mutex lock */
		pthread_mutex_init(&mutex,NULL);

		/* acquire the mutex lock */
		pthread_mutex_lock(&mutex);

		// call remove item
		retval = remove_item(&item); 
		printf("Buffer Size: %d Front: %d Back: %d \n", buffSize, buffer[0], buffer[buffSize]);

		/* release the mutex lock */
		pthread_mutex_unlock(&mutex);

		if (retval)
		{
			printf("report error condition\n"); 
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

	srand(time(NULL));   // should only be called once, this is to make randint

	if (argc < 2)
	{
		printf("Needs some arguments.\n");
		printf("First: sleep time in seconds.\n");
		printf("Second: Number of producer threads.\n");
		printf("Third: Number of consumer threads\n");
		return 1;
	}

	// Step 1
	int sleepTime = atoi(argv[1]);
	int prodThreads = atoi(argv[2]);
	int consThreads = atoi(argv[3]);

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