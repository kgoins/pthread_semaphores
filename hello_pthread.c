/* hello-pthread.c
** 
** Demonstrates creating & joining Pthreads
**
** By Dave Small
** For COP 4600
** 200607.04 - v1.0: created
**
** This code was based upon hello.c by Blaise Barney (LAST REVISED: 04/05/05)
** which is a part of his POSIX Threads Programming tutorial found at
** http://www.llnl.gov/computing/tutorials/pthreads/
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	5

void * printHello( void *threadID )
{
  int i;

  for ( i = 0; i < 5; ++i )
  {
    printf( "Thread %d says: Hello!\n", threadID );
    usleep( random() & 0x0000FFFF );
  }

  printf( "Thread %d says: Goodbye!\n", threadID );
  pthread_exit( NULL );
}

int main( void )
{
  pthread_t thread[NUM_THREADS];
  int i;

  for ( i = 0; i < NUM_THREADS; ++i )
  {

    // make the threads
    if( pthread_create( &thread[i], NULL, printHello, (void *)i ) )
    {
      printf( "ERROR: creating thread %d\n", i );
      exit(-1);
    }
    else
    {
      printf( "Created thread %d\n", i );
    }
  }

  // wait for the threads to terminate
  for ( i = 0; i < NUM_THREADS; ++i )
  {
    if ( pthread_join( thread[i], NULL ) )
    {
      printf("ERROR: joining thread %d\n", i );
    }
    else
    {
      printf("Joined thread %d\n", i );
    }
  }

 return 0; 
}
