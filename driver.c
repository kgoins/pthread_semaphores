#include <errno.h>
#include <string.h>
#include "barber_customer.h"

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
    for (i = BARBERS-1; i < (CUSTOMERS + BARBERS)-1; i++) {
        if ( pthread_create(&threads[i], NULL, customer, (void*) i) ) {
            printf("Error creating customer %d\n", i);
            exit(-1);
        } else {
            printf("Created customer %d\n", i);
        }
    }
}

void threadController() {
    int i; /* loop var */

    /* join customer threads */
    for (i = BARBERS-1; i < (BARBERS + CUSTOMERS)-1; i++) {
        int error = pthread_join(threads[i], NULL);
        if ( error ) {
            printf("ERROR: %s, joining customer: %d\n", strerror(errno),i);
            exit(-1);
        } else printf("Joined customer %d\n", i);
    }

    printf("All customers finished, setting kill_barbers\n");
    kill_barbers = 1;
    pthread_cond_broadcast(&customerSem->cond);

    /* wait for barbers to die */
    for (i = 0; i < BARBERS-1; i++) {
        int error = pthread_join(threads[i], NULL);
        if ( error ) {
            printf("ERROR: %s, when joining barber: %d\n", strerror(errno),i);
            break;
        } else printf("Joined barber %d\n", i);
    }

    printf("All threads have been terminated\n");
}

/* include sync vars for initialization */
    semaphore_t* barberSem;
    semaphore_t* customerSem;
    pthread_mutex_t waitingMutex;

    int customers_waiting;
    unsigned short kill_barbers;

    pthread_t threads[BARBERS + CUSTOMERS];


int main (int argc, char const* argv[]) {

    /* init sync vars */
    barberSem = createSem(BARBERS);
    customerSem = createSem(0);
    pthread_mutex_init(&waitingMutex, NULL);

    customers_waiting = 0;
    kill_barbers = 0;

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
