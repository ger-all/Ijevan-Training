#include <iostream>
#include <sstream>
#include <set>

using namespace std;

void printInput(const string& str) {
	istringstream iss(str);
	string word;

	cout << "Input:\n";
	while (iss >> word) {
		cout << word << " ";
	}
	cout << "\n\n";
}

void printOutput(const multiset<string>& msWords) {
	cout << "Output:\n";
	set<string> uniqueWords(msWords.begin(), msWords.end());
		/** Second variant is :
			set<string> uniqueWords;
			for (const string& word : vWords) {
				uniqueWords.insert(word);
			}
		*/
	for (const string& w : uniqueWords) {
		cout << w << " " << msWords.count(w) << endl;
	}
	cout << endl;
}

int main() {
	string str = "apple orange apple banana orange apple";

	istringstream iss(str);   // դարձնում ենք string-ը stream
	string word;

	multiset<string> msWords;
	while (iss >> word) {     // կարդում ենք մինչև whitespace
		msWords.insert(word);
	}

	printInput(str);
	printOutput(msWords);

	return 0;
}

// O(n log n) է բարդությունը

