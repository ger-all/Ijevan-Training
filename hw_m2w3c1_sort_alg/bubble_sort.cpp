#include <iostream>
using namespace std;

void bubble_sort(int arr[], int len) {
    int temp;
    for (int i = len - 2; i >= 0; --i) {
        for (int j = 0 ; j <= i; ++j) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
	int testArr[] = {3, 4, 44, 15, 10, 18, 6};
    const int SIZE = sizeof(testArr) / sizeof(testArr[0]);
	bubble_sort(testArr, SIZE);

    cout << "Array       : {3, 4, 44, 15, 10, 18, 6}" << endl;
    cout << "Sorted Array: {";
    for (int i = 0; i < SIZE - 1; ++i) {
        cout << testArr[i] << ", ";
    }
    cout << testArr[SIZE - 1] << "}" << endl;

	return 0;
}

