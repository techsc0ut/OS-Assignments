#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
 
int main(int argc, char **argv)
{   
    if(argc==1){
        DIR *d;
        struct dirent *dir;
        char currentDirectory[1024]; 
        getcwd(currentDirectory, sizeof(currentDirectory)); 
        d = opendir(currentDirectory);
        int count=0;
        int a=4;
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {   count++;
                const char *ptr=dir->d_name;
                if(ptr[0]=='.'){
                    continue;
                }else{
                    printf("%s \t", dir->d_name);
                    if(count==a){
                    printf("\n");
                    a=a+4;
                    }
                }                
            }
            closedir(d);
        }
        exit(0);
    }else if(argc==2 && (strcmp(argv[1],"-a")==0)){
        DIR *d;
        struct dirent *dir;
        char currentDirectory[1024]; 
        getcwd(currentDirectory, sizeof(currentDirectory)); 
        d = opendir(currentDirectory);
        int count=0;
        int a=4;
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {   count++;
                printf("%s \t", dir->d_name);
                if(count==a){
                    printf("\n");
                    a=a+4;
                }
            }
            if(count==0){
                printf("Empty\n");
            }
            closedir(d);
        }
        exit(0);
    }else if(argc==2 && (strcmp(argv[1],"-1")==0)){
        DIR *d;
        struct dirent *dir;
        char currentDirectory[1024]; 
        getcwd(currentDirectory, sizeof(currentDirectory)); 
        d = opendir(currentDirectory);
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {   const char *ptr=dir->d_name;
                if(ptr[0]=='.'){
                    continue;
                }else{
                    printf("%s \n", dir->d_name);
                }
            }
            closedir(d);
        }
        exit(0);
    }else {
        printf("Unsupported/Invalid type ls command\n");
        exit(0);
    }		
}
