#include <iostream>
using namespace std;

int power(int a, int b) {
    if (b < 0) {
        cout << "Power isn't defined: b is negative number" << endl;
        return -1;
    } else if (b == 0) {
        return 1;
    } else {
        return a * power(a, b - 1);
    }
}

int main() {
    cout << power (2, 5);
    return 0;
}

