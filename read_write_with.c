#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int readCount = 0;
int checkingDigit = 0;

sem_t binary_sem, database_sem;
pthread_t readers[50], writers[50];

void* readerFunc(void* arg) {
	do {
		sem_wait(&binary_sem);
		
		readCount += 1;
		if(readCount == 1) {
			sem_wait(&database_sem);
		}
		
		sem_post(&binary_sem);
		printf("\nReader Thread %d is reading now... Checking Digit: %d", pthread_self(), checkingDigit);
		sleep(1);
		
		sem_wait(&binary_sem);
		readCount -= 1;
		if(readCount == 0) {
			sem_post(&database_sem);
		}
		
		sem_post(&binary_sem);
	} while(1);
}

void* writerFunc(void* arg) {
	do {
		sem_wait(&database_sem);
		checkingDigit += 1;
		printf("\nWriter Thread %d is writing now... Checking Digit updated: %d", pthread_self(), checkingDigit);
		sleep(1);
		sem_post(&database_sem);
	} while(1);
}

int main() {
	int count, numberOfThreads;
	
	sem_init(&binary_sem, 0, 1);
	sem_init(&database_sem, 0, 1);
	
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
	
	sem_destroy(&binary_sem);
	sem_destroy(&database_sem);
	
	return 0;
}
