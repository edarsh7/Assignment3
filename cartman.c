
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX MAX
//global semaphores that keep track of the junctions and deadlock
sem_t junction[MAX];
sem_t deadlock;

//struct that keeps all of the cart info so our thread can access the information
typedef struct cart_info
{
  enum junction junction;
  enum track track;
  unsigned int cart;
}cart_info;

void init_cart(unsigned int cart, enum track track, enum junction junction, struct cart_info * CART)
{
  CART->cart = cart;
  CART->track = track;
  CART->junction = junction;
}


//this thread function will allow 2 threads in, then wait and reserve each junction necessary
//for the given track
void *arrive_manager(void *arg)
{
  cart_info *CART = (cart_info *)arg;

  sem_wait(&deadlock);

  sem_wait(&junction[(CART->track) % MAX]);
  reserve(CART->cart, (CART->track) % MAX);
  sem_wait(&junction[(CART->track + 1) % MAX]);
  reserve(CART->cart, (CART->track + 1) % MAX);

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
  init_cart(cart, track, junction);

  pthread_create(&thread, NULL, arrive_manager, CART);
}

/*
 * depart will release and free up the junction semaphores for an individual call. 
 * remove the deadlock after 2 threads have departed.
 */
void depart(unsigned int cart, enum track track, enum junction junct) 
{
  release(cart, (track+1) % MAX);
  sem_post(&junction[(track+1) % MAX]);
  release(cart, (track) % MAX);
  sem_post(&junction[(track) % MAX]);

  sem_post(&deadlock);

}


/*
 * Cartman initializes the semaphores necessary for a) each individual junction and b) a way to avoid deadlock
 */
void cartman() 
{
  sem_init(&deadlock, 0, 2);

  for(int i=0; i < MAX; i++)
  {
    sem_init(&junction[i], 0, 1);
  }

}


/*
For the deadlock test, i pass the test about 90% of the time, I'm not sure what the problem is but
it seems to be cutting it close to the 4.20 second time limit. Changing my deadlock semaphore initializer 
to anything more than 2 causes all the cartman tests to fail. Im not sure what is going on :( 
*/