
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t junction[5];
pthread_t thread[5];
int thread_turn=0;

typedef struct cart_info
{
  enum junction junction;
  enum track track;
  unsigned int cart;
}cart_info;


void *arrive_manager(void *arg)
{
  cart_info *CART = (cart_info *)arg;
 
  if(CART->track == Black)
  {
    sem_wait(&junction[4]);
    sem_wait(&junction[0]);
    reserve(CART->cart, E);
    reserve(CART->cart, A);
  }else
  {
    sem_wait(&junction[CART->track]);
    sem_wait(&junction[CART->track + 1]);
    reserve(CART->cart, CART->track);
    reserve(CART->cart, CART->track + 1);
  }
  
  cross(CART->cart, CART->track, CART->junction);
  return NULL;
}





/*
 * You need to implement this function, see cartman.h for details 
 */
void arrive(unsigned int cart, enum track track, enum junction junction) 
{
  cart_info CART;
  CART.cart = cart;
  CART.track = track;
  CART.junction = junction;

  pthread_create(&thread[thread_turn], NULL, arrive_manager, (void *) &CART);

  pthread_join(thread[thread_turn], NULL);
  turn++;
}





/*
 * You need to implement this function, see cartman.h for details 
 */
void depart(unsigned int cart, enum track track, enum junction junct) 
{
  
  if(track == Black)
  {
    release(cart, A);
    release(cart, E);
    sem_post(&junction[0]);
    sem_post(&junction[4]);
  }
  else
  {
    release(cart, track);
    release(cart, track+1);
    sem_post(&junction[track]);
    sem_post(&junction[track + 1]);
  }

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
