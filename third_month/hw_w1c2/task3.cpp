#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<string> names = {"Bob", "Alex", "Christina", "Zoe", "Anna"};

    sort(names.begin(), names.end(), [](const string& a, const string& b) -> bool {
        if (a.size() != b.size())
            return a.size() < b.size();  // shorter first
        return a < b;                    // alphabetical if same length
    });

    for (const auto& name : names)
        cout << name << " ";
    cout << "\n";

    return 0;
}

