#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_rw;   // protects readcount
pthread_mutex_t wrt;        // writer lock
int readcount = 0;
int data = 0;

void* reader(void* arg) {
    int id = *((int*)arg);

    pthread_mutex_lock(&mutex_rw);
    readcount++;
    if(readcount == 1)
        pthread_mutex_lock(&wrt);  // block writers
    pthread_mutex_unlock(&mutex_rw);

    printf("Reader %d is reading data: %d\n", id, data);
    sleep(1);

    pthread_mutex_lock(&mutex_rw);
    readcount--;
    if(readcount == 0)
        pthread_mutex_unlock(&wrt);
    pthread_mutex_unlock(&mutex_rw);

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    pthread_mutex_lock(&wrt);  
    data += 5;
    printf("Writer %d modified data to: %d\n", id, data);
    sleep(2);
    pthread_mutex_unlock(&wrt);

    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int r_id[5] = {1,2,3,4,5};
    int w_id[2] = {1,2};

    pthread_mutex_init(&mutex_rw, NULL);
    pthread_mutex_init(&wrt, NULL);

    // create 5 readers
    for(int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &r_id[i]);

    // create 2 writers
    for(int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &w_id[i]);

    // wait for all threads
    for(int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    for(int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex_rw);
    pthread_mutex_destroy(&wrt);

    return 0;
}
