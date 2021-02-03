
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t junction[5];

typedef struct cart_info
{
  enum junction junction;
  enum track track;
  unsigned int cart;
}cart_info;

void *arrive_manager(void *arg)
{
  cart_info *CART = (cart_info *)arg;

  switch(CART->track){
    case Black:
      sem_wait(&junction[0]);
      sem_wait(&junction[4]);
      reserve(CART->cart, A);
      reserve(CART->cart, E);
      break;

    case Red:
      sem_wait(&junction[0]);
      sem_wait(&junction[1]);
      reserve(CART->cart, A);
      reserve(CART->cart, B);
      break;

    case Green:
      sem_wait(&junction[1]);
      sem_wait(&junction[2]);
      reserve(CART->cart, B);
      reserve(CART->cart, C);
      break;

    case Blue:
      sem_wait(&junction[2]);
      sem_wait(&junction[3]);
      reserve(CART->cart, C);
      reserve(CART->cart, D);
      break;

    case Yellow:
      sem_wait(&junction[3]);
      sem_wait(&junction[4]);
      reserve(CART->cart, D);
      reserve(CART->cart, E);
      break;
  }
  cross(CART->cart, CART->track, CART->junction);

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
  pthread_join(&thread, NULL);
}

/*
 * You need to implement this function, see cartman.h for details 
 */
void depart(unsigned int cart, enum track track, enum junction junction) 
{
    switch(CART->track){
    case Black:
      release(cart, A);
      release(cart, E);
      sem_open(&junction[0]);
      sem_open(&junction[4]);
      break;

    case Red:
      release(cart, A);
      release(cart, B);
      sem_open(&junction[0]);
      sem_open(&junction[1]);
      break;

    case Green:
      release(cart, B);
      release(cart, C);
      sem_open(&junction[1]);
      sem_open(&junction[2]);
      break;

    case Blue:
      release(cart, C);
      release(cart, D);
      sem_open(&junction[2]);
      sem_open(&junction[3]);
      break;

    case Yellow:
      release(cart, D);
      release(cart, E);
      sem_open(&junction[3]);
      sem_open(&junction[4]);
      break;
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
