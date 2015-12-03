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

int memory_size = 0;
int free_memory = 32;
int sleep_time = 5;

int allocate(){
  int item = free_memory;

  pthread_mutex_lock(&mutex);

  while (free_memory > memory_size){
    pthread_cond_wait(&empty, &mutex);
  }
  printf("acquired... %d/%d [free/total] \n", free_memory, memory_size);

  memory_size -= free_memory;

  pthread_cond_signal(&full);
  pthread_mutex_unlock(&mutex);

  return item;
}

int deallocate(){
  int item = free_memory;

  pthread_mutex_lock(&mutex);

  while (free_memory == 0){
    pthread_cond_wait(&full, &mutex);
  }
  printf("freed... %d/%d [free/total] \n", free_memory, memory_size);

  memory_size += free_memory;

  pthread_cond_signal(&empty);
  pthread_mutex_unlock(&mutex);

  return item;
}

void * consumer(void * param){
   int item;
   while(1){
     // printf("acquring memory...\n");
     item = allocate();
     // printf("release memory %d\n", item);
     sleep(sleep_time);
     item = deallocate();
   }
}

int main(int argc, char * argv[])
{

  memory_size = atoi(argv[1]);
  int threads = atoi(argv[2]);

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&full,NULL);
  pthread_cond_init(&empty,NULL);

  int i;
  
  for (i = 0; i < threads; i++)
     pthread_create(&tid, NULL, consumer, NULL); 
  pthread_join(tid,NULL);
}