#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

# define BUFFER_SIZE 8

int produceCount = 0;
int consumeCount = 0;

int buffer_array[BUFFER_SIZE];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* producer (void* arg) {
	int itemProd = 0;
	int i = 0;
	
	while (1) {
		++itemProd;
		while (produceCount - consumeCount == BUFFER_SIZE);
		
		buffer_array[produceCount % BUFFER_SIZE] = itemProd;
		sleep(1);
		
		pthread_mutex_lock(&lock);
		++produceCount;
		printf("\nProducing an item: %d and count is: %d", itemProd,(produceCount - consumeCount));
		pthread_mutex_unlock(&lock);
	}
}

void* consumer (void* arg) {
	int itemCons;
	int i = 0;
	
	while (1) {
		while (produceCount - consumeCount == 0);
		
		itemCons = buffer_array[consumeCount % BUFFER_SIZE];
		sleep(1);
		
		pthread_mutex_lock(&lock);
		++consumeCount;
		printf("\nConsuming item: %d and count is: %d", itemCons,(produceCount - consumeCount));
		pthread_mutex_unlock(&lock);
	}
}

int main() {
	pthread_t producer_thread, consumer_thread;
	
	pthread_create(&producer_thread, NULL, producer, NULL);
	//sleep(1);
	pthread_create(&consumer_thread, NULL, consumer, NULL);
	
	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);
	
	return 0;
}
