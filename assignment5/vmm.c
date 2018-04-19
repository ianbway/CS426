// Ian Braudaway
// CS426-001
// Assignment 5 Virtual Memory Manager

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "string.h"
#include "da.h"

int
main(int argc, char *argv[])
{
	int pageTable[256];
	int physical[256];
	int tlb[16];

	// Open First argument to read in addresses.txt
	FILE *fp = fopen(argv[1], "r");

	if (!fp)
	{
		printf("There is no file to read for the first argument.\n");
		exit(1);
	}

	// Read in addresses into a DA
	DA *addressArray = newDA(displaySTRING);
	char *token = readToken(fp);

	while (token)
	{
		insertDA(addressArray, newSTRING(token));
		token = readToken(fp);
	}

	int i;
	for (i=0; i < sizeDA(addressArray); i++)
	{
		printf("Virtual address: %s\n", getSTRING(getDA(addressArray, i)));
	}

	//displayDA(stdout, addressArray);
	
	return 0;
}