#include "readerwriter.h"

Semaphore mutex, rw_mutex, write_lock;
int readCount = 0;
// Helper functions from lectures
int* createArgs(int i) {
    int* args=newInt(1); args[0]=i; return args;
}

Thread createThread(void* threadFunction, void* args) {
    Thread thread; pthread_create (&thread, NULL, threadFunction, args);
    return thread;
}
void joinThreads(Thread* threads, int count) {
    int i; for(i=0; i<count; i++)joinThread(threads[i]);
}

void reading_writing() {
    int x=0, j=0, i = 0, T = rand() % 10000;
    for(i = 0; i < T; i++) for(j = 0; j < T; j++) x=i*j;
}

void init_semaphores(){
    // Initialize all semaphores
    init(mutex, 1);
    init(rw_mutex, 1);
    init(write_lock, 1);

}
// Acquire write lock
void lock_write(){
    wait(write_lock);
    wait(rw_mutex);
}
// Release write lock
void unlock_write() {
    signal(rw_mutex);
    signal(write_lock);
}
// Acquire read lock
void lock_read() {
    wait(write_lock);
    wait(mutex);
    readCount++;
    if (readCount == 1) {
        wait(rw_mutex);
    }

    signal(mutex);

    signal(write_lock);
}
// Release read lock
void unlock_read(){
    wait(mutex);
    readCount--;
    if(readCount == 0) {
        signal(rw_mutex);
    }
    signal(mutex);
}



