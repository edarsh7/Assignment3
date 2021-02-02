
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t junction[5];


void *arrive_manager(void *arg)
{
  int junct = *(int *)arg;
  sem_wait(&junction[junct]);
  sem_wait(&junction[junct+1]);
}

/*
 * You need to implement this function, see cartman.h for details 
 */
void arrive(unsigned int cart, enum track track, enum junction junction) 
{
  pthread_t thread;
  int junct = (int) junction;
  pthread_create(&thread, NULL, arrive_manager, (void)* junct);
  pthread_join(&thread, NULL);
}

/*
 * You need to implement this function, see cartman.h for details 
 */
void depart(unsigned int cart, enum track track, enum junction junction) 
{
}


/*
 * You need to implement this function, see cartman.h for details 
 */
void cartman() 
{
  for(int i=0; i < 5; i++)
  {
    sem_init(&junction[i], 0, 1);
  }
}
