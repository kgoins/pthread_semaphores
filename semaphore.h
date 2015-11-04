#ifndef SEM_H
#define SEM_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

typedef enum {false, true} bool;

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    SIMPLEQ_HEAD(queuehead,entry) head;
    pthread_t headTID;

} semaphore_t;

semaphore_t* createSem(int initCount);
void destroySem(semaphore_t* target);

void down(semaphore_t* sem);
void up(semaphore_t* sem);

#endif
