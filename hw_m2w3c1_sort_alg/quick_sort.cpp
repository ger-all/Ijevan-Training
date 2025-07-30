#include <iostream>
#include <algorithm> //for std::swap
using namespace std;

void quick_sort(int arr[], int len);
void quick_sort(int arr[], int left, int right);
int partition(int arr[], int left, int right);

int main() {
	int testArr[] = {3, 4, 44, 15, 10, 18, 6};
    const int SIZE = sizeof(testArr) / sizeof(testArr[0]);
	quick_sort(testArr, SIZE);

    cout << "Array       : {3, 4, 44, 15, 10, 18, 6}" << endl;
    cout << "Sorted Array: {";
    for (int i = 0; i < SIZE - 1; ++i) {
        cout << testArr[i] << ", ";
    }
    cout << testArr[SIZE - 1] << "}" << endl;

	return 0;
}

void quick_sort(int arr[], int len) {
    quick_sort(arr, 0, len - 1);    
}

void quick_sort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivotIndex = partition(arr, left, right);

    quick_sort(arr, left, pivotIndex - 1);
    quick_sort(arr, pivotIndex + 1, right);
}

int partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= j && arr[i] <= pivot)
            i++;
        while (i <= j && arr[j] > pivot)
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }

    swap(arr[left], arr[j]);  // place pivot at correct position
    return j;
}

