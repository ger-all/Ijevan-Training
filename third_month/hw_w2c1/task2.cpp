#include <iostream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

int main() {
    string str = "apple orange apple banana orange apple";
    istringstream iss(str);
    string word;

    // Step 1. Count frequencies in O(n)
    unordered_map<string, int> freq;
    while (iss >> word) {
        ++freq[word];
    }

    // Step 2. Print in sorted order
    cout << "Input:\n" << str << "\n\n";
    cout << "Output:\n";

    // O(k log k) է (k-ն՝ տարբեր բառերի քանակը)։
    map<string, int> sorted(freq.begin(), freq.end()); // automatically sorted by key
    for (const auto& p : sorted) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}

