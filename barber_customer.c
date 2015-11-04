#include "barber_customer.h"

static int customers_waiting = 0;


void get_haircut () {
    printf("A customer is getting a haircut\n");
    usleep(200);
    printf("A customer is finished getting a haircut\n");
}

void cut_hair () {
    printf("A Barber is cutting hair\n");
    usleep(200);
    printf("A Barber is finished cutting hair\n");
}

void* barber(void* tid) {
    while (!kill_barbers) {
        down(customerSem);
        pthread_mutex_lock(&waitingMutex);
        --customers_waiting;
        up(barberSem);
        pthread_mutex_unlock(&waitingMutex);

        cut_hair();
    }

    pthread_exit(NULL);
}

void* customer(void* tid) {
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
