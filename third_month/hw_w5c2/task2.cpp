#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buffer;                  // shared buffer (capacity = 1)
sem_t empty, full;           // semaphores
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);                // wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer = i;                      // produce item
        std::cout << "Produced: " << buffer << std::endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);                 // signal that buffer has data
        sleep(1);                        // only for demonstration
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);                 // wait for data
        pthread_mutex_lock(&mutex);

        int item = buffer;               // consume item
        std::cout << "Consumed: " << item << std::endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);                // signal buffer empty
        sleep(2);                        // only for demonstration
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, 1);   // counter == 1
    sem_init(&full, 0, 0);    // counter == 0
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

