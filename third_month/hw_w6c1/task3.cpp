#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>   // sleep

// Global variables
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cv  = PTHREAD_COND_INITIALIZER;
bool turn = false;
const int Number = 10;

void* ping(void* arg) {
    for(int i = 0; i < Number / 2; ++i) {
        pthread_mutex_lock(&mtx);

        while (turn) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("Ping: \n");
        turn = true;

        // Wake up waiting thread
        pthread_cond_signal(&cv);

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

void* pong(void* arg) {
    for(int i = 0; i < Number / 2; ++i) {
        pthread_mutex_lock(&mtx);

        while (!turn) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("Pong: \n");
        turn = false;

        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

int main() {
    pthread_t A, B;

    // Create Threads
    pthread_create(&A, NULL, ping, NULL);
    pthread_create(&B, NULL, pong, NULL);

    // Սպասում ենք, որ Thread-ները ավարտեն
    pthread_join(A, NULL);
    pthread_join(B, NULL);

    // մաքրում ենք ռեսուրսները
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}

