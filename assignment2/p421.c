// Ian Braudaway
// CS426-001 Assignment 2
// Problem 4.21, Implementation File

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int n;

void *
average_wrapper(void *args)
{
    int retval = average(args);

    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

void *
maximum_wrapper(void *args)
{
    int retval = maximum(args);

    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

void *
minimum_wrapper(void *args)
{
    int retval = minimum(args);

    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

// Function to find average of array values
int 
average(int input[n])
{
	int sum = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		sum = sum + input[i];
	}
	int average = sum / n;
	
	printf("The average value is %d\n", average);
}

// Function for max value in array
int 
maximum(int input[n])
{
	int maximum = input[0];
	int i;
	for (i = 0; i < n; i++)
  	{
    	if (input[i] > maximum)
    	{
       		maximum  = input[i];
    	}
	}

	printf("The maximum value is %d\n", maximum);
}

// Function for min value in array
int 
minimum(int input[n])
{
	int minimum = input[0];
	int i;
	for (i = 0; i < n; i++)
  	{
    	if (input[i] < minimum)
    	{
       		minimum  = input[i];
    	}
	}

	printf("The minimum value is %d\n", minimum);
}

int 
main(int argc, char **argv)
{
	printf("Enter the number of elements: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Error! number should be greater than 0.\n");
        printf("Enter the number again: ");
        scanf("%d", &n);
    }

    int valArray[n];

    int i;
    for(i = 0; i < n; ++i)
    {
        printf("%d. Enter number: ", i+1);
        scanf("%d", &valArray[i]);
    }

	pthread_t thr;

	pthread_create(&thr,NULL,average_wrapper,valArray);
	pthread_create(&thr,NULL,maximum_wrapper,valArray);
	pthread_create(&thr,NULL,minimum_wrapper,valArray);
}