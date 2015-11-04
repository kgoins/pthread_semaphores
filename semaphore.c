#include "semaphore.h"
#include "barber_customer.h"

semaphore_t* createSem ( int initCount ) {
    semaphore_t* newSem = (semaphore_t*) malloc(sizeof(semaphore_t));
    newSem->count = initCount;

    /* init synch vars */
    pthread_mutex_init(&newSem->mutex, NULL);
    pthread_cond_init(&newSem->cond, NULL);

    /* init queue */
    newSem->head = SIMPLEQ_HEAD_INITIALIZER(head);


    return newSem;
}

void destroySem (semaphore_t* targSem) {
    pthread_mutex_destroy(&targSem->mutex);
    pthread_cond_destroy(&targSem->cond);

    free(targSem);
}

void down (semaphore_t* sem) {
    printf("Count: %d\n", sem->count);
    pthread_mutex_lock(&sem->mutex);

    while (sem->count == 0) {
        printf("Thread is waiting\n");

        if (kill_barbers == 1) {
            printf("Kill signal caught\n");
            pthread_mutex_unlock(&sem->mutex);
            return;
        }
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }

    sem->count--;
    pthread_mutex_unlock(&sem->mutex);
}

void up (semaphore_t* sem) {
    pthread_mutex_lock(&sem->mutex);
    if (sem->count == 0) {
        sem->count++;
        pthread_cond_signal(&sem->cond);
    } else sem->count++;
    pthread_mutex_unlock(&sem->mutex);
}
