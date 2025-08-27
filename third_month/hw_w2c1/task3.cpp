#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    vector<string> inputVector = { "red", "blue", "green", "yellow", "red", "pink", "blue" };

    unordered_set<string> uniqueWords;
    string duplicate = "None";

    for (const string& word : inputVector) {
        auto result = uniqueWords.insert(word); // auto result is pair
        if (false == result.second) {
            duplicate = word;
            break;
        }        
    }

    cout << "Input:\n" << inputVector.size() << endl;
    for (const string& word : inputVector) {
        cout << word << " ";
    }
    cout << "\n\n";
    
    cout << "Output:\n" << duplicate << endl;

    return 0;
}

