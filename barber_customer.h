#ifndef BARBER_CUSTOMER_HD
#define BARBER_CUSTOMER_HD

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "semaphore.h"

#define CUSTOMERS 8
#define BARBERS 2
#define CHAIRS 5

/* synchronization variables */
extern semaphore_t* customerSem;
extern semaphore_t* barberSem;
extern pthread_mutex_t waitingMutex;
extern unsigned short kill_barbers;

/* data members */
extern pthread_t threads[BARBERS + CUSTOMERS];
extern int customers_waiting;

/* joint funcitons */
void* barber(void* tid);
void* customer(void* tid);


#endif
