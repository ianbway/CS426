// Ian Braudaway
// CS426 Chapter 3 Programming Project 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */


void  
parse(char *line, char **argv)
{
    while (*line != '\0') /* if not the end of line */ 
    {       
        while (*line == ' ' || *line == '\t' || *line == '\n')
        {
            *line++ = '\0'; /* replace white spaces with 0 */
        }

        *argv++ = line; /* save the argument position */

        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
        {
            line++; /* skip the argument until */
        }
    }

    *argv = '\0'; /* mark the end of argument list  */
}

void  
execute(char **argv)
{
	/**
	* After reading user input, the steps are:
	* (1) fork a child process using fork()
	* (2) the child process will invoke execvp()
	* (3) if command included &, parent will not invoke wait()
	*/

    pid_t pid;
    int status;
     
    if ((pid = fork()) < 0) /* fork a child process */
    {     
        fprintf(stderr, "Fork Failed\n");
 		return 1;
    }

    else if (pid == 0) /* for the child process: */
    {          
        if (execvp(*argv, argv) < 0) /* execute the command  */
        {     
            printf("Exec failed\n");
            return 1;
        }
    }

    else 
    {                                  /* for the parent: */
        while (wait(&status) != pid)       /* wait for completion  */
               ;
    }
}

int 
main(int argc, char **argv)
{
	char *args[MAX_LINE/2 + 1]; /* command line arguments */
	int should_run = 1; /* flag to determine when to exit program */
	
	char line[1024];

	while (should_run) 
	{
		printf("osh>");
		fflush(stdout);

		gets(line);

		parse(line, args); /* parse the line */
        if (strcmp(args[0], "exit") == 0)  /* is it an "exit"? */
		{
			exit(0); /* exit if it is */
		}
               
        execute(args); /* otherwise, execute the command */
	}

	return 0;
}