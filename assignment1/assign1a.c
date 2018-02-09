// Ian Braudaway
// CS426 Problem 3.21

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

 int 
 main(int argc, char **argv)
 {
	int n = atoi(argv[1]);

	// Negative input error test, or 0
	if (n < 1)
	{
		fprintf(stderr, "Please input positive integer.\n");
		return 1;
	}

	// Input 1, so output 1
	if (n == 1)
	{
		printf("%d\n", n);
		return 0;
	}

 	pid_t pid;

 	pid = fork();

 	// Negative fork error test
 	if (pid < 0) 
 	{
 		fprintf(stderr, "Fork Failed\n");
 		return 1;
 	}

 	// Child Process
 	else if (pid == 0)
 	{

 		printf("%d,", n);

 		while (n != 1)
 		{
 			// Even N
 			if ((n % 2) == 0)
    		{
    			n = n / 2;
    			// Not 1 needs a comma
    			if (n > 1)
    				printf("%d,", n);
    			// 1 does not need a comma afterwards, we have reached the end
    			else
    				printf("%d\n", n);
    		}

    		// Odd N
    		else
    		{
    			n = 3 * n + 1;
    			printf("%d,", n);
    		}
    	}
 	}

 	// Parent Process
 	else
 	{
 		wait(NULL);
 	}

 	return 0;
 }