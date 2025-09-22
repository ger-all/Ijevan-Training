#include <iostream>
#include <pthread.h>
#include <unistd.h>

/* Useful:
 * If you open the comment and use the "./out | ws -l" command in bush,
 *  you will see 401 (Each thread: 100).
 */

int counter = 0;               // shared variable
pthread_mutex_t mutex;         // mutex for synchronization

void* increment(void* arg) {
    for (int j = 0; j < 100; j++) {
        pthread_mutex_lock(&mutex);
//std::cout << counter << std::endl;
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void* decrement(void* arg) {
    for (int j = 0; j < 100; j++) {
        pthread_mutex_lock(&mutex);
//std::cout << counter << std::endl;
        counter--;
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main() {
    pthread_t t1, t2, t3, t4;

    pthread_mutex_init(&mutex, nullptr);

    // 2 increment threads
    pthread_create(&t1, nullptr, increment, nullptr);
    pthread_create(&t2, nullptr, increment, nullptr);

    // 2 decrement threads
    pthread_create(&t3, nullptr, decrement, nullptr);
    pthread_create(&t4, nullptr, decrement, nullptr);

    // wait for all threads
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);

    pthread_mutex_destroy(&mutex);

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}

