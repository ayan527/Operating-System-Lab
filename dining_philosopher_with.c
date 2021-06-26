#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

# define PHILS 5

sem_t chopsticks[PHILS];

void* philosopher_last(void* arg) {
	int phil = *(int *)arg;
	
	while (1) {
		printf("\nPhilosopher %d is thinking...", (phil+1));
		sleep(1);
		
		sem_wait(&chopsticks[(phil + 1) % PHILS]);
		printf("\nPhilosopher %d has taken right chopstick %d", (phil + 1), ((phil + 1) % PHILS));
		sem_wait(&chopsticks[phil]);
		printf("\nPhilosopher %d has taken left chopstick %d", (phil + 1), phil);
	
		printf("\nPhilosopher %d is eating", (phil + 1));
		sleep(1);
		printf("\nPhilosopher %d has finished eating",(phil + 1));
		
		printf("\nPhilosopher %d has released right chopstick %d", (phil + 1), ((phil + 1) % PHILS));
		sem_post(&chopsticks[(phil + 1) % PHILS]);
		printf("\nPhilosopher %d has released left chopstick %d", (phil + 1), phil);
		sem_post(&chopsticks[phil]);
	}
}

void* philosopher(void* arg) {
	int phil = *(int *)arg;
	
	while (1) {
		printf("\nPhilosopher %d is thinking...", (phil+1));
		sleep(1);
		
		sem_wait(&chopsticks[phil]);
		printf("\nPhilosopher %d has taken left chopstick %d", (phil + 1), phil);
		sem_wait(&chopsticks[(phil + 1) % PHILS]);
		printf("\nPhilosopher %d has taken right chopstick %d", (phil + 1), ((phil + 1) % PHILS));
	
		printf("\nPhilosopher %d is eating", (phil + 1));
		sleep(1);
		printf("\nPhilosopher %d has finished eating",(phil + 1));
		
		printf("\nPhilosopher %d has released left chopstick %d", (phil + 1), phil);
		sem_post(&chopsticks[phil]);
		printf("\nPhilosopher %d has released right chopstick %d", (phil + 1), ((phil + 1) % PHILS));
		sem_post(&chopsticks[(phil + 1) % PHILS]);
	}
}

int main() {
	int i, a[PHILS];
	pthread_t phils[PHILS];
	
	for(i = 0; i < PHILS; i++)
		sem_init(&chopsticks[i], 0, 1); 
		
	for(i = 0; i < PHILS; i++) {
		a[i] = i;
		
		if (i != PHILS-1) {
			pthread_create(&phils[i], NULL, philosopher, (void *)&a[i]);	
		} else {
			pthread_create(&phils[i], NULL, philosopher_last, (void *)&a[i]);
		}	
	}
	
	for(i = 0; i < PHILS; i++) {
		pthread_join(phils[i], NULL);	
	}
	
	for(i = 0; i < PHILS; i++) {
		sem_destroy(&chopsticks[i]);	
	}
	
	return 0;
}
