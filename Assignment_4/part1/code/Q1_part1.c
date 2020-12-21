/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void func(int *a,int b){
	if(b==1){
		while(*a!=-90){
			*a-=1;
			printf("Inside Child Process : %d\n",*a);
		}
	}else if(b==2){
		while(*a!=100){
			*a+=1;
			printf("Inside Parent Process : %d\n",*a);
		}
	}
}

int main(){
	int Global_Variable=10;
	pid_t child_pid,w;
	int status;
	child_pid=fork();
	if(child_pid==-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(child_pid==0){
		func(&Global_Variable,1);
		printf("Final value inside child : %d\n",Global_Variable);
		exit(EXIT_SUCCESS);
	}
	else{
		w=waitpid(child_pid,&status,WUNTRACED | WCONTINUED);
		if(w==-1){
			perror("waitpid");
		}
		else if(WIFEXITED(status)){
			func(&Global_Variable,2);
			printf("Final value inside Parent : %d\n",Global_Variable);
		}
	}
	return 0;
}