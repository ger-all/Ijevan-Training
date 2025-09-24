#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>   // sleep

// Global variables
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cv  = PTHREAD_COND_INITIALIZER;
bool bBooked = false;

void* bookTickets(void* arg) {
    sleep(3); // Simulate delay
    pthread_mutex_lock(&mtx);
    
    bBooked = true;
    printf("Booking Friend: Court is booked!\n");
    
    // Wake up waiting thread
    pthread_cond_broadcast(&cv);
    
    pthread_mutex_unlock(&mtx);
    return NULL;
}

void* getReadyForVacation(void* arg) {
    int fNum = *((int*)arg);
    printf("Friend %d: Hey, You booked the tickets?\n", fNum);
    
    pthread_mutex_lock(&mtx);
    
    // always use while, not if
    while (!bBooked) {
        pthread_cond_wait(&cv, &mtx);
    }
    
    printf("Friend %d: Yayyy!!\n", fNum);
    
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main() {
    pthread_t thrdBook, thrdFriends[5];
    int friendNums[5];

    // Create Threads
    for (int i = 0; i < 5; ++i) {
        friendNums[i] = i + 1;
        pthread_create(&thrdFriends[i], NULL, getReadyForVacation, &friendNums[i]);
    }   
    pthread_create(&thrdBook, NULL, bookTickets, NULL);
    
    // Սպասում ենք, որ Thread-ները ավարտեն
    for (int i = 0; i < 5; ++i) {
        pthread_join(thrdFriends[i], NULL);
    }
    pthread_join(thrdBook, NULL);
    
    // մաքրում ենք ռեսուրսները
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);
    
    return 0;
}

