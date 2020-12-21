/* Name : Rahul Khatoliya
	Roll No : 2019265 */
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define PHILOSOPHERS 5

pthread_mutex_t chopsticks[PHILOSOPHERS];
pthread_t philosophers[PHILOSOPHERS];
pthread_attr_t attributes[PHILOSOPHERS];

int check=0;
int check_eating[PHILOSOPHERS];

void *philosopher_task(void *);
void think(int);
void Up(int);
void eat(int);
void Down(int);

void *philosopher_task(void *philosopherNumber) {
	/* Terminating Condition When all Philosophers have finished Eating */
	while (check<5) {
		think((intptr_t)philosopherNumber);
		Up((intptr_t)philosopherNumber);
		eat((intptr_t)philosopherNumber);
		Down((intptr_t)philosopherNumber);
	}
}

void think(int philosopherNumber) {
	int sleepTime = rand() % 3 + 1;
	printf("Philosopher %d will think for %d seconds\n", philosopherNumber, sleepTime);
	sleep(sleepTime);
}

void Up(int philosopherNumber) {
	int right = (philosopherNumber + 1) %PHILOSOPHERS;
	int left = (philosopherNumber +PHILOSOPHERS) % PHILOSOPHERS;
	if (philosopherNumber & 1) {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
	}
	else {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
	}
}

void eat(int philosopherNumber) {
	if(check_eating[philosopherNumber]==0){
		check_eating[philosopherNumber]=1;
		check++;
		int eatTime = rand() % 3 + 1;
		printf("Philosopher %d will eat for %d seconds\n", philosopherNumber, eatTime);
		sleep(eatTime);
	}else{
		int eatTime = rand() % 3 + 1;
		sleep(eatTime);
	}
}

void Down(int philosopherNumber) {
	printf("Philosopher %d will will put down her chopsticks\n", philosopherNumber);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) %PHILOSOPHERS]);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + PHILOSOPHERS) % PHILOSOPHERS]);
}

int main() {
	int i;
	/* Loop to initiaize check_array which will check if all the philosophers have eaten or not */
	for(i=0;i<PHILOSOPHERS;++i){
		check_eating[i]=0;
	}
	for (i = 0; i <PHILOSOPHERS; ++i) {
		pthread_mutex_init(&chopsticks[i], NULL);
	}

	for (i = 0; i <PHILOSOPHERS; ++i) {
		pthread_attr_init(&attributes[i]);
	}
	
	for (i = 0; i <PHILOSOPHERS; ++i) {
		pthread_create(&philosophers[i], &attributes[i], philosopher_task, (void *)(intptr_t)(i));
	}

	for (i = 0; i <PHILOSOPHERS; ++i) {
		pthread_join(philosophers[i], NULL);
	}
	return 0;
}

