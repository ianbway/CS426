// Ian Braudaway
// CS426-001 Assignment 2
// Problem 3.20, Header File

#define MIN_PID 300
#define MAX_PID 5000

int map[MAX_PID-MIN_PID];

int allocate_map();

int allocate_pid();

void release_pid(int pid);