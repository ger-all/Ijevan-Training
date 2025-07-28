#include <iostream>
using namespace std;

int factorial(int n) {
    if (n < 0) {
	cout << "Factorial isn't defined for negative numbers";
	return -1;
    } else if (n <= 1) {
        return 1;
    } else (n > 1) {
        return n * factorial(n-1);
    }
}

int main() {
    cout << factorial (5);
    return 0;
}

