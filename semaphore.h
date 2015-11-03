#ifndef SEM_H
#define SEM_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;

} semaphore_t;

semaphore_t* createSem(int initCount);
void destroySem(semaphore_t* target);

void down(semaphore_t* sem);
void up(semaphore_t* sem);

#endif
