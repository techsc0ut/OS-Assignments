/*Name: Rahul Khatoliya
    Roll No: 2019265*/
#include <string.h>
#include <stdio.h>   
#include <sys/types.h>   
#include <sys/ipc.h>     
#include <sys/shm.h>     
#include <sys/sem.h>     
#include <unistd.h>  
#include <wait.h>    
#include <time.h>    
#include <stdlib.h>  

#define SEM_ID    2500    

struct String {
    char text[500];
};

struct Numbers
{
    long Number;
};

void
sem_lock(int sem_set_id)
{
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

void
sem_unlock(int sem_set_id)
{
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;   
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}


void
add_text(int sem_set_id, int* text_num, struct String* strings,
        char* text)
{
    sem_lock(sem_set_id);
    strcpy(strings[*text_num].text, text);
    (*text_num)++;
    sem_unlock(sem_set_id);
}

void 
add_Number(int sem_set_id,int* Numbers_count,struct Numbers* numbers,long num){
    sem_lock(sem_set_id);
    numbers[*Numbers_count].Number=num;
    (*Numbers_count)++;
    sem_unlock(sem_set_id);
}

void
do_child(int sem_set_id, int* text_num, struct String* strings,int* Numbers_count,struct Numbers* numbers)
{
    add_text(sem_set_id, text_num, strings,
        "Ram");
    add_Number(sem_set_id,Numbers_count,numbers,213);
    add_Number(sem_set_id,Numbers_count,numbers,2112);
    add_text(sem_set_id, text_num, strings,
        "Shiv");
    add_Number(sem_set_id,Numbers_count,numbers,2113);
}

void
do_parent(int sem_set_id, int* text_num, struct String* strings,int* Numbers_count,struct Numbers* numbers)
{   
    add_text(sem_set_id, text_num, strings,
        "Vishnu");
    add_text(sem_set_id, text_num, strings,
        "Ganesh");
    add_Number(sem_set_id,Numbers_count,numbers,1213);
    add_Number(sem_set_id,Numbers_count,numbers,3213);
    int i, num_loops;

    for (num_loops=0; num_loops < 6; num_loops++) {
        sem_lock(sem_set_id);
        printf("---------------------------------------------------\n");
        if(num_loops==5){
            printf("Final Values Inside Both Text and Number Segments \n");
        }else{
            printf("Values Inside Both Text and Number Segments \n");
        }
        printf("\n");
        printf("Number Of Texts: %d\n", *text_num);
        for (i=0; i < (*text_num); i++) {
            printf("Text Number %d:\n", i+1);
            printf("  text: %s:\n", strings[i].text);
        }
        printf("\n");
        printf("Total Numbers: %d\n", *Numbers_count);
        for (i=0; i < (*Numbers_count); i++) {
            printf("Number  %d:\n", i+1);
            printf("  value: %ld:\n", numbers[i].Number);
        }
        sem_unlock(sem_set_id);
    }
}

int main(int argc, char* argv[])
{
    int sem_set_id1;  
    union semun {              
                int val;
                struct semid_ds *buf;
                ushort * array;
        } sem_val,sem_val2;    
    int shm_id,shm_id2;                
    char* shm_addr;
    char* shm_addr2;            
    int* text_num;        
    int* Numbers_count;
    struct Numbers* numbers;
    struct String* strings; 
    struct shmid_ds shm_desc;
    struct shmid_ds shm_desc2;
    int rc;            
    pid_t pid;             
    sem_set_id1 = semget(SEM_ID, 1, IPC_CREAT | 0600);
    if (sem_set_id1 == -1) {
    perror("main: semget");
    exit(1);
    }

    sem_val.val = 1;
    rc = semctl(sem_set_id1, 0, SETVAL, sem_val);
    if (rc == -1) {
    perror("main: semctl");
    exit(1);
    }

    shm_id = shmget(1000, 2048, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1) {
        perror("main: shmget1: ");
        exit(1);
    }

    shm_id2 = shmget(1011, 2048, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id2 == -1) {
        perror("main: shmget2: ");
        exit(1);
    }

    shm_addr = shmat(shm_id, NULL, 0);
    if (!shm_addr) { 
        perror("main: shmat: ");
        exit(1);
    }

    shm_addr2 = shmat(shm_id2, NULL, 0);
    if (!shm_addr2) { 
        perror("main: shmat: ");
        exit(1);
    }

    text_num = (int*) shm_addr;
    *text_num = 0;
    strings = (struct String*) ((void*)shm_addr+sizeof(int));

    Numbers_count=(int*)shm_addr2;
    *Numbers_count=0;
    numbers=(struct Numbers*)((void*)shm_addr2+sizeof(int));

    pid = fork();
    switch (pid) {
    case -1:
        perror("fork: ");
        exit(1);
        break;
    case 0:
        do_child(sem_set_id1, text_num, strings,Numbers_count,numbers);
        exit(0);
        break;
    default:
        do_parent(sem_set_id1, text_num, strings,Numbers_count,numbers);
        break;
    }


    {
        int child_status;

        wait(&child_status);
    }

    if (shmdt(shm_addr) == -1) {
        perror("main: shmdt: ");
    }

    if (shmdt(shm_addr2) == -1) {
        perror("main: shmdt: ");
    }

    if (shmctl(shm_id, IPC_RMID, &shm_desc) == -1) {
        perror("main: shmctl: ");
    }

    if (shmctl(shm_id2, IPC_RMID, &shm_desc2) == -1) {
        perror("main: shmctl: ");
    }

    return 0;
}


