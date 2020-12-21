/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
#include <sys/wait.h>

int check_input(char input[]){
	for (int i=0;input[i]!='\0'; i++){
		if(i==0){
			if(input[i]=='-'){
				continue;
			}else if(!isdigit(input[i])){
				return -1;
			}
		}
		else if(!isdigit(input[i]))
        {	
            return -1;
        }
	}
	return 0;
}

int main()
{   
	/*Input for Selecting Process*/
	int ch=-1;
	int check_int=-1;
	char buf[50];
	do{
		printf("\nSelect process on which syscall should be applied : \n\n Process 1 \n\n Process 2 \n");
		scanf("%s",buf);
		check_int=check_input(buf);
		if(check_int<0){
			printf("\nInvalid Argument");
		}else {
			ch=atoi(buf);
			if(ch!=1 && ch!=2){
				printf("\nNo Such Process, should be 1 or 2\n");
				ch=-1;
			}else{
				ch=0;
			}
		}
	}while(ch==-1 || check_int==-1);
	
	/*Input For Soft Real Time Value*/
	int check_neg=-1;
	int check=-1;
	int rtnice;
	char soft[50];
	do{	
		printf("Soft Real time Value : ");
        scanf("%s",soft);
        check=check_input(soft);
		if(check<0){
			printf("\nError : AlphaNumeric Not Allowed \n");
		}
		else{
			rtnice=atoi(soft);
			if(rtnice<0){
				printf("\nError : Negative Soft value not Allowed \n");
			}else{
				check_neg=0;
			}
		}
	}while(check==-1 || check_neg==-1);

    pid_t pid=fork();     
    if(pid!=0)
    {
        printf("\nProcess 1 PID: %d\n",getpid());
        printf("\nProcess 2 PID: %d\n",pid);
        int ret;
        if(ch==1){
        	ret = syscall(441,getpid(), rtnice);
        	if(ret<0){
            	perror("rtnice failure");
            	exit(1);
        	}
        }else{
			ret = syscall(441,pid, rtnice);
        	if(ret<0){
            	perror("rtnice failure");
            	exit(1);
        	}
        }
    
      	clock_t t; 
        t = clock(); 
        int count=0;
       	int i=0;
        for(i=0; i<2000000000; i++)
        {
            count += i;     
        } 
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC;      
        printf("\nProcess with PID: %d terminated in [ %f Time units ]\n",getpid(),time_taken);
        wait(&pid);
    }   
    else
    {	
    	clock_t t; 
        t = clock();
        int count=0;
       	int i=0;
        for(i=0; i<2000000000; i++)
        {
            count += i;     
        }  
        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC;           
        printf("\nProcess with PID: %d terminated in [ %f Time units ]\n",getpid(),time_taken);
    }
    return 0;
}