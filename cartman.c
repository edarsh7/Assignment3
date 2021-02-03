
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
