 #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUF_SIZE 10

sem_t empty;
sem_t full;
sem_t mutex;

int ct;
int in = 0;
int out = 0;

char buf[BUF_SIZE];

void disp_buf()
{
	int i;
	for (i = 0; i < BUF_SIZE; i++) {
		printf("| %c " , buf[i]);

		if (i == BUF_SIZE - 1) {
			printf("|");
		}

	}
	printf("\r");
       
}


void *producer(void *param)
{
	while (1) {
		sem_wait(&empty);
		sem_wait(&mutex);

		if (buf[in] == 'x') {    // Make sure not overwriting
			buf[in] = 'o';
		}

		in = (in + 1) % BUF_SIZE;

		disp_buf();
		
		sem_post(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *param)
{
	while (1) {
		sem_wait(&full);
		sem_wait(&mutex);

		if (buf[out] == 'o') {   // Don't consume something that doesn't exist
			buf[out] = 'x';
		}

		out = (out + 1) % BUF_SIZE;

		disp_buf();

		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main(int argc, char **argv)
{
	int num_producers;
	int num_consumers;
	int i;

//	printf("argc = %d\n", argc);

	if (argc != 3) {
		printf("usage: program  num_producers num_consumers\n");
		exit(1);
	}


	/* Get the stuff that was passed in through the command line */
	sscanf(argv[1], "%d", &num_producers);
	sscanf(argv[2], "%d", &num_consumers);

	/* Initialize the semaphores */
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUF_SIZE);
	sem_init(&mutex, 0, 1);
	
	/* Allocate space for arrays based on the command line arguments */
	pthread_t *prod_TIDs = prod_TIDs = malloc(num_producers * sizeof(int));
	pthread_t *cons_TIDs = cons_TIDs = malloc(num_consumers * sizeof(int));

	/* Fill the buffer with 'x's to represent and empty buffer */
	for (i = 0; i < BUF_SIZE; i++) 
		buf[i] = 'x';

	/* Create the producer threads */
	for(i = 0; i < num_producers; i++)
		pthread_create(&prod_TIDs[i], NULL, producer, NULL);

	/* Create the consumer threads */
	for (i = 0; i < num_consumers; i++)
		pthread_create(&cons_TIDs[i], NULL, consumer, NULL);

				
	while (1);

	
	return 0;
}

