#include <stdio.h>
#include <stdlib.h>
#include "semaphore.h"

#define CUSTOMERS 10
#define BARBERS 2
#define CHAIRS 5

typedef enum {false, true} bool;

semaphore_t* barberSem;
semaphore_t* customerSem;

void* barber(void* threadID) {
    while (true) {
        down(customerSem);
    }

}
void* customer(void * threadID);


int main (int argc, char const* argv[]) {
    barberSem = createSem(BARBERS);
    customerSem = createSem(CUSTOMERS);

    /* create threads */
    int i; /* loop variable */
    pthread_t threads[BARBERS + CUSTOMERS];

    /* spin barber threads */
    for (i = 0; i < BARBERS; i++) {
        if ( pthread_create(&threads[i], NULL, barber, (void*) i) ) {
            printf("Error creating barber %d, i");
            exit(-1);
        } else {
            printf("Created barber %d, i");
        }
    }
    /* spin customer threads */
    for (i = BARBERS; i < CUSTOMERS; i++) {
        if ( pthread_create(&threads[i], NULL, customer, (void*) i) ) {
            printf("Error creating barber %d, i");
            exit(-1);
        } else {
            printf("Created barber %d, i");
        }
    }


    /* destroy semaphores */
    destroySem(barberSem);
    destroySem(customerSem);

    return 0;
}
