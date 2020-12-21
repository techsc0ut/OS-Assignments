#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* func(char** argv,int argc){
    char *buf;
    strcpy(buf,"");
    int j=2;
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
	if(argc==2){
        if(strcmp(argv[1],"-n")==0){
            printf("Missing File Name \n");
        exit(0);
        }else{
            FILE *fptr; 
            char filename[100], c; 
            fptr = fopen(argv[1],"r"); 
            if (fptr == NULL) 
            { 
                perror(argv[1]);
                exit(0); 
            } 
            c = fgetc(fptr); 
            while (c != EOF) 
            { 
                printf ("%c", c); 
                c = fgetc(fptr); 
            } 
            fclose(fptr);
        } 
    	exit(0); 
    }else if(argv[1] && (strcmp(argv[1],"-n")==0)){
        char* buf=func(argv,argc);
        char line[400] = {0};
        unsigned int lineNumber = 0;
        /* Open file */
        FILE *fptr = fopen(buf, "r");    
        if (!fptr)
        {   perror(buf);
            exit(0);
        }
        /* Get each line until there are none left */
        while (fgets(line, 400, fptr))
        {
            printf("[%d]: %s", ++lineNumber, line);
        }
        if (fclose(fptr))
        {   perror(buf);
            exit(0);
        }
        exit(0); 
    }else if(argc==4 && (strcmp(argv[2],">")==0)){
		FILE *fptr1, *fptr2; 
    	char filename[100], c; 
    	fptr1 = fopen(argv[1], "r"); 
    	if (fptr1 == NULL) 
    	{ 
        	perror(argv[1]);
        	exit(0); 
    	} 
    	fptr2 = fopen(argv[3], "w"); 
    	if (fptr2 == NULL) 
    	{ 
        	perror(argv[3]);
        	exit(0); 
    	} 
    	c = fgetc(fptr1); 
    	while (c != EOF) 
    	{ 
      		fputc(c, fptr2); 
        	c = fgetc(fptr1); 
    	} 
    	fclose(fptr1); 
    	fclose(fptr2); 
    	exit(0);
	}else{
        printf("Unsupported/Invalid Cat type Command\n");
        exit(0);
    }
}










 







