#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

# define BUFFER_SIZE 8

int count = 0;
int buffer_array[BUFFER_SIZE];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg) {
	int itemProd = 0;
	int in = 0;
	while(1) {
		//sleep(1);
		++itemProd;
		while(count == BUFFER_SIZE);
		buffer_array[in] = itemProd;
		in = (in + 1) % BUFFER_SIZE;
		
		pthread_mutex_lock(&lock);
		count += 1;
		printf("\nProducing an item: %d and count is: %d", itemProd, count);
		pthread_mutex_unlock(&lock);
	}
}

void* consumer(void* arg) {
	int itemCons;
	int out = 0;
	while(1) {
		//sleep(1);
		while(count == 0);
		itemCons = buffer_array[out];
		out = (out + 1) % BUFFER_SIZE;
		
		pthread_mutex_lock(&lock);
		count -= 1;
		printf("\nConsuming item: %d and count is: %d", itemCons, count);
		pthread_mutex_unlock(&lock);
	}
}

int main() {
	pthread_t producer_thread, consumer_thread;
	
	pthread_create(&producer_thread, NULL, producer, NULL);
	sleep(1);
	pthread_create(&consumer_thread, NULL, consumer, NULL);
	
	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);
	
	//pthread_mutex_destory(&lock);
	return 0;
}
