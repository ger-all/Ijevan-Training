#include <iostream>
#include <pthread.h>
#include <cstdlib> // for exit

// Thread function to compute factorial
void* computeFactorial(void* arg) {
    int n = *((int*)arg);
    unsigned long long* result = new unsigned long long(1);

    for (int i = 2; i <= n; ++i)
        *result *= i;

    pthread_exit(result); // return pointer to result
}

int main() {
    int n, r;
    std::cout << "Enter n and r: ";
    std::cin >> n >> r;

    if (r > n || n < 0 || r < 0) {
        std::cerr << "Invalid input\n";
        return 1;
    }

    pthread_t t1, t2;
    int numerator_input = n;
    int denominator_input = n - r;

    // Create threads
    if (pthread_create(&t1, nullptr, computeFactorial, &numerator_input) != 0) {
        std::cerr << "Failed to create numerator thread\n";
        return 1;
    }

    if (pthread_create(&t2, nullptr, computeFactorial, &denominator_input) != 0) {
        std::cerr << "Failed to create denominator thread\n";
        return 1;
    }

    // Collect results
    void* num_ret;
    void* den_ret;

    pthread_join(t1, &num_ret);
    pthread_join(t2, &den_ret);

    unsigned long long numerator = *((unsigned long long*)num_ret);
    unsigned long long denominator = *((unsigned long long*)den_ret);

    delete (unsigned long long*)num_ret;
    delete (unsigned long long*)den_ret;

    unsigned long long permutation = numerator / denominator;
    std::cout << "P(" << n << "," << r << ") = " << permutation << std::endl;

    return 0;
}

