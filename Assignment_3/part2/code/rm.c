#include <stdio.h> 
#include <time.h>        
#include <string.h>
#include <stdlib.h>

char* func(char** argv,int argc){
    char *buf;
    strcpy(buf,"");
    int j=1;
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

int main(int argc, char **argv) {// In Our Code , if the file exist it will be removed , irrespective of the fact that it is read only or not .
   if(argc==2){
   	   int del = remove(argv[1]);
   	   if(del)
       		perror(argv[1]);
       exit(0);
   }else if(argc>2 && (strcmp(argv[1],"-i")==0)){// Removes while asking ..
        int len=argc;
        for(int i=2;i<len;i++){
            char c[4];
            printf("\nrm: remove regular file '%s'? (y/n)\n",argv[i]);
            fgets(c,sizeof(c),stdin);
            if(c[0]=='y' || c[0]=='Y'){
                int del = remove(argv[i]);
                if (!del)
                    continue;
                else
                    perror(argv[i]); 
            }else{
              continue;
            }
        }
        exit(0);
   }
   else if(argc>2 && (strcmp(argv[1],"-f")==0)){// Removes without asking , Ignores Non-existing .
   		int len=argc;
   		for(int i=2;i<len;i++){
   			int del = remove(argv[i]);
   		}
   		exit(0);
    }
    else if(argc>2 && (strcmp(argv[1],"-I")==0)){
      printf("Do You mean \"rm -i\" \n");
      exit(0);
    }

    else if(argc>2 && (strcmp(argv[1],"-F")==0)){
      printf("Do You mean \"rm -f\" \n");
      exit(0);
    }
   else if(argc>2){
    printf("Searching in Directory..\n");
    char *buf=func(argv,argc);
    //printf("%s\n", buf);
    int del = remove(buf);
    if(del){
      perror(buf);
    }else{
      printf("Successfully removed\n");
    }
    exit(0);
   }
   else if(argc==1){
      printf("rm: missing operand");
      exit(0);
   }else{
    printf("Unsupported/Invalid Type rm Command\n");
    exit(0);
   }
}