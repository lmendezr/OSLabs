#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5;

sem_t clientes;
sem_t barberos;
sem_t silla; //(iniciado a 1)
int sillasLibres; //(iniciado a N)
int clientThreads;

pthread_t tid;

/* Barbero */
void * barbero(void * param){
	while(1) {
		sem_wait(&clientes); /* Espera por clientes y duerme */
		// printf("Barber is sleeping\n");
		sem_wait(&silla); /* Incrementa numero de sillas disponibles */
		sillasLibres++;
		printf("%d\n", sillasLibres);
		sem_post(&barberos); /* Llama proximo cliente */
		sem_post(&silla); /* Suelta mutex de sillas */
		/* Recorta cliente */
		// printf("Barber is cutting\n");
	}
}
/* Clientes */
void * cliente(void * param){
	while(1) {
		sem_wait(&silla); /* Esperar por silla */
		if ( sillasLibres > 0 ) {
			sillasLibres--; /* Esperando turno */
			printf("%d\n", sillasLibres);
			// printf("Client is waiting for a turn\n");
			sem_post(&clientes); /* Avisa barbero */
			// printf("Client notifies the barber\n");
			sem_post(&silla);
			sem_wait(&barberos); /* Esperar si el barbero esta ocupado */
			// printf("Client found a non-busy barber :)\n");
		} else {
			sem_post(&silla); /* No hay sillas disponibles */
			// printf("There are no available chairs :(\n");
		}
	}
}

int main(int argc, char * argv[])
{
    sem_init(&clientes, 0, 0);
    sem_init(&barberos, 0, 0);
    sem_init(&silla, 0, 1);

    sillasLibres = atoi(argv[1]);
    clientThreads = atoi(argv[2]);

    pthread_create(&tid, NULL, barbero,NULL);
    int i = 0;
    while (i<clientThreads){
    	pthread_create(&tid, NULL, cliente, NULL); 
    	i++; 
	}
    pthread_join(tid,NULL);
}

