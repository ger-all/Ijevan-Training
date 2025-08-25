#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<string> fruits = { "apple", "banana", "apricot", "cherry" };
	char startLetter = 'a';

	int count = count_if(fruits.cbegin(), fruits.cend(), 
		[startLetter](const string& str) {
			return str.at(0) == startLetter;
		}
	);
	
	cout << "Number of names starting with '" << startLetter << "' = " << count << endl;

	return 0;
}

