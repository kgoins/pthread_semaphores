#include <stdlib.h>
#include "semaphore.h"

semaphore_t* createSem (int initCount ) {
    semaphore_t* newSem = (semaphore_t*) malloc(sizeof(semaphore_t));
    newSem->count = initCount;

    /* init synch vars */
    pthread_mutex_init(&newSem->mutex, NULL);
    pthread_cond_init(&newSem->cond, NULL);

    return newSem;
}

void destroySem (semaphore_t* targSem) {
    pthread_mutex_destroy(&targSem->mutex);
    pthread_cond_destroy(&targSem->cond);

    free(targSem);
}

void down (semaphore_t* sem) {
    pthread_mutex_lock(&sem->mutex);
    --sem->count;
    while (sem->count == 0)
        pthread_cond_wait(&sem->cond, &sem->mutex);
    pthread_mutex_unlock(&sem->mutex);
}

void up (semaphore_t* sem) {
    pthread_mutex_lock(&sem->mutex);
    ++sem->count;
    while (sem->count)
        pthread_cond_wait(&sem->cond, &sem->mutex);
}
