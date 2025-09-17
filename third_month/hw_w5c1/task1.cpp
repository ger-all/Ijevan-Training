#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

int main() {
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;

    int fd[2]; // pipe file descriptors
    if (pipe(fd) == -1) {
        std::cerr << "Pipe failed\n";
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork failed\n";
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(fd[0]); // Close unused read end

        unsigned long long fact = factorial(n);
        write(fd[1], &fact, sizeof(fact));

        close(fd[1]); // Close write end
        return 0;
    } else {
        // Parent process
        close(fd[1]); // Close unused write end

        unsigned long long result;
        read(fd[0], &result, sizeof(result));
        close(fd[0]);

        wait(NULL); // Wait for child to finish

        std::cout << "Factorial of " << n << " is: " << result << std::endl;
    }

    return 0;
}

