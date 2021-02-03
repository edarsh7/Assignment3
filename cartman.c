
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t junction[5];
sem_t deadlock;
int turn = 0;

typedef struct cart_info
{
  enum junction junction;
  enum track track;
  unsigned int cart;
}cart_info;

void *arrive_manager(void *arg)
{

  cart_info *CART = (cart_info *)arg;
  enum junction j1 = CART->track;
  enum junction j2 = CART->track + 1;

  sem_wait(&deadlock);
  sem_wait(&junction[(int)CART->track]);
  if(CART->track == Black)
  {
    sem_wait(&junction[0]);
    reserve(CART->cart, A);
  }else
  {
    sem_wait(&junction[(int)CART->track + 1]);
    reserve(CART->cart, j2);
  }
  reserve(CART->cart, j1);

  
  
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
  
  pthread_create(&thread, NULL, arrive_manager, (void *) &CART);
  pthread_join(thread, NULL);
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
    sem_post(&junction[4]);
    sem_post(&junction[0]);
  }else
  {
    release(cart, junct);
    release(cart, junct + 1);
    sem_post(&junction[(int)track]);
    sem_post(&junction[(int)track + 1]);
  }
  
}


/*
 * You need to implement this function, see cartman.h for details 
 */
void cartman() 
{
  sem_init(&deadlock, 0, 1);
  for(int i=0; i < 5; i++)
  {
    sem_init(&junction[i], 0, 1);
  }
}
