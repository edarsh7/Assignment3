
/*********************************************************************
 *
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ***********************************************************************/

#include "manpage.h"
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turn = 0;

void *thread_organizer(void *empty)
{

  int pid = getParagraphId();

  pthread_mutex_lock(&lock);

  while(turn != pid)
  {
    pthread_cond_wait(&cond, &lock);
  }

  showParagraph();
  
  turn++;
  
  pthread_cond_broadcast(&cond);

  pthread_mutex_unlock(&lock);

  return NULL;
}

/*
 * See manpage.h for details.
 *
 * As supplied, shows random single messages.
 */
void manpage() 
{
  pthread_mutex_init(&lock, NULL);

  pthread_t threads[7];
  for(int i = 0; i < 7; i++)
  {
    pthread_create(&threads[i], NULL, thread_organizer, NULL);
  }

  for(int j = 0; j < 7; j++)
  {
    pthread_join(threads[j], NULL);
  }

  pthread_mutex_destroy(&lock);
}
