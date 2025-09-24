#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>   // sleep

// Global variables
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cv  = PTHREAD_COND_INITIALIZER;
bool bBooked = false;

void* bookTickets(void* arg) {
    sleep(2); // Simulate delay
    pthread_mutex_lock(&mtx);
    
    bBooked = true;
    printf("Friend: Court is booked!\n");
    
    // Wake up waiting thread
    pthread_cond_signal(&cv);
    
    pthread_mutex_unlock(&mtx);
    return NULL;
}

void* getReadyForVacation(void* arg) {
    printf("You: Hey, You booked the tickets?\n");
    
    pthread_mutex_lock(&mtx);
    
    // always use while, not if
    while (!bBooked) {
        pthread_cond_wait(&cv, &mtx);
    }
    
    printf("You: Yayyy!!\n");
    
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    // Ստեղծում ենք երկու Thread
    pthread_create(&t1, NULL, getReadyForVacation, NULL);
    pthread_create(&t2, NULL, bookTickets, NULL);
    
    // Սպասում ենք, որ Thread-ները ավարտեն
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // մաքրում ենք ռեսուրսները
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);
    
    return 0;
}

