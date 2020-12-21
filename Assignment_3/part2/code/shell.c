#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h>
#define clear() printf("\033[H\033[J")  
  
#define BUFFSIZE 1000 // max number of letters to be supported 
#define COMSIZE 100 // max number of commands to be supported 
 
// Function to take input 
char programDirectory[100];
char rd[100];
char* buffer;


int Input(char* str){;    
    buffer = readline("\n>>> "); 
    if (strlen(buffer) != 0) { 
        add_history(buffer); 
        strcpy(str, buffer); 
        return 0; 
    } else { 
        return 1; 
    } 
} 

// Function to print Current Directory. 
void Directory(){ 
    char currentDirectory[1024]; 
    getcwd(currentDirectory, sizeof(currentDirectory)); 
    printf("\nDir: %s", currentDirectory); 
} 

int isNumeric(char **parsed){
    char str[10];
    strcpy(str,parsed[1]);
    int flag=0;
    if(str[0]=='-'){
        for(int i=1;i<strlen(str);i++){
            if(str[i]>='0' && str[i]<='9'){
                continue;
            }else{
                return 0;
            }
        }
        if(flag==0){
            return 1;
        }
    }else{
        for(int i=0;i<strlen(str);i++){
            if(str[i]>='0' && str[i]<='9'){
                continue;
            }else{
                return 0;
            }
        }
        if(flag==0){
            return 1;
        }  
    }
    return 0;
}


void showSessionHistory(int a){
    //chdir(getenv("HOME"));
    HISTORY_STATE *myhist = history_get_history_state ();
    /* retrieve the history list */
    HIST_ENTRY **mylist = history_list ();
    if(a==0){
        printf("Last executed command : ");
        int c=myhist->length;
        c=c-2;
        printf (" %8s  %s\n", mylist[c]->line, mylist[c]->timestamp);
    }
    else{
        printf ("\nCurrent Session history\n\n");

        for (int i = 0; i < myhist->length; i++) { /* output history list */
            printf (" %8s  %s\n", mylist[i]->line, mylist[i]->timestamp);
        }
        putchar ('\n');
    }
}

  
// Function where the system command is executed 
void external_command_handler(char** parsed){ 
    pid_t pid;
    pid = fork();
    if (pid < 0){
        printf("A fork error has occurred.\n");
        return;
    }
    else if (pid == 0) /* Inside Children */
    {
        strcat(programDirectory,"/");
        strcat(programDirectory,parsed[0]);
        execvp(programDirectory,parsed);
        printf("Invalid Shell Command\n");
        exit(127);
    }
    else  /* Inside parent */
    {
        wait(0);/* Wait for the child to terminate. */
        return ;
    }
}

void echoCommand(char** parsed){
    char* ar=parsed[1];
    if(ar[0]=='\"'){
        char* buf;   
        buf = buffer;
        int a=strlen(buf);
        char buf2[a];
        int flag=0;
        int j=0;   
        for(int i=0;i<strlen(buf);i++){
           if(buf[i]=='\"'){
             flag=1;
           }
           if(flag!=0 && buf[i]!='\"'){
              buf2[j]=buf[i];
              j++;
              flag++;
           }
           if(flag==1 && buf[i]=='\"'){
              continue;
           }
           if(flag>1 && buf[i]=='\"'){
              flag=0;
           }
        }
        char fin[j];
        for(int k=0;k<j;k++){
            fin[k]=buf2[k];
        }
        fin[j]='\0';
        printf("%s\n",fin);
        printf("\n");
    }
    else if(strcmp(parsed[1],"-e")==0){
        char* buf;   
        buf = buffer;
        int a=strlen(buf);
        char buf21[a];
        int flag=0;
        int j=0;   
        for(int i=0;i<strlen(buf);i++){
           if(buf[i]=='\"'){
             flag=1;
           }
           if(flag!=0 && buf[i]!='\"'){
              buf21[j]=buf[i];
              j++;
              flag++;
           }
           if(flag==1 && buf[i]=='\"'){
              continue;
           }
           if(flag>1 && buf[i]=='\"'){
              flag=0;
           }
        }
        char fin[j];
        for(int k=0;k<j;k++){
            fin[k]=buf21[k];
        }
        fin[j]='\0';
        char* buf2=fin;
        for(int i=0;i<strlen(buf2);i++){
        if(flag==1){
            printf("\n%c",buf2[i]);
            flag=0;
        }
        else if(flag==2){
            printf("\t%c",buf2[i]);
            flag=0;
        }else if(flag==3){
            printf("\b%c",buf2[i]);
            flag=0;
        }
        else if(flag==4){
            printf("\v%c",buf2[i]);
            flag=0;
        }
        else{
            if(buf2[i]=='\\'){
            if(!buf2[i+1]){
                continue;
            }else{
                if(buf2[i+1]=='n'){
                    flag=1;
                    i++;
                }else if(buf2[i+1]=='t'){
                    flag=2;
                    i++;
                }else if(buf2[i+1]=='b'){
                    flag=3;
                    i++;
                }else if(buf2[i+1]=='v'){
                    flag=4;
                    i++;
                }else{
                    continue;
                }
            }
        }else if(buf2[i]!='\"' && (buf2[i-1] && buf2[i-1]!='\\')){
            printf("%c",buf2[i]);
        }
      }
    }
            printf("\n");
    }else {
        int j=1;
        while(parsed[j]){
            printf("%s ",parsed[j]);
            j++;
        }
        printf("\n");
    }   
} 

void cdCommand(){
      char* buf;   
      buf = buffer;
      int a=strlen(buf);
      char buf2[a];
      int flag=0;
      int j=0;   
      for(int i=0;i<strlen(buf);i++){
           if(buf[i]=='\"'){
             flag=1;
           }
           if(flag!=0 && buf[i]!='\"'){
              buf2[j]=buf[i];
              j++;
              flag++;
           }
           if(flag==1 && buf[i]=='\"'){
              continue;
           }
           if(flag>1 && buf[i]=='\"'){
              flag=0;
           }
      }
      char fin[j];
      for(int k=0;k<j;k++){
          fin[k]=buf2[k];
      }
      fin[j]='\0';
      int ab=chdir(fin);
      if(ab!=0){
        printf("No such Directory [%s] Exists / or Too many arguments \n",fin);
      }
}

// Function to execute Internal commands . 
int internal_Commands_Handler(char** parsed,char* buf) { 
    int i, a,check = 0; 
    char* Cmds[6]; 
    char currentDirectory[1024];
    //‘cd’, ‘echo’, ‘history’, ‘pwd’ and ‘exit’.
    Cmds[0] = "exit"; 
    Cmds[1] = "cd"; 
    Cmds[2] = "history"; 
    Cmds[3] = "pwd";
    Cmds[4] = "echo";
    Cmds[5] =  "clear"; 
    
    for (i = 0; i < 6; i++) { 
        if (strcmp(parsed[0], Cmds[i]) == 0) { 
            check = i + 1; 
            break; 
        } 
    } 
    switch (check) { 
    case 1://exit
        if(!parsed[1] && (strcmp(parsed[0],"exit")==0)){
            exit(0);
        } 
        else if(parsed[1] && (strcmp(parsed[1],"--help")==0)){
            printf("exit: exit [n] \n\tExit the shell. \n\tExits the shell with a status of N.  If N is omitted, the exit status \n\tis that of the last command executed .");
            return 1;
        }else if(isNumeric(parsed)==1){
            printf("Program Terminated with exit status [%s]\n",parsed[1]);
            exit(0);
        }
        exit(0); 
    case 2://cd
        if(parsed[2]){
            cdCommand();
            return 1;
        }else{
            a=chdir(parsed[1]);
            if(a!=0){
                printf("No such Directory Exists\n");
                return 1; 
            }
        }          
        return 1;
    case 3://History
        if(parsed[1] && (strcmp(parsed[1],"!!")==0)){
            showSessionHistory(0);
            return 1;
        }else if(parsed[1]){
            printf("Unsupported/Invalid history Type Command\n");
            return 1;
        }else if(strcmp(parsed[0],"History")==0){
            printf("Do you mean \"history\"\n");
            return 1;
        }
        else{
            showSessionHistory(1);
            return 1;  
        } 
    case 4://pwd
        if(parsed[1] && (strcmp(parsed[1],"-P")==0)){
            getcwd(currentDirectory, sizeof(currentDirectory)); 
            printf("\nWorking Directory : %s", currentDirectory); 
            printf("\n");
        }else if(parsed[1] && (strcmp(parsed[1],"-L")==0)){
            getcwd(currentDirectory, sizeof(currentDirectory)); 
            printf("\nWorking Directory : %s", currentDirectory); 
            printf("\n");
        }else if(parsed[1]){
            printf("Unsupported or Invalid type pwd Option");
        }else if(strcmp(parsed[1],"Pwd")==0){
            printf("Do You Mean \"pwd\"\n");
        }else{
            getcwd(currentDirectory, sizeof(currentDirectory)); 
            printf("\nWorking Directory : %s", currentDirectory); 
            printf("\n");
        }
        return 1; 
    case 5:// echo
    // Commands for formatted text must be inside - " "  to operate .
        if(!parsed[1]){
            printf("Incomplete arguments ... \n");
            return 1;
        }else if(parsed[1] && (strcmp(parsed[1],"-E")==0)){
            printf("Do you mean \"echo -e <text> \" \n");
            return 1;
        }else  if(parsed[1] && (strcmp(parsed[1],"-e")==0) && (!parsed[2])){
            printf("Arguments Missing for \"-e\" type echo command\n");
            return 1;
        }
        else{
            echoCommand(parsed);
            return 1;  
        }
    case 6:
        clear();
        return 1;     
    default: 
        break; 
    } 
    return 0; 
} 

// function for parsing command words 
void commandParser(char* str, char** parsed){  
    for (int i = 0; i < COMSIZE; i++) { 
        parsed[i] = strsep(&str, " "); 
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 

int commandType(char* str, char** parsed){ 
    commandParser(str, parsed); 
    if(internal_Commands_Handler(parsed,str)){
        return 0;//Command was internal type ..
    }//else the command might be an external one ..
    return 1; 
} 
  
int main(){
    getcwd(programDirectory, sizeof(programDirectory));  
    char inputBuffer[BUFFSIZE], *Args[COMSIZE]; 
    int status = 0; 
    while (1) { 
        Directory(); 
        if (Input(inputBuffer)) 
            continue;
        // fputs(buffer,Hptr);     
        status = commandType(inputBuffer, 
        Args);  
        if (status == 1)
            external_command_handler(Args); 
    }
    // fclose(Hptr);
    return 0;
} 
