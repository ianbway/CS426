# Ian Braudaway
# CS426-001 Makefile for Assignment 2

420_OBJS = assign2_420.o 
320_OBJS = assign2_320.o test_320.o
OPTS = -Wall -Wextra -std=c99 -g -c 
LOPTS = -Wall -Wextra -std=c99 -g
CC = gcc

all : assign2_420

assign2_420 : assign2_420.o assign2_320.o
	$(CC) $(LOPTS) -pthread -o assign2_420 assign2_420.o assign2_320.o

test_320 : test_320.o assign2_320.o
	$(CC) $(LOPTS) -o test_320 test_320.o assign2_320.o

test_320.o : test_320.c assign2_320.h
	$(CC) $(OPTS) test_320.c

assign2_320.o : assign2_320.c assign2_320.h
	$(CC) $(OPTS) assign2_320.c

assign2_420.o : assign2_420.c assign2_320.h
	$(CC) $(OPTS) assign2_420.c

clean :
	rm -f $(320_OBJS) $(420_OBJS) ./test_320 ./assign2_420

test :
	./assign2_420