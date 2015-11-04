#include "barber_customer.h"

void get_haircut () {
    printf("A customer is finished getting a haircut\n");
}

void cut_hair () {
    printf("A Barber is finished cutting hair\n");
}

void* barber(void* tid) {
    while ( true ) {
        down(customerSem);
        if (kill_barbers == 1) break;

        pthread_mutex_lock(&waitingMutex);
        --customers_waiting;

        up(barberSem);
        pthread_mutex_unlock(&waitingMutex);

        cut_hair();
    }

    printf("Barber exiting\n");
    pthread_exit(NULL);
}

void* customer(void* tid) {
    pthread_mutex_lock(&waitingMutex);
    printf("Hi I'm customer %d\n",tid);

    if (customers_waiting < CHAIRS) { /* if barber shop !full */
        ++customers_waiting;
        up(customerSem);
        pthread_mutex_unlock(&waitingMutex);

        down(barberSem);
        get_haircut();
    } 
    else {
        printf("Shop is full\n");
        pthread_mutex_unlock(&waitingMutex);
    }

    printf("Customer %d exiting\n", tid);
    pthread_exit(NULL);
}
