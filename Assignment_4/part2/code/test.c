    /* Name: RAHUL KHATOLIYA
       Roll_Number: 2019265 */
    #include <linux/kernel.h>
    #include <sys/syscall.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <errno.h>

    #define __NR_sh_task_info 440

    long sh_task_info_syscall(char* fileName,int pi)
    {
        return syscall(__NR_sh_task_info,pi,fileName);
    }

    int main()
    {	
        char Continue='y';
        do{
            printf("\n ENTER PROCESS ID : ");
            char* pidArg=(char*)malloc(20*sizeof(char));
            scanf("%s",pidArg);
            int pid=atoi(pidArg);

            printf("\n ENTER FILENAME/PATH : ");
            char* fileName = (char*) malloc(512*sizeof(char));
            scanf("%s", fileName);

            long activity;
            activity = sh_task_info_syscall(fileName,pid);
            if(activity < 0)
            {
                perror(" sh_task_info failure");
            }
            else
            {
                printf(" sh_task_info : SUCCESS");
            }
            printf("\n Want to test more (y) ?");
            scanf(" %c",&Continue);
            
        }while(Continue=='y' || Continue=='Y');   
        return 0; 
    }