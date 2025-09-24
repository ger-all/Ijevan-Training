#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>   // sleep

// Global variables
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cv  = PTHREAD_COND_INITIALIZER;
const int Number = 5;
unsigned int turn = 0;

void* zero(void* arg) {
    for(int i = 1; i <= Number; ++i) {
        pthread_mutex_lock(&mtx);

        while (turn != 0) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("0");
        fflush(stdout);
 
        turn = (i % 2 == 1) ? 1 : 2;  // Odd turn or Even turn

        // Wake up waiting thread
        pthread_cond_broadcast(&cv);

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

void* odd(void* arg) {
    for(int i = 1; i <= Number * 2; i += 2) {
        pthread_mutex_lock(&mtx);

        while (turn != 1) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("%d", i);
        fflush(stdout);

        turn = 0;

        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

void* even(void* arg) {
    for(int i = 2; i <= Number * 2; i += 2) {
        pthread_mutex_lock(&mtx);

        while (turn != 2) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("%d", i);
        fflush(stdout);

        turn = 0;

        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}


int main() {
    pthread_t threads[3];

    // Create Threads
    pthread_create(&threads[0], NULL, zero, NULL);
    pthread_create(&threads[1], NULL, even, NULL);
    pthread_create(&threads[2], NULL, odd, NULL);

    // Սպասում ենք, որ Thread-ները ավարտեն
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    // մաքրում ենք ռեսուրսները
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}

