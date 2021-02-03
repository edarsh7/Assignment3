
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t junction[5];
sem_t deadlock;

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
    reserve(CART->cart, A);
    reserve(CART->cart, E);
  }else
  {
    sem_wait(&junction[(int)CART->track]);
    sem_wait(&junction[(int)CART->track + 1]);
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

  pthread_t thread;
  
  sem_wait(&deadlock);
  pthread_create(&thread, NULL, arrive_manager, (void *) &CART);
  pthread_join(thread, NULL);
  sem_post(&deadlock);
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
    sem_post(&junction[(int)track]);
    sem_post(&junction[(int)(track + 1)]);
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
  sem_init(&deadlock, 0, 2);
}
