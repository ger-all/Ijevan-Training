#include <iostream>
using namespace std;

bool palindromeCycle (string);
void palRec (string);
bool palRec (string, int left, int right);

int main() {
    cout << palindromeCycle ("madam") << endl;
    palRec ("madam");

    cout << palindromeCycle ("moom") << endl;
    palRec ("moom");

    cout << palindromeCycle ("hello") << endl;
    palRec ("hello");

    return 0;
}

void palRec (string str) {
    cout << "Is palindrome? " << palRec (str, 0, str.length() - 1) << endl;
}

bool palRec (string str, int left, int right) {
    if (left >= right) return true;
    if (str.at(left) != str.at(right)) return false;
    return palRec (str, left + 1, right - 1);
}

bool palindromeCycle (string str) {
    int len = str.length();
    for (int i=0; i < len/2; i++) {
        if (str.at(i) != str.at(len-1-i)) {
            return false;
        }
    }
    return true;
}

