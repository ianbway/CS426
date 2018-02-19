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
int average;
int maximum;
int minimum;

int average_value(int []);
int maximum_value(int []);
int minimum_value(int []);

void *
average_wrapper(void *args)
{
    int retval = average_value(args);

    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

void *
maximum_wrapper(void *args)
{
    int retval = maximum_value(args);

    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

void *
minimum_wrapper(void *args)
{
    int retval = minimum_value(args);

    int *ret = malloc(sizeof(int));
    *ret = retval;
    return ret;
}

// Function to find average of array values
int 
average_value(int input[])
{
	int sum = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		sum = sum + input[i];
	}
	average = sum / n;
}

// Function for max value in array
int 
maximum_value(int input[])
{
	maximum = input[0];
	int i;
	for (i = 0; i < n; i++)
  	{
    	if (input[i] > maximum)
    	{
       		maximum  = input[i];
    	}
	}
}

// Function for min value in array
int 
minimum_value(int input[])
{
	minimum = input[0];
	int i;
	for (i = 0; i < n; i++)
  	{
    	if (input[i] < minimum)
    	{
       		minimum  = input[i];
    	}
	}
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
    for(i = 0; i < n; i++)
    {
        printf("%d. Enter number: ", i+1);
        scanf("%d", &valArray[i]);
    }

	pthread_t average_thr;
	pthread_t maximum_thr;
	pthread_t minimum_thr;

	pthread_create(&average_thr,NULL,average_wrapper,valArray);
	pthread_create(&maximum_thr,NULL,maximum_wrapper,valArray);
	pthread_create(&minimum_thr,NULL,minimum_wrapper,valArray);

	printf("The average value is %d\n", average);
	printf("The maximum value is %d\n", maximum);
	printf("The minimum value is %d\n", minimum);
}