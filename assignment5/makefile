# Ian Braudaway
# CS426-001
# Makefile for Assignment 5 Virtual Memory Manager

VMM_OBJS = string.o scanner.o da.o vmm.o
DA_OBJS = string.o da.o
OPTS = -Wall -Wextra -std=c99 -g -c 
LOPTS = -Wall -Wextra -std=c99 -g
CC = gcc

all : vmm

vmm : $(VMM_OBJS)
	$(CC) $(LOPTS) $(VMM_OBJS) -o vmm

vmm.o : vmm.c 
	$(CC) $(OPTS) vmm.c	

scanner.o : scanner.c scanner.h
	$(CC) $(OPTS) scanner.c

string.o : string.c string.h
	$(CC) $(OPTS) string.c

da.o : da.c da.h
	$(CC) $(OPTS) da.c

clean :
	rm -f $(DA_OBJS) $(VMM_OBJS) ./vmm

test :
	./vmm addresses.txt
