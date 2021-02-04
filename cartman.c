
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

//global semaphores that keep track of the junctions and deadlock
sem_t junction[5];
sem_t deadlock;

//struct that keeps all of the cart info so our thread can access the information
typedef struct cart_info
{
  enum junction junction;
  enum track track;
  unsigned int cart;
}cart_info;


//this thread function will allow 2 threads in, then wait and reserve each junction necessary
//for the given track
void *arrive_manager(void *arg)
{
  cart_info *CART = (cart_info *)arg;

  sem_wait(&deadlock);

  sem_wait(&junction[(CART->track) % 5]);
  reserve(CART->cart, (CART->track) % 5);
  sem_wait(&junction[(CART->track + 1) % 5]);
  reserve(CART->cart, (CART->track + 1) % 5);

  cross(CART->cart, CART->track, CART->junction);
  return NULL;
}



/*
 * In our arrive function, it will allocate space to a given cart and its information and then create a thread
 * a thread with that carts info as an argument
 */
void arrive(unsigned int cart, enum track track, enum junction junction) 
{
  pthread_t thread;
  cart_info *CART = malloc(sizeof(cart_info));
  CART->cart = cart;
  CART->track = track;
  CART->junction = junction;

  pthread_create(&thread, NULL, arrive_manager, CART);
}

/*
 * depart will release and free up the junction semaphores for an individual call. 
 * remove the deadlock after 2 threads have departed.
 */
void depart(unsigned int cart, enum track track, enum junction junct) 
{
  release(cart, (track+1) % 5);
  sem_post(&junction[(track+1) % 5]);
  release(cart, (track) % 5);
  sem_post(&junction[(track) % 5]);

  sem_post(&deadlock);

}


/*
 * Cartman initializes the semaphores necessary for a) each individual junction and b) a way to avoid deadlock
 */
void cartman() 
{
  sem_init(&deadlock, 0, 2);

  for(int i=0; i < 5; i++)
  {
    sem_init(&junction[i], 0, 1);
  }

}


/*
For the deadlock test, i pass the test about 90% of the time, I'm not sure what the problem is but
it seems to be cutting it close to the 4.20 second time limit. Changing my deadlock semaphore initializer 
to anything more than 2 causes all the cartman tests to fail. Im not sure what is going on :( 
*/