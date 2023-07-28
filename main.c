#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "readerwriter.h"

void *writer(void *args) {

    int writerID=((int*)args)[0];

    printf("Writer[%d] is created..\n", writerID);
    // Aqcuire write lock
    lock_write();

    printf("Writer[%d] is writing\n", writerID);
    // Perform operation
    reading_writing();

    printf("Writer[%d] finished writing\n", writerID);
    // Release write lock
    unlock_write();
    
    return NULL;
    
}

void *reader(void *args) {
    
    int readerID=((int*)args)[0];
    printf("Reader[%d] is created..\n", readerID);
    //Acquire read lock
    lock_read();

    printf("Reader[%d] is reading\n", readerID);
    // Perform operation
    reading_writing();

    printf("Reader[%d] finished reading\n", readerID);
    // Release read lock
    unlock_read();

    return NULL;
}

int main()
{

    // Open file
    FILE *file = fopen("scenarios.txt", "r");
    if (file == NULL){

        printf("Unable to open file.\n");
        return 0;
    }
    // 2-dimensional array storing up to 20 scenarios with up to 15 readers or writers
    char scenarios[20][16];

    // Count number of scenarios in file while storing them
    int nScenarios = 0;

    // Read up to the total 20 scenarios
    while (nScenarios < 20 && fgets(scenarios[nScenarios], 16, file) != NULL) {

        // Remove newline character from end of each scenario
        int len = strlen(scenarios[nScenarios]);
        if (len > 0 && scenarios[nScenarios][len - 1] == '\n') {
            scenarios[nScenarios][len - 1] = '\0';
        }
        nScenarios++;
    }

    // Closing file
    fclose(file);

    // Variables and lock initialization
    char readerOrWriter;
    int readerID = 0, writerID = 0, i = 0, j = 0, k = 0;
    init_semaphores();

    if(file) {
        // Loop and go through each scenario
        for(i = 0; i < nScenarios; i++) {

            printf("\nStarting Scenario #%d:\n", i + 1);

            // Create threads for each reader or writer, max 15
            Thread threads[16];

            // Get numbers of readers and writers in current scenario to know number of threads created
            for(j = 0; j < strlen(scenarios[i]); j++){
               
                readerOrWriter = scenarios[i][j];

                if(readerOrWriter== 'r') {
                    int* id=createArgs(readerID++);
                    threads[j]=createThread(reader, id);
                }
                else if(readerOrWriter== 'w') {
                    int* id=createArgs(writerID++);
                    threads[j]=createThread(writer, id);
                }
                
            }
            // Join Threads and continue to next scenario
            joinThreads(threads, strlen(scenarios[i]));
            printf("\nFinished Scenario #%d\n", i + 1);
        }
    }

    
    else printf("Scenario file does not exist...\n");

     

    return 0;
}



