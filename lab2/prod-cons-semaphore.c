#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

int count = 0;
int in = 0;
int out = 0;
int buffer [BUFFER_SIZE];

// prod/cons semaphores
sem_t full, empty;

pthread_t tid;

void insert(int item){
   while (count == BUFFER_SIZE);
   buffer[in] = item;
   in = (in + 1) % BUFFER_SIZE;
   count++;
}

int remove_item(){
   int item;
   while (count == 0);
   item = buffer[out];
   out = (out + 1) % BUFFER_SIZE;
   count--;
   return item;
}

void * producer(void * param){
   int item;
   while(1){
      item = rand() % BUFFER_SIZE ;

      sem_wait(&empty);

      insert(item);
      printf("inserted: %d\n", item);

      sem_post(&full);
   }
}

void * consumer(void * param){
   int item;
   while(1){

     sem_wait(&full);

     item = remove_item();
     printf("removed: %d\n", item);

     sem_post(&empty);
   }
}

int main(int argc, char * argv[])
{
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    int i;

    for (i = 0; i < producers; i++)
       pthread_create(&tid, NULL, producer,NULL);

    for (i = 0; i < consumers; i++)
       pthread_create(&tid, NULL, consumer, NULL);  
    pthread_join(tid,NULL);
}

