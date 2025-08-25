#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> numbers = { 5, 1, 2, 10, 1, 4 };
	cout << "Even numbers: ";

	for_each(numbers.begin(), numbers.end(), 
		[](const int& num) { 
			if (0 == num % 2)
				cout << num << ' ';
		}
	);

	cout << endl;

	return 0;
}

