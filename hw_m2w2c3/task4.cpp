#include <iostream>
using namespace std;

int F(int i) {
    if (i < 0) {
        cout << "F function isn't defined: i is negative number" << endl;
        return -1;
    }
    if (i == 0) return 0;
    if (i == 1) return 5;
    if (i == 2) return 3;
    if (i == 3) return 4;
    if (i == 4) return 4;
    return F(i-5) * F(i-4) + F(i-2);
}

int main() {
    cout << F (5);
    return 0;
}

