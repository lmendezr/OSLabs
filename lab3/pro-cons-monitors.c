#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFFER_SIZE 20

int count = 0;
int in = 0;
int out = 0;
int buffer [BUFFER_SIZE];

pthread_mutex_t mutex;
pthread_t tid;


pthread_cond_t full;
pthread_cond_t empty;

void insert(int item){

  pthread_mutex_lock(&mutex);

  while (count == BUFFER_SIZE){
    pthread_cond_wait(&full, &mutex);
  }

  buffer[in] = item;
  in = (in + 1) % BUFFER_SIZE;

  count++;

  if(count == 1){
    pthread_cond_signal(&empty);
  }
   pthread_mutex_unlock(&mutex);
}

int remove_item(){
  int item;

  pthread_mutex_lock(&mutex);

  while (count == 0){
    pthread_cond_wait(&empty, &mutex);
  }

  item = buffer[out];
  out = (out + 1) % BUFFER_SIZE;
  count--;

  if(count == BUFFER_SIZE - 1){
    pthread_cond_signal(&full);
  }

  pthread_mutex_unlock(&mutex);

  return item;
}

void * producer(void * param){
  int item;

  while(1){
    item = rand() % BUFFER_SIZE ;
    insert(item);
    printf("inserted: %d\n", item);
  }
}

void * consumer(void * param){
   int item;
   while(1){
     item = remove_item();
     printf("removed: %d\n", item);
   }
}

int main(int argc, char * argv[])
{
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&full,NULL);
  pthread_cond_init(&empty,NULL);

  int producers = atoi(argv[1]);
  int consumers = atoi(argv[2]);

  int i;
  
  for (i = 0; i < producers; i++)
     pthread_create(&tid, NULL, producer,NULL);

  for (i = 0; i < consumers; i++)
     pthread_create(&tid, NULL, consumer, NULL);  
  pthread_join(tid,NULL);
}