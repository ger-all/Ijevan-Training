#include <iostream>
#include <unordered_set>

using namespace std;

void print(const unordered_set<int>& set) {
    cout << set.size() << endl;
    for (const int& num : set) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    unordered_set<int> first = { 1, 2, 3, 4, 5 };
    unordered_set<int> second = { 3, 4, 5, 6 };

    cout << "Input:\n";
    print(first);
    print(second);
    cout << endl;

    for (const int& num: second) {
        first.insert(num);
    }
    // կա՛մ first.insert(second.begin(), second.end());

    cout << "Output:\n" << first.size() << endl;

    return 0;
}

