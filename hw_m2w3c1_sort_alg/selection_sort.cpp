#include <iostream>
using namespace std;

void selection_sort(int arr[], int len) {
    int min, ind, temp;
    for (int i = 0; i < len; ++i) {
        min = arr[i];
        ind = i;
        for (int j = i + 1; j < len; ++j) {
            if (arr[j] < min) {
                min = arr[j];
                ind = j;
            }
        }
        temp = arr[ind];
        arr[ind] = arr[i];
        arr[i] = temp;
    }
}

int main() {
	int testArr[] = {3, 4, 44, 15, 10, 18, 6};
    const int SIZE = sizeof(testArr) / sizeof(testArr[0]);
	selection_sort(testArr, SIZE);

    cout << "Array       : {3, 4, 44, 15, 10, 18, 6}" << endl;
    cout << "Sorted Array: {";
    for (int i = 0; i < SIZE - 1; ++i) {
        cout << testArr[i] << ", ";
    }
    cout << testArr[SIZE - 1] << "}" << endl;

	return 0;
}

