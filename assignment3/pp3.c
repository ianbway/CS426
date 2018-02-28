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

#define BUFFER_SIZE 5

/* the buffer */ 
typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];

int counter = 0;
int in = 0;
int out = 0;

int insert_item(buffer_item);
int remove_item(buffer_item *);
void *producer_wrapper(void *);
void *consumer_wrapper(void *);

sem_t mutex;
sem_t empty;
sem_t full;

int 
insert_item(buffer_item item) 
{ 
	/* insert item into buffer return 0 if successful, otherwise return -1 indicating an error condition */ 

	long threadId = pthread_self();
	printf("Thread: %ld is Producing %d\n", threadId, item);

	printf("Thread: %ld Before Wait.\n", threadId);
	sem_wait(&empty);
	sem_wait(&mutex);
	printf("Thread: %ld After Wait.\n", threadId);
 	buffer[in] = item;
 	in = (in + 1) % BUFFER_SIZE;
 	counter++;
 	printf("Thread: %ld Before Signal.\n", threadId);
 	sem_post(&mutex);
 	int sig = sem_post(&full);

 	printf("Thread: %ld After Signal.\n", threadId);
 	printf("Thread: %ld Buffer Size: %d\n", threadId, counter);

 	if (sig)
 	{
 		return -1;
 	}

 	return 0;
} 

int 
remove_item(buffer_item *item) 
{ 
	/* remove an object from buffer placing it in item return 0 if successful, otherwise return -1 indicating an error condition */ 

	long threadId = pthread_self();
	printf("Thread: %ld is Consuming %d\n", threadId, *item);

	printf("Thread: %ld Before Wait.\n", threadId);
	sem_wait(&full);
	sem_wait(&mutex);
	printf("Thread: %ld After Wait.\n", threadId);
 	*item = buffer[out];
 	out = (out + 1) % BUFFER_SIZE;
 	counter--;
 	printf("Thread: %ld Before Signal.\n", threadId);
 	sem_post(&mutex);
 	int sig = sem_post(&empty);
	/* consume the item in next consumed */


 	printf("Thread: %ld After Signal.\n", threadId);
	printf("Thread: %ld Buffer Size: %d\n", threadId, counter);

	if (sig)
	{
		return -1;
	}

	return 0;
} 

void *
producer_wrapper(void *param) 
{ 

	buffer_item item;
	int retval;

	while (1) 
	{ 
		/* sleep for a random period of time */ 
		int randInt = rand() % 5;
		sleep(randInt); 

		/* generate a random number */ 
		int item = rand(); 

		// call insert item
		retval = insert_item(item);

		if (retval) 
		{
			printf("Error in producer_wrapper\n"); 
		}
	}

    pthread_exit(0);
} 

void *
consumer_wrapper(void *param) 
{ 
	buffer_item item;
	int retval;

	while (1) 
	{ 
		/* sleep for a random period of time */ 
		int randInt = rand() % 5;
		sleep(randInt); 

		// call remove item
		retval = remove_item(&item); 

		if (retval)
		{
			printf("Error in consumer_wrapper\n"); 
		} 
	}

	pthread_exit(0);
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

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);

	if (argc != 4)
	{
		printf("Invalid number of arguments.\n");
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