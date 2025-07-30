#include <iostream>
using namespace std;

void merge_sort(int arr[], int len);
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main() {
	int testArr[] = {3, 4, 44, 15, 10, 18, 6};
    const int SIZE = sizeof(testArr) / sizeof(testArr[0]);
	merge_sort(testArr, SIZE);

    cout << "Array       : {3, 4, 44, 15, 10, 18, 6}" << endl;
    cout << "Sorted Array: {";
    for (int i = 0; i < SIZE - 1; ++i) {
        cout << testArr[i] << ", ";
    }
    cout << testArr[SIZE - 1] << "}" << endl;

	return 0;
}

void merge_sort(int arr[], int len) {
    merge_sort(arr, 0, len - 1);    
}

void merge_sort(int arr[], int left, int right) {
    // cout << "merge_sort(arr[], " << left << ", " << right << "..) finction is called" << endl;
    if (left >= right) return;

    int mid = (left + right) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void merge(int arr[], int left, int mid, int right) {
    int newArr[right - left + 1];
    int i = left;
    int j = mid + 1;
    int ind = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j])
            newArr[ind++] = arr[i++];
        else
            newArr[ind++] = arr[j++];
    }

    while (i <= mid)
        newArr[ind++] = arr[i++];
    while (j <= right)
        newArr[ind++] = arr[j++];
    
    for (int k = 0; k < ind; ++k)
        arr[left + k] = newArr[k];
}

