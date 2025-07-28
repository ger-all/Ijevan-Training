#include <iostream>
using namespace std;

void printNumRec(int n) {
    if (n == 1) {
        cout<<n;
        return;
    }
    if (n > 1) {
        printNumRec(n-1);
        cout<< " " << n;
    }
}

int main() {
    printNumRec (5);
    return 0;
}

