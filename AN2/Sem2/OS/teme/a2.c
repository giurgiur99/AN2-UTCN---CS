#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include "a2_helper.h"

#define MAXSTEPS 5
#define NO_OF_THREADS 6
#define NO_OF_THREADS_MAIN 10
#define NAME_LEN 11

pthread_mutex_t lock, lockp6, mt[10] = PTHREAD_MUTEX_INITIALIZER;
typedef struct {
	int pid;
	int tid;
	
} struct_thread;
sem_t sem34, sem43;
sem_t semBarrier;
sem_t sem1, sem2, sem3, sem4, sem14;
int  i=1, counter=0,ok=0;

void *func(void *arg)
{
    struct_thread* i = ((struct_thread *)arg);
    //if(i->tid==3)
    //pthread_mutex_lock(&mt[i->tid]);
    sem_t* sem21 = sem_open("sem21", O_CREAT, 0666, 0);
    sem_t* sem41 = sem_open("sem41", O_CREAT, 0666, 0);

    if(i->pid == 6 && i->tid==1 && ok!=0)
    {
        sem_wait(sem21);
    }

    if(i->pid == 6 && i->tid==4)
    {
        sem_wait(&sem34);
    }
    info(BEGIN, i->pid, i->tid);
    if(i->pid == 6 && i->tid==3)
    {
        sem_post(&sem34);
    }

    if(i->pid == 6 && i->tid==3)
    {
        sem_wait(&sem43);
    }

    info(END, i->pid, i->tid);

    if(i->pid == 6 && i->tid==4)
    {
        sem_post(&sem43);
    }

    
    if(i->pid == 6 && i->tid==1 && ok!=0)
    {
        sem_post(sem41);
    }
    if(i->pid == 6 && i->tid==5)
        ok++;
    

    //pthread_mutex_unlock(&mt[i->tid]);

     sem_close(sem21);
     sem_close(sem41);
    return NULL;
}

void *func_2(void * arg)
{
    struct_thread* i = ((struct_thread *)arg);
   if(i->pid == 3)
    {
        sem_wait(&semBarrier);
    }
    info(BEGIN, i->pid, i->tid);
    if(i->pid == 3 && i->tid==14)
    {
        sem_wait(&sem14);
        sem_wait(&sem14);
        sem_wait(&sem14);
        sem_wait(&sem14);
    }

    if(i->pid == 3 && i->tid==1)
    {
        sem_post(&sem14);
        sem_wait(&sem1);
    }
    if(i->pid == 3 && i->tid==2)
    {
        sem_post(&sem14);
        sem_wait(&sem2);
    }
    if(i->pid == 3 && i->tid==3)
    {
        sem_post(&sem14);
        sem_wait(&sem3);
    }
    if(i->pid == 3 && i->tid==4)
    {
        sem_post(&sem14);
        sem_wait(&sem4);
    }
    info(END,i->pid, i->tid);
    if(i->pid == 3 && i->tid==14)
    {
        sem_post(&sem1);
        sem_post(&sem2);
        sem_post(&sem3);
        sem_post(&sem4);
    }
    if(i->pid == 3)
    {
        sem_post(&semBarrier);
    }
    return NULL;
}

void *func_3(void *arg)
{
    struct_thread* i = ((struct_thread *)arg);
    sem_t* sem21 = sem_open("sem21", O_CREAT, 0644, 0);
    sem_t* sem41 = sem_open("sem41", O_CREAT, 0644, 0);

    if(i->pid == 5 && i->tid==4 && ok!=0)
    {
        sem_wait(sem41);
    }


    info(BEGIN, i->pid, i->tid);

    info(END, i->pid, i->tid);

    if(i->pid == 5 && i->tid==2 && ok!=0)
    {
        sem_post(sem21);
    }


    sem_close(sem21);
    sem_close(sem41);
    return NULL;
}



int main(){
    init();
    int p2, p3, p4, p5, p6, p7;
 
    info(BEGIN,1,0);
    sem_t* sem21 = sem_open("sem21", O_CREAT, 0644, 0);
    sem_t* sem41 = sem_open("sem41", O_CREAT, 0644, 0);
    sem_close(sem21);
    sem_close(sem41);
    p2 = fork();
    if(p2 == 0){
    
        info(BEGIN, 2, 0);
        p3 = fork();
        if(p3 == 0)
        {
            info(BEGIN, 3, 0);
            
            p5 = fork();
            if(p5 == 0)
            {
                info(BEGIN, 5, 0);
                p6 = fork();
                if(p6 == 0)
                    {
                        info(BEGIN, 6, 0);
                        
                        sem_init(&sem34, 0, 0);
                        sem_init(&sem43, 0, 0);
                         struct_thread threads[20];
                         pthread_t tid[20];
                         for(int i = 1 ; i < NO_OF_THREADS ; i++)
                         {
                             threads[i].tid = i;
                             threads[i].pid = 6;
                             pthread_create(&tid[i], NULL,func, &threads[i]);
                         }
                         
                          for(int i = NO_OF_THREADS-1 ; i >= 1 ; i--)
                         {
                             pthread_join(tid[i], NULL);
                         }
                         
                        
                       
                      info(END, 6, 0);
                      return 0;
                    }
                    else
                        {
                             waitpid(p6, NULL, 0);
                             struct_thread threads5[10];
                             pthread_t tid5[10];
                             for(int i = 1 ; i <= 5; i++)
                         {
                             threads5[i].tid = i;
                             threads5[i].pid = 5;
                             pthread_create(&tid5[i], NULL,func_3, &threads5[i]);
                         }
                        
                          for(int i = 1 ; i <= 5 ; i++)
                         {
                             pthread_join(tid5[i], NULL);
                         }
                            info(END, 5, 0);
                            return 0;
                        }
            }
            else
            {
                p7 = fork();
                if(p7 == 0){
                    info(BEGIN, 7, 0);
                    info(END, 7, 0);
                    return 0;
                }
                else
                {
                    
                    struct_thread threads3[50];
                    sem_init(&semBarrier, 0, 5);
                    pthread_t tid3[50];
                    sem_init(&sem1, 0, 0);
                    sem_init(&sem2, 0, 0);
                    sem_init(&sem3, 0, 0);
                    sem_init(&sem4, 0, 0);
                    sem_init(&sem14, 0, 0);
                    threads3[14].tid = 14;
                    threads3[14].pid = 3;
                    pthread_create(&tid3[14], NULL,func_2, &threads3[14]); 

                    for(int i = 1 ; i <= 4 ; i++)
                     {
                      threads3[i].tid = i;
                      threads3[i].pid = 3;
                      pthread_create(&tid3[i], NULL,func_2, &threads3[i]);        
                     }
                    
                    

                for(int i = 5 ; i <= 48 ; i++)
                     {
                      if(i!=14){
                      threads3[i].tid = i;
                      threads3[i].pid = 3;
                      pthread_create(&tid3[i], NULL,func_2, &threads3[i]);   
                      }     
                     }
                        
                for(int i = 1 ; i  <= 48 ; i++)
                     pthread_join(tid3[i], NULL);
                    
                    

                    waitpid(p7, NULL, 0);
                    waitpid(p5, NULL, 0);
                    info(END, 3, 0);
                }
            }
        }
        else
        {
            p4 = fork();
            if(p4 == 0){
                 info(BEGIN, 4, 0);
                 info(END, 4, 0);
                 return 0;
            }
            else
            {
                waitpid(p4, NULL, 0);
                waitpid(p3, NULL, 0);
                info(END, 2, 0);
            }
        }
   
    }
    else
        {
            waitpid(p2, NULL, 0);
            sem_destroy(sem21);
            sem_destroy(sem41);
            info(END, 1, 0);
        }


    return 0;
}
