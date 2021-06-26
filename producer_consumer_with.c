#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

# define BUFFER_SIZE 8

int buffer_array[BUFFER_SIZE];

sem_t full_sem, empty_sem, binary_sem;

void* producer(void* arg) {
	int itemProd = 0;
	int in = 0;
	while(1) {
		// sleep(1);
		++itemProd;
		
		sem_wait(&empty_sem);
		sem_wait(&binary_sem);
		
		buffer_array[in] = itemProd;
		printf("\nProducing an item: %d", itemProd);
		in = (in + 1) % BUFFER_SIZE;
		
		sem_post(&binary_sem);
		sem_post(&full_sem);
	}
}

void* consumer(void* arg) {
	int itemCons;
	int out = 0;
	while(1) {
		// sleep(1);
		sem_wait(&full_sem);
		sem_wait(&binary_sem);
		
		itemCons = buffer_array[out];
		printf("\nConsuming an item: %d", itemCons);
		sleep(1);
		out = (out + 1) % BUFFER_SIZE;
		
		sem_post(&binary_sem);
		sem_post(&empty_sem);
	}
}

int main() {
	sem_init(&full_sem, 0, 0);
	sem_init(&empty_sem, 0, BUFFER_SIZE);
	sem_init(&binary_sem, 0, 1);
	
	pthread_t producer_thread, consumer_thread;
	
	pthread_create(&producer_thread, NULL, producer, NULL);
	sleep(1);
	pthread_create(&consumer_thread, NULL, consumer, NULL);
	
	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);
	
	sem_destroy(&binary_sem);
	sem_destroy(&full_sem);
	sem_destroy(&empty_sem);
	
	return 0;
}
