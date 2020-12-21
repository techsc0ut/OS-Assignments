/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */

#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void *func1(void* a){
	int* x=(int*)a;
	while(*x>-90){
		*x-=1;
		printf("Inside Child Thread : %d\n",*x);
	}
	printf("Final value Inside Child Thread %d\n",*x);
	return NULL;
}

void *func2(void *a){
	int* x=(int*)a;
	while(*x<100){
		*x+=1;
		printf("Inside Parent Thread : %d\n",*x);
	}
	printf("Final value Inside Parent Thread %d\n",*x);
	return NULL;
}

int main(){
	int Global_Variable=10;
	pthread_t t1, t2;	
	pthread_create(&t1,NULL,func1,(void *)&Global_Variable);
	pthread_create(&t2,NULL,func2,(void *)&Global_Variable);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}
