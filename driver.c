#include "barber_customer.h"

static pthread_t threads[BARBERS + CUSTOMERS];

void createThreads() {
    int i; /* loop variable */

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
}

void threadController() {
    int i; /* loop var */
    /* join threads */
    for (i = 0; i < (BARBERS + CUSTOMERS); i++) {
        if ( pthread_join(threads[i], NULL) ) {
            printf("ERROR joining thread: %d\n", i);
            exit(-1);
        } else printf("Joined thread %d\n", i);
    }
}

int main (int argc, char const* argv[]) {
    /* init sync vars */
    barberSem = createSem(BARBERS);
    customerSem = createSem(CUSTOMERS);
    pthread_mutex_init(&waitingMutex, NULL);

    /* create threads */
    createThreads();
    
    /* join, clean up, and kill threads */
    threadController();

    /* destroy sync vars */
    pthread_mutex_destroy(&waitingMutex);
    destroySem(barberSem);
    destroySem(customerSem);

    return 0;
}
