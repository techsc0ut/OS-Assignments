/* Name : Rahul Khatoliya
    Roll No: 2019265 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
 
#define N 5 //Number of Philosophers.
#define LEFT p+1 //Global variable for Left Fork
#define RIGHT (p+1)%N+1//Global variable for Left Right Fork.
#define Blocking 1//Flag for Blocking Variant.
#define Non_Blocking 2//Flag for Non_Blocking Variant.
#define Variant 1//Current Value of Variant Flag.

/* Semaphore Structure */
typedef struct {
    int val;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}my_semaphore;

void wait(my_semaphore *s);//Blocking wait.
int Wait(my_semaphore *s);//Non-Blocking wait.

void signal(my_semaphore *s);//Blocking signal
int Signal(my_semaphore *s);//Non-Blocking signal.

/* Eat Method for Current Philosopher */
void Eat(int p){
    printf("Philosopher %d eats using forks %d and %d\n",p+1,LEFT,RIGHT);
    sleep(1);
    printf("Philosopher %d puts fork %d and %d\n",p+1,LEFT,RIGHT);
}
 
int phil[N] = {0, 1, 2, 3, 4};//Sole Argument For Philospoher Threads.

my_semaphore forks[N];//Semaphore Array for Forks.
my_semaphore bowls[2];//Semaphore Array for 2 sauce bowls.

/* Blocking Variant of wait */ 
void wait(my_semaphore *s)
{
    pthread_mutex_lock(&(s->mutex));//Locking for mutual exclusion.
    while (s->val == 0) {
        pthread_cond_wait(&(s->cond), &(s->mutex));//These are used to block on a condition variable.
    }
    s->val--;
    pthread_mutex_unlock(&(s->mutex));//Unlocking the mutex.
}

/* Non-Blocking Variant of wait */
int Wait(my_semaphore *s){
    pthread_mutex_lock(&(s->mutex));
    sleep(1);//To provide a slight time gap.
    s->val--;
    if (s->val < 0) {
        s->val = 0;
        errno = EAGAIN;//Semaphore Already Locked.
        pthread_mutex_unlock(&(s->mutex));
        return -errno;
    }else{
        pthread_mutex_unlock(&(s->mutex));
        return 0;
    }
    
}

/* Blocking Variant of signal */ 
void signal(my_semaphore *s)
{
    pthread_mutex_lock(&(s->mutex));
    s->val++;
    pthread_cond_broadcast(&(s->cond));//This function shall unblock threads blocked on a condition variable.
    pthread_mutex_unlock(&(s->mutex));
}

/* Non-Blocking Variant of signal */
int Signal(my_semaphore *s){
    pthread_mutex_lock(&(s->mutex));
    sleep(1);
    s->val++;
    if(s->val<= 0) {
            printf("This Should Not Execute\n");
            errno = EINVAL;
            pthread_mutex_unlock(&(s->mutex));
            return -errno;
    }
    pthread_mutex_unlock(&(s->mutex));
    return 0;
}

/* Method : signal(printValue) , just for debugging purpose */
void signal_print(my_semaphore *s)
{   
    pthread_mutex_lock(&(s->mutex));
    printf("!!!!!----For Debugging Purpose-----!!!!!\n");
    printf("Value of Semaphore Varible before increment : %d\n",s->val);
    s->val++;
    printf("Value of Semaphore Varible After increment : %d\n",s->val);
    printf("!!!!!----For Debugging Purpose-----!!!!!\n");
    pthread_cond_broadcast(&(s->cond));
    pthread_mutex_unlock(&(s->mutex));
}

/* Semaphore Initializer */
void init(my_semaphore *s,int a)
{
    s->val = a;
}

/* Philosopher Thread Task */
void *philospher(void *num){   
    /* Blocking Version */
    int TRUE=1;
    if(Variant==Blocking){// Checking of Blocking Variant.
        do{   
            int *i=num;
            if(*i==4){
                sleep(1);
                wait(&forks[*i]);// wait for picking up left fork.
                wait(&forks[(*i+1)%N]);// wait for picking up right fork.
                wait(&bowls[0]);// wait for picking up bowl 1.
                wait(&bowls[1]);// wait for picking up bowl 2.

                /* Critical Section */
                Eat(*i);// All resources required are avalable , undergo eating.

                sleep(1);
                signal(&forks[*i]);// allow waiting threads to take his left fork once he had finished eating.
                signal(&forks[(*i+1)%N]);// allow waiting threads to take his right fork once he had finished eating.
                signal(&bowls[0]);// allow waiting threads to take bowl 1,  once he had finished eating.
                signal(&bowls[1]);// allow waiting threads to take bowl 2 once he had finished eating.
                sleep(1);
                printf("Philosopher %d Thinking\n",*i+1);// Philosopher is thinking Currently.
            }else{//  Checking of Non-Blocking Variant.
                sleep(1);
                wait(&forks[*i]);
                wait(&forks[(*i+1)%N]);
                wait(&bowls[0]);
                wait(&bowls[1]);

                /* Critical Section */
                Eat(*i);

                sleep(1);
                signal(&forks[*i]);
                signal(&forks[(*i+1)%N]);
                signal(&bowls[0]);
                signal(&bowls[1]);
                sleep(1);
                printf("Philosopher %d Thinking\n",*i+1);
            }    
        }while(TRUE==1);
    }else{
        /* Non-Blocking Version */    
        do{ 
            int *i=num;
            if (Wait(&forks[*i])<0 && Wait(&forks[(*i+1)%N])<0 && Wait(&bowls[0])<0 && Wait(&bowls[1])<0){//Wait for the resources required without blocking.                  
                continue;
            }else{   
                sleep(1);                                 
                printf("Philosopher %d eats using forks %d and %d\n",*i+1,*i+1,(*i+1)%N+1);//Undergo Eating.
                printf("Philosopher %d puts forks %d and %d\n",*i+1,*i+1,(*i+1)%N+1);//Puts the forks and bowls back.
                printf("Philosopher %d Thinking\n",*i+1);
                sleep(0);
                Signal(&forks[*i]);// Allow other threads to take left fork , without waking up threads. 
                Signal(&forks[(*i+1)%N]);// Allow other threads to take left fork , without waking up threads.
                Signal(&bowls[0]);// Allow other threads to take bowl 1 , without waking up threads.
                Signal(&bowls[1]);// Allow other threads to take bowl 2 , without waking up threads.
            }     
        }while(TRUE==1);
    }
}
 
int main()
{   
    int i;
    pthread_t thread_id[N];// Initialise Threads array.
    
    /* Initialize All forks semaphores */
    for(i = 0; i < N; i++){
        init(&forks[i],1);
    }

    /* Initialising the only 2 available Bowl semaphores */
    init(&bowls[0],1);
    init(&bowls[1],1);

    /* Create Philosopher Threads , and invoke their respective Tasks */
    for(i = 0; i < N; i++){
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    /* Join the Philosopher Threads */
    for(i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}
/*  Deadlock free Solution :
    
    # Reason(For Blocking variant): 
        Allow waiting for all philosophers to 
        their left and then to the right fork , and then pick the bowls if both avaiable together 
        except the last philospoher who would first wait for right fork , then left fork and eventualy
        the two bowls together.

    # Reason(For Non-blocking variant): 
        Since No blocking of threads , therefore
        No chances of deadlocks.
                            
                                */
