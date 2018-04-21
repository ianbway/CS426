// Ian Braudaway
// CS426-001
// Assignment 5 Virtual Memory Manager LRU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

#define PAGESIZE 256
#define PAGEENTRIES 256
#define PAGEBITNUM 8
#define FRAMESIZE 256
#define FRAMEENTRIES 256
#define MEMORYSIZE (FRAMESIZE * FRAMEENTRIES) // 32768
#define TLBENTRIES 16

int virtual;
int pageNumber;
int offset;
int physical;
int frameNumber;
int value;
int pageTable[PAGEENTRIES];
int tlb[TLBENTRIES][2];
int frontTLB = -1;
int backTLB = -1;
char memory[MEMORYSIZE];
int memoryIndex = 0;

int faultCounter = 0;
int tlbCounter = 0;
int addressCounter = 0;
float faultRate;
float tlbRate;

int getPhysical(int virtual);
int getOffset(int virtual);
int getPageNum(int virtual);
void initPageTable(void);
void initTLB(void);
int consultPT(int pageNumber);
int consultTLB(int pageNumber);
void updateTLB(int pageNumber, int frameNumber);
int getFrame();

int main(int argc, char *argv[]) 
{
    // File variables.
    char* inputFile;
    char* backingStoreFile;
    char* outputFile;
    char* backingStoreData;
    int backingStoreFD;
    char line[8];
    FILE* inputPointer;
    FILE* outputPointer;

    initTLB();
    initPageTable();

    // Making sure command line arguments are in the correct form.
    if (argc != 4) 
    {
        printf("Enter address file as first argument. Backing store as second. Output file is third. Nothing more or less.\n");
        exit(1);
    }

    else 
    {
        inputFile = argv[1];
        backingStoreFile = argv[2];
        outputFile = argv[3];

        // Does input file exist?
        if ((inputPointer = fopen(inputFile, "r")) == NULL) 
        {
            printf("Input file could not be opened.\n");
            exit(1);
        }

        // Does output file exist?
        if ((outputPointer = fopen(outputFile, "a")) == NULL) 
        {
            printf("Output file could not be opened.\n");
            exit(1);
        }

        // Open the backing store file, map the backing store to memory, and init the file descriptor.
        backingStoreFD = open(backingStoreFile, O_RDONLY);
        backingStoreData = mmap(0, MEMORYSIZE, PROT_READ, MAP_SHARED, backingStoreFD, 0);
        // Make sure mmap call succeeded. 
        if (backingStoreData == MAP_FAILED) 
        {
            close(backingStoreFD);
            printf("Mapping backing store failed.\n");
            exit(1);
        }

        // Start reading lines from input file.
        while (fgets(line, sizeof(line), inputPointer)) 
        {
            // Found an address.
            virtual = atoi(line);
            addressCounter++;

            // Get the pageNumber and offset from the virtual address.
            pageNumber = getPageNum(virtual);
            offset = getOffset(virtual);

            frameNumber = consultTLB(pageNumber);

            if (frameNumber != -1) 
            {
                physical = frameNumber + offset;
                value = memory[physical];
            }

            else 
            {
                // TLB lookup failed. 
                frameNumber = consultPT(pageNumber);
                if (frameNumber != -1) 
                {
                    physical = frameNumber + offset;
                    updateTLB(pageNumber, frameNumber);
                    value = memory[physical];
                }

                else 
                {
                    // Page fault.
                    int page_address = pageNumber * PAGESIZE;

                    if (memoryIndex != -1) 
                    {
                        memcpy(memory + memoryIndex, backingStoreData + page_address, PAGESIZE);
                        frameNumber = memoryIndex;
                        physical = frameNumber + offset;
                        value = memory[physical];
                        pageTable[pageNumber] = memoryIndex;
                        updateTLB(pageNumber, frameNumber);

                        if (memoryIndex < MEMORYSIZE - FRAMESIZE) 
                        {
                            memoryIndex += FRAMESIZE;
                        }

                        else 
                        {
                            memoryIndex = -1;
                        }
                    }

                    else 
                    {
                        // Failed, no free frame in memory exists. Swap. 
                    }
                }
            }

            // Print address information.
            fprintf(outputPointer, "Virtual address: %d ", virtual);
            fprintf(outputPointer, "Physical address: %d ", physical);
            fprintf(outputPointer, "Value: %d\n", value);
        }

        // Statistics math.
        faultRate = (float) faultCounter / (float) addressCounter;
        tlbRate = (float) tlbCounter / (float) addressCounter;

        // Print required statistics at end of file.
        fprintf(outputPointer, "Number of Translated Addresses = %d\n", addressCounter);
        fprintf(outputPointer, "Page Faults = %d\n", faultCounter);
        fprintf(outputPointer, "Page Fault Rate = %.3f\n", faultRate);
        fprintf(outputPointer, "TLB Hits = %d\n", tlbCounter);
        fprintf(outputPointer, "TLB Hit Rate = %.3f\n", tlbRate);

        // Close files.
        fclose(inputPointer);
        fclose(outputPointer);
        close(backingStoreFD);
    }

    return 0;
}

// Calculate and return the physical address. 
int getPhysical(int virtual) 
{
    physical = getPageNum(virtual) + getOffset(virtual);
    return physical;
}

// Calculate and return the page number. 
int getPageNum(int virtual) 
{
    return (virtual >> PAGEBITNUM);
}

// Calculate and return the offset value. 
int getOffset(int virtual) 
{
    int mask = 255;
    return virtual & mask;
}

// Sets all pageTable elements to -1. 
void initPageTable(void) 
{
    for (int i = 0; i < PAGEENTRIES; i++) 
    {
        pageTable[i] = -1;
    }
}

// Sets all TLB elements to -1. 
void initTLB(void) 
{
    for (int i = 0; i < TLBENTRIES; i++) 
    {
        tlb[i][0] = -1;
        tlb[i][1] = -1;
    }
}

// Takes a pageNumber and checks within the Page Table for a corresponding frame number. 
int consultPT(int pageNumber) 
{
    if (pageTable[pageNumber] == -1) 
    {
        faultCounter++;
    }

    return pageTable[pageNumber];
}

// Takes a pageNumber and checks within the TLB for a corresponding frame number. 
int consultTLB(int pageNumber) 
{
    // If pageNumber is found, return the corresponding frame number. 
    for (int i = 0; i < TLBENTRIES; i++) 
    {
        if (tlb[i][0] == pageNumber) 
        {
            // TLB hit
            tlbCounter++;

            return tlb[i][1];
        }
    }

    // If pageNumber doesn't exist in TLB, return -1. 
    // TLB miss
    return -1;
}

void updateTLB(int pageNumber, int frameNumber) 
{
    
    // FIFO
    if (frontTLB == -1) 
    {
        // Set front and back indices to 0.
        frontTLB = 0;
        backTLB = 0;

        // Update TLB with page number and frame number.
        tlb[backTLB][0] = pageNumber;
        tlb[backTLB][1] = frameNumber;
    }
    
    
    else 
    {
        // Use circular array method to implement queue.
        frontTLB = (frontTLB + 1) % TLBENTRIES;
        backTLB = (backTLB + 1) % TLBENTRIES;

        // Insert new TLB entry in the back of the circulary array. 
        tlb[backTLB][0] = pageNumber;
        tlb[backTLB][1] = frameNumber;
    }

    return;
}