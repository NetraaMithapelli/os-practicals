#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

#define N 5     //No of philosophers and forks
#define ROUNDS 3  // No of times each philosopher eats

sem_t forks[N];  //creates semaphores for each fork
sem_t room;     //No of philospophers allowed

void *philosopher(void *arg){
    int id = *(int *)arg;        //id of current philosopher
    for(int round = 0; round < ROUNDS; round++){
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);


        //Get permission to try for forks
        sem_wait(&room);
        
        //Pick up left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up the left fork \n", id);

        //Pick up right fork
        sem_wait(&forks[(id+1) % N]);
        printf("Philosopher %d picked the right fork\n", id);

        //After picking both forks philospher can eat
        printf("Philosopher %d is eating (round %d). \n", id, round+1);
        sleep(1);   //PAuse to represent eating

        //Put back both forks 
        sem_post(&forks[(id+1) % N]);
        sem_post(&forks[id]);

        printf("Philosopher %d finished eating\n", id);

        //Leave the room once finished your work
        sem_post(&room);
    }
    printf("Philosopher %d finished all rounds \n", id);
    return NULL;
}

int main(){
    pthread_t philosophers[N];
    int ids[N]; //array to hold 5 philosopher ids

    for(int i=0; i<N; i++){
        sem_init(&forks[i], 0, 1);
    }

    //Let atmost 4 philosphers try to pick up forks at once
    sem_init(&room, 0, N-1);

    //Create one thread for each philospher
    for(int i=0; i<N; i++){
        ids[i] = i;             //Give this philospher its id

        //Start teh philosher func in new thread
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    //Wait for all five philosphers to finish
    for(int i=0; i<N; i++){
        pthread_join(philosophers[i], NULL);
    }

    //Clean up semaphoresafter all threads finished
    for(int i=0; i<N; i++){
        sem_destroy(&forks[i]);
    }
    sem_destroy(&room);

    printf("\nAll philosophers have finished . Program terminated");
    return 0;
}


