#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

char* func(char** argv,int argc){
    int j=1;
    char *buf;
    while(argv[j+1]){
      //printf("Hello1\n");
      strcat(buf,argv[j]);
      strcat(buf," ");
      //printf("Hello2\n");
      j++;
    }
    strcat(buf,argv[j]);
    return buf;
}

int main(int argc, char **argv){ 	
	if(argc==2)//For making a Single directory .
	{		int status;   
    	status = mkdir(argv[1],0777);//0700 here refers to mode of file permisiions .. 
  		// checking if the directory is created or not ...
    	if(status){
        	perror("Unable to create directory\n"); 
        	exit(0);
    	}
    	exit(0);
	}
	else if(argc==3 && (strcmp(argv[1],"-p")==0))// For Creating Parent Directories , and ignoring if already exist .
	{   char * token = strtok(argv[2], "/");
      // loop through the string to extract all other tokens
      while( token != NULL ) {
        mkdir(token,0777); //printing each token
        chdir(token);
        token = strtok(NULL, "/");
      }
      exit(0);
	 }
   else if(argc>2 && (strcmp(argv[1],"-v")==0)){// For Creating Multiple directories within the current working directory .
      for(int i=2;i<argc;i++){
        int a=mkdir(argv[i],0777);
        if(a==-1){
            printf("\nmkdir: cannot create directory ‘%s’: File exists",argv[i]);
        }else{
            printf("\nmkdir: created directory '%s'",argv[i]);
        }
      }
      exit(0);
   }
   else if(argc>2)
   {  
      char* buf=func(argv,argc);
      mkdir(buf,0777);
      exit(0);
   }
   else{
      printf("mkdir: missing operand\n");
      exit(0);
   }
}