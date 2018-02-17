# Ian Braudaway
# CS426-001 Makefile for Assignment 2
DA_OBJS = integer.o real.o string.o da.o
CDA_OBJS = integer.o real.o string.o cda.o
STACK_OBJS = integer.o real.o string.o da.o stack.o
QUEUE_OBJS = integer.o real.o string.o cda.o queue.o
BST_OBJS = integer.o real.o string.o bst.o test-bst.o
MATILDA_OBJS = integer.o real.o string.o scanner.o da.o cda.o stack.o queue.o bst.o matilda.o 
OPTS = -Wall -Wextra -std=c99 -g -c 
LOPTS = -Wall -Wextra -std=c99 -g
CC = gcc

all : matilda

matilda : $(MATILDA_OBJS)
	$(CC) $(LOPTS) $(MATILDA_OBJS) -lm -o matilda

test-bst : $(BST_OBJS)
	$(CC) $(LOPTS) $(BST_OBJS) -o test-bst

matilda.o : matilda.c
	$(CC) $(OPTS) -lm matilda.c

scanner.o : scanner.c scanner.h
	$(CC) $(OPTS) scanner.c

real.o : real.c real.h
	$(CC) $(OPTS) real.c 
	
integer.o : integer.c integer.h
	$(CC) $(OPTS) integer.c

string.o : string.c string.h
	$(CC) $(OPTS) string.c

da.o : da.c da.h
	$(CC) $(OPTS) da.c

cda.o : cda.c cda.h
	$(CC) $(OPTS) cda.c

stack.o : stack.c stack.h
	$(CC) $(OPTS) stack.c

queue.o : queue.c queue.h
	$(CC) $(OPTS) queue.c

bst.o : bst.c bst.h
	$(CC) $(OPTS) bst.c

clean :
	rm -f $(DA_OBJS) $(STACK_OBJS) $(CDA_OBJS) $(QUEUE_OBJS) $(BST_OBJS) $(MATILDA_OBJS) ./test-bst ./matilda ./matilda.o

test :
	./matilda yourcode-0-1 > mytestoutput1
	diff correcttestoutput1 mytestoutput1
	./matilda -i yourcode-0-2 > mytestoutput2
	diff correcttestoutput2 mytestoutput2
	./matilda -p yourcode-0-3 > mytestoutput3
	diff correcttestoutput3 mytestoutput3
	./matilda -b yourcode-0-4 > mytestoutput4
	diff correcttestoutput4 mytestoutput4
	./matilda -p -i -b yourcode-0-5 > mytestoutput5
	diff correcttestoutput5 mytestoutput5
	./matilda -p -b -i yourcode-0-6 > mytestoutput6
	diff correcttestoutput6 mytestoutput6
	./matilda -p -i -b yourcode-0-7 > mytestoutput7
	diff correcttestoutput7 mytestoutput7
	./matilda yourcode-0-8 > mytestoutput8
	diff correcttestoutput8 mytestoutput8
	./matilda -p -b yourcode-0-9 > mytestoutput9
	diff correcttestoutput9 mytestoutput9
	./matilda -p yourcode-0-10 > mytestoutput10
	diff correcttestoutput10 mytestoutput10
	./matilda -p yourcode-0-11 > mytestoutput11
	diff correcttestoutput11 mytestoutput11
	./matilda -p yourcode-0-12 > mytestoutput12
	diff correcttestoutput12 mytestoutput12
	./matilda -p yourcode-0-13 > mytestoutput13
	diff correcttestoutput13 mytestoutput13
	./matilda -p yourcode-0-14 > mytestoutput14
	diff correcttestoutput14 mytestoutput14
	./matilda -i -p -b input.txt
	./matilda -i -p -b mycode-0-1
	./matilda -i -p -b mycode-0-2
	./matilda -i -p -b mycode-0-3
	./matilda -i -p -b mycode-0-4
	./matilda -i -p -b mycode-0-5
	./matilda -i -p -b mycode-0-6
	./matilda -i -p -b mycode-0-7
	./matilda -i -p -b mycode-0-8
	./matilda -i -p -b yourcode-0-1
	./matilda -i -p -b yourcode-0-2
	./matilda -i -p -b yourcode-0-3
	./matilda -i -p -b yourcode-0-4
	./matilda -i -p -b yourcode-0-5
	./matilda -i -p -b yourcode-0-6
	./matilda -i -p -b yourcode-0-7
	./matilda -i -p -b yourcode-0-8
	./matilda -i -p -b yourcode-0-9
	./matilda -i -p -b yourcode-0-10
	./matilda -i -p -b yourcode-0-11
	./matilda -i -p -b yourcode-0-12
	./matilda -i -p -b yourcode-0-13
	./matilda -i -p -b yourcode-0-14
