#ifndef BARBER_CUSTOMER_HD
#define BARBER_CUSTOMER_HD

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "semaphore.h"

#define CUSTOMERS 10
#define BARBERS 2
#define CHAIRS 5

extern semaphore_t* customerSem;
extern semaphore_t* barberSem;
extern pthread_mutex_t waitingMutex;
extern unsigned short kill_barbers = 0;

void* barber(void* tid);
void* customer(void* tid);


#endif
