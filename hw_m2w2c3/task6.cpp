#include <iostream>
using namespace std;

int gcd (int a, int b) {
    if (b == 0) return a;      // Base case
    return gcd(b, a % b);      // Recursive case
}

int main() {
    cout << "GCD of 8 and 6 is: " << gcd(8, 6) << endl;
    cout << "GCD of 48 and 18 is: " << gcd(48, 18) << endl;
    cout << "GCD of 100 and 25 is: " << gcd(100, 25) << endl;
    cout << "GCD of 7 and 3 is: " << gcd(7, 3) << endl;
    return 0;
}

