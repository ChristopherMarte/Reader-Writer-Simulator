Reader-Writer Non-starving locks program

This program demonstrates the functionality of the implemented reader-writer locks that do not produce starvation for readers or writers.
The program opens up scenarios.txt and stores each scenario in a 2-dimensional array. The program iterates through the array for each scenario and 
creates reader and writer threads, maximum of number of readers or writers being 15. The implemented locks allows multiple readers to read at the same time, but does not
allow readers or other writers to access the shared resource when a writer has acquired a lock. This is done by implementing 3 semaphore, which control reads, writes and mutual exclusion.

The program displays the read-write operations, making sure to give both readers and writers a far chance at performing their operations.

The executable file can be created by running the make command or alternatively running the compile statement: gcc -o rwmain main.c readerwriter.c -lpthread
This creates the rwmain executable, which can then be run by using the statement: ./rwmain 

If the program is ran using the above command, an example output will be:

Starting Scenario #1:
Reader[0] is created..
Reader[0] is reading
Reader[1] is created..
Reader[1] is reading
Reader[2] is created..
Reader[2] is reading
Writer[0] is created..
Reader[5] is created..
Reader[1] finished reading
Reader[4] is created..
Reader[6] is created..
Reader[3] is created..
Reader[2] finished reading
Reader[0] finished reading
Writer[0] is writing
Writer[0] finished writing
Reader[5] is reading
Reader[4] is reading
Reader[3] is reading
Reader[6] is reading
Reader[6] finished reading
Reader[3] finished reading
Reader[5] finished reading
Reader[4] finished reading

Finished Scenario #1
