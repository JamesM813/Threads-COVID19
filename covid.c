#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_OPERATORS 4
#define NUM_LINES 8

static sem_t connected_lock;
static sem_t operators;
static int connected = 0;
static int next_id = 0;

void* phonecall(void* vargp) {
    
	int id;
	// critical section for next_id
	
	sem_wait(&connected_lock);
	id = next_id;
	next_id++;
	sem_post(&connected_lock);
	
	printf("Thread [%d] is attempting to connect ...\n", id);
	
	while (1) {
		// critical section for connected
		sem_wait(&connected_lock);
			
		if (connected < NUM_LINES) {
			connected++;
			sem_post(&connected_lock);
			printf("Thread [%d] connects to an available line, call ringing ...\n", id);
			break;
		} else {
			sem_post(&connected_lock);
			// line is busy
			sleep(1); // wait and then try again
		}
	}
		sem_wait(&operators); // wait for operator
		printf("Thread [%d] is speaking to an operator in the local health center.\n", id);
		sleep(3); // order taking process
		printf("Thread [%d] has made an appointment for the test! The operator has left ...\n", id);
		sem_post(&operators); // release operator

		// update connected count
		sem_wait(&connected_lock);
		connected--;
		sem_post(&connected_lock);


		printf("Thread [%d] has hung up!\n", id);
		return NULL;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Usage: ./COVID_test num_calls\n");
		exit(1);
	}


	int num_calls = atoi(argv[1]);
	pthread_t callers[num_calls];

	// initialize semaphores
	sem_init(&connected_lock, 0, 1);
	sem_init(&operators, 0, NUM_OPERATORS);

	for (int i = 0; i < num_calls; i++) {
		pthread_create(&callers[i], NULL, phonecall, NULL);
	}

	for (int i = 0; i < num_calls; i++) {
		pthread_join(callers[i], NULL);
	}

	// destroy semaphores
	sem_destroy(&connected_lock);
	sem_destroy(&operators);
	return 0;
}
																																																																											
