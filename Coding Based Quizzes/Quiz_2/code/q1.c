#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(){
	char * input;
	input=(char*)malloc(500*sizeof(char));
	int fd1[2],fd2[2];
	pid_t pid;
	/* Creating Two Pipes , one for passing the input string from parent to child and another for sending the upper-cased string from child */
	pipe(fd1);
	pipe(fd2);
	pid=fork();
	/* Note : file descriptor , 0 for reading and 1 for writing */
	if(pid!=0){
		/* Taking Input String From User */
		close(fd1[0]);
		printf("\nInput String : ");
		fgets(input,500,stdin);
		write(fd1[1],input,strlen(input)+1);
		close(fd1[1]);

		wait(NULL);

		close(fd2[1]);
		char *final;
		final=(char*)malloc(500*sizeof(char));
		read(fd2[0],final,500);
		printf("Upper-Cased String : %s\n",final);
		close(fd2[0]);
	}else{
		close(fd1[1]);
		char *recv;
		recv=(char*)malloc(500*sizeof(char));
		read(fd1[0],recv,500);

		for(int i=0;recv[i]!='\0';i++){
			recv[i]=toupper(recv[i]);
		}
		close(fd1[0]);
		close(fd2[0]);
		write(fd2[1],recv,strlen(recv)+1);
		close(fd2[1]);
	}
	return 0;
}

