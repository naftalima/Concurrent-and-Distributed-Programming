#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <semaphore.h>

#define THREAD_NUM 100

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

int buffer[15];
int count = 0;

void* DesejoCortarCabelo(void* args) {
    while (1) {
        // Produce
        int x = rand() % 100;
        sleep(1);

        // Add to the buffer
        sem_wait(&semEmpty);//semwait decrement semaphore and waitif its zero or same post to increment it]
        //if semempty is zero means that there are no slots on the semaphore so we should wait
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        printf("%d esperando \n", x);
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);//sempost increments semaphore once the buffer was incremented 
    }
}

void* CortarCabelo(void* args) {
    while (1) {
        int y;

        // Remove from the buffer
        sem_wait(&semFull);//because we want to wait until theres at least one element wait until its more then zero 
        //waits until the DesejoCortarCabelo puts a element in the buffer 
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[0];
        for (int i = 0 ; i < count-1 ; i++){
            buffer[i]=buffer[i+1];
        }
        count--;
        printf("-> %d cortou o cabelo. \n", y);
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        // Consume
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 15);
    sem_init(&semFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
       int x = (rand() % 100)%2;
        if (x == 0) {
            if (pthread_create(&th[i], NULL, &DesejoCortarCabelo, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &CortarCabelo, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}