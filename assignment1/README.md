# CS426
Operating Systems
Ian Braudaway
Assignment 1

Part A) Compile assign1a.c with gcc. 
Then run executable with its first argument being the number "n" you wish to pass in. 
Make sure "n" is greater than or equal to 1. You must run again if it is not.

Part B) Compile assign1b.c with gcc.
Then run executable. You should be greeted with the shell tool, it should
look like: ">osh". From here run the command line arguments you wish to run.
If "history" is entered and executed, the command history will be output up to 10.
If "!!"" is entered and executed, the most recent command from history is executed.
If "!N" is entered and executed, the Nth command in history is executed. N goes up to 10.
If the command includes "&", the parent fork will not invoke "wait()".
Type in "exit" to leave the program.