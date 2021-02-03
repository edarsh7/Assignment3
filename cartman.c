
#include "cartman.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t junction[5];
sem_t deadlock;
pthread_t threads[5];

typedef struct cart_info
{
  enum junction junction;
  enum track track;
  unsigned int cart;
}cart_info;


void *arrive_manager(void *arg)
{
  cart_info *CART = (cart_info *)arg;
  int junct = CART->track;

  sem_wait(&deadlock);
  sem_wait(&junction[(junct+1) % 5]);
  reserve(CART->cart, (junct+1) % 5);
  sem_wait(&junction[(junct) % 5]);
  reserve(CART->cart, (junct) % 5);
  
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

  pthread_create(&threads[cart], NULL, arrive_manager, (void *) &CART);


}




/*
 * You need to implement this function, see cartman.h for details 
 */
void depart(unsigned int cart, enum track track, enum junction junct) 
{
  
  release(cart, (track) % 5);
  sem_post(&junction[(track) % 5]);
  release(cart, (track + 1) % 5);
  sem_post(cart, (track + 1) % 5);
  sem_post(&deadlock);
}





/*
 * You need to implement this function, see cartman.h for details 
 */
void cartman() 
{
  sem_init(&deadlock, 0 ,2);
  for(int i=0; i < 5; i++)
  {
    sem_init(&junction[i], 0, 1);
  }

}
