#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
	vector<int> vNumbers = { 1, 2, 2, 3, 4, 1, 5, 3 };
	unordered_set<int> setNumbers;

	for (const int& num : vNumbers) {
		setNumbers.insert(num);
	}

	cout << "Input:   ";
	for (const int& num : vNumbers) {
		cout << num << ' ';
	}
	cout << endl;
	cout << "Output:  " << setNumbers.size() << endl;

	return 0;
}

// O(n) է բարդությունը
// Իսկ ներդրված ցիկլերի (Brute force) տարբերակով՝ Օ(n²)

