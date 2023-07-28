#ifndef READERWRITER_H
#define READERWRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define Thread pthread_t
#define Semaphore sem_t
#define exitThreads() pthread_exit(NULL)
#define newInt(n) (int*)malloc(sizeof(int)*n)
#define wait(semaphore) sem_wait(&semaphore)
#define signal(semaphore) sem_post(&semaphore)
#define joinThread(thread) pthread_join(thread, NULL)
#define init(semaphore, value) sem_init(&semaphore, 0, value)

// function prototypes

int* createArgs(int i);
Thread createThread(void* threadFunction, void* args);
void joinThreads(Thread* threads, int count);
void init_semaphores();
void reading_writing();
void lock_write();
void unlock_write();
void lock_read();
void unlock_read();

#endif