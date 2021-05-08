#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* func1(void *arg) {
	int i;
	for (i = 0; i < 10; i++) {
		sleep(1);
		printf("\nFunction 1 called: %d", i);
	}
}

void* func2(void *arg) {
	int i;
	for (i = 0; i < 10; i++) {
		sleep(1);
		printf("\nFunction 2 called: %d", i);
	}
}

int main() {
	pthread_t thread1, thread2;
	printf("\nBefore Threading");
	pthread_create(&thread1, NULL, func1, NULL);
	sleep(1);
	pthread_create(&thread2, NULL, func2, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("\nAfter Threading");
	return 0;	
}
