#include <iostream>
using namespace std;

void insertion_sort(int arr[], int len) {
    int temp;
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0; --j) {
            if (arr[j] < arr[j - 1]) {
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

int main() {
	int testArr[] = {3, 4, 44, 15, 10, 18, 6};
    const int SIZE = sizeof(testArr) / sizeof(testArr[0]);
	insertion_sort(testArr, SIZE);

    cout << "Array       : {3, 4, 44, 15, 10, 18, 6}" << endl;
    cout << "Sorted Array: {";
    for (int i = 0; i < SIZE - 1; ++i) {
        cout << testArr[i] << ", ";
    }
    cout << testArr[SIZE - 1] << "}" << endl;

	return 0;
}

