#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "semaphore.h"

#define CUSTOMERS 10
#define BARBERS 2
#define CHAIRS 5

semaphore_t* barberSem;
semaphore_t* customerSem;
pthread_mutex_t waitingMutex; 

static int customers_waiting = 0;


void get_haircut () {
    printf("A customer is getting a haircut\n");
    usleep(200);
}

void cut_hair () {
    printf("A Barber is cutting hair\n");
    usleep(200);
}


void* barber(void* threadID) {
    while (true) {
        down(customerSem);
        pthread_mutex_lock(&waitingMutex);
        --customers_waiting;
        up(barberSem);
        pthread_mutex_unlock(&waitingMutex);

        cut_hair();
        
    }
}

void* customer(void * threadID) {
    pthread_mutex_lock(&waitingMutex);

    if (customers_waiting < CHAIRS) { /*if shop is full, leave*/
        ++customers_waiting;
        up(customerSem);
        pthread_mutex_unlock(&waitingMutex);
        down(barberSem);
        get_haircut();
    } else {
        pthread_mutex_unlock(&waitingMutex);
    }

    pthread_exit(NULL);
}


int main (int argc, char const* argv[]) {
    barberSem = createSem(BARBERS);
    customerSem = createSem(CUSTOMERS);
    pthread_mutex_init(&waitingMutex, NULL);

    /* create threads */
    int i; /* loop variable */
    pthread_t threads[BARBERS + CUSTOMERS];

    /* spin barber threads */
    for (i = 0; i < BARBERS; i++) {
        if ( pthread_create(&threads[i], NULL, barber, (void*) i) ) {
            printf("Error creating barber %d\n", i);
            exit(-1);
        } else {
            printf("Created barber %d\n", i);
        }
    }
    /* spin customer threads */
    for (i = BARBERS; i < CUSTOMERS; i++) {
        if ( pthread_create(&threads[i], NULL, customer, (void*) i) ) {
            printf("Error creating barber %d\n", i);
            exit(-1);
        } else {
            printf("Created barber %d\n", i);
        }
    }

    /* join threads */
    for (i = 0; i < (BARBERS + CUSTOMERS); i++) {
       if ( pthread_join(threads[i], NULL) ) {
           printf("ERROR joining thread: %d\n", i);
           exit(-1);
       } else {
           printf("Joined thread %d\n", i);
       }
    }

    /* destroy semaphores */
    pthread_mutex_destroy(&waitingMutex);
    destroySem(barberSem);
    destroySem(customerSem);

    return 0;
}
