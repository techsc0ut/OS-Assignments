#include <stdio.h> 
#include <time.h>        
#include <string.h>
#include <stdlib.h>

#define LEN 256

int main(int argc, char **argv) {
    if(argc==1)
    {   //Current IST time ...
        char buf[LEN] = {0};
        time_t rawtime = time(NULL);
        if (rawtime == -1) {
            perror("The time() function failed");
            return 1;   
        }
        struct tm *ptm = localtime(&rawtime);
        if (ptm == NULL) {
            perror("The localtime() function failed");
            return 1;
        }
        strftime(buf,LEN, "%A %-d %B %G %r %Z", ptm);
        puts(buf);
        exit(0);
    }
    else if(argc==2 && (strcmp(argv[1],"-u")==0)){
        //Current GMT/UTC time ...
        char buf[LEN] = {0};   
        time_t now = time(&now);
        if (now == -1) {
            perror("The time() function failed");
        }
        struct tm *ptm = gmtime(&now);
        if (ptm == NULL) {
            perror("The gmtime() function failed");
        }    
        strftime(buf,LEN, "%A %-d %B %G %r %Z", ptm);
        puts(buf);
        exit(0);
    }else if(argc==2 && ((strcmp(argv[1],"-R")==0))){
        char buf[LEN] = {0};
        time_t rawtime = time(NULL);
        if (rawtime == -1) {
            perror("The time() function failed");
            return 1;   
        }
        struct tm *ptm = localtime(&rawtime);
        if (ptm == NULL) {
            perror("The localtime() function failed");
            return 1;
        }  
        strftime(buf,LEN, "%a, %-d %b %G %T %z", ptm);
        puts(buf);
        exit(0);
    }else if(argc==2 && ((strcmp(argv[1],"-r")==0))){
        printf("do you mean \"date -R\"\n");
        exit(0);
    }else if(argc==2 && (strcmp(argv[1],"-U")==0)){
        printf("do you mean \"date -u\"\n");
        exit(0);
    }else{
        printf("Unsupported/Invalid Date Command Option\n");
        exit(0);
    }
}
