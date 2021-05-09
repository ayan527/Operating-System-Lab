#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int readCount = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t readers[50], writers[50];

void* readerFunc(void* arg) {
	do {
		++readCount;
		if (readCount == 1) pthread_mutex_lock(&lock);
		printf("\nReader Thread %d is reading now...", pthread_self());
		sleep(1);
		--readCount;
		if(readCount == 0) pthread_mutex_unlock(&lock);
	} while(1);
}

void* writerFunc(void* arg) {
	do {
		pthread_mutex_lock(&lock);
		printf("\nWriter Thread %d is writing now...", pthread_self());
		sleep(1);
		pthread_mutex_unlock(&lock);
	} while(1);
}

int main() {
	int count, numberOfThreads;
	
	printf("\nEnter no. of threads (1-50): ");
	scanf("%d",&numberOfThreads);
	
	for(count = 0; count < numberOfThreads; count++) {
		pthread_create(&writers[count], NULL, writerFunc, NULL);
		pthread_create(&readers[count], NULL, readerFunc, NULL);
	}
	
	for(count = 0; count < numberOfThreads; count++) {
		pthread_join(writers[count], NULL);
		pthread_join(readers[count], NULL);
	}
	
	return 0;
}
