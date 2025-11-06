#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex_pc;

void* producer(void* arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        item = i + 1;

        sem_wait(&empty);              // wait for empty slot
        pthread_mutex_lock(&mutex_pc); // enter critical section

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex_pc);
        sem_post(&full);               // signal item available

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for(int i = 0; i < 10; i++) {

        sem_wait(&full);               // wait for filled slot
        pthread_mutex_lock(&mutex_pc); // enter critical section

        item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex_pc);
        sem_post(&empty);              // signal empty slot

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex_pc, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex_pc);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
