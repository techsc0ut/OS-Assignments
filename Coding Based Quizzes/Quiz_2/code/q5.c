/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int count_readers = 0;
sem_t Mutex1, Mutex2;
long Shared;	

/* Note: sem_wait(mutex) locks and sem_post(mutex) unclocks the critical section */

void* driver_read(void*x) {
	sem_wait(&Mutex1); 
	count_readers++;
	if (count_readers == 1) {
		sem_wait(&Mutex2);
	}
	sem_post(&Mutex1); 
	printf("Reading Latest - %ld\n", Shared);
	sem_wait(&Mutex1); 
	if (--count_readers == 0) {
		sem_post(&Mutex2); 
	}
	sem_post(&Mutex1); 
}
void* driver_write(void*x) {
	sem_wait(&Mutex2); 
	Shared = *((long*) x);
	printf("Writing - %ld\n", *((long*) x));
	sem_post(&Mutex2); 
}
int main() {
	pthread_t ID[20];
	sem_init(&Mutex1, 0, 1);
	sem_init(&Mutex2, 0, 1);

	/* Simultaneously Creating Threads and Reading/Writing into the shared variable */
	for (int i = 0 ; i < 5 ; i++) { 
		long* Val = (long*) malloc(sizeof(long));
		*Val = i;
		pthread_create(ID + i , NULL, driver_write, Val);
		pthread_create(ID + i + 1 , NULL, driver_read, NULL);
	}
	for (int i = 0 ; i < 5 ; i++) {
		pthread_join(*(ID + i) , NULL);
		pthread_join(*(ID + i + 1) , NULL);
	}
	sem_destroy(&Mutex1);
	sem_destroy(&Mutex2);
	return 0;
}


