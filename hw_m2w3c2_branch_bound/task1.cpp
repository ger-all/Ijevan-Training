#include <iostream>
#include <vector>
using namespace std;

void task_1 (const vector<int>& nums);
void findSubs (int index, int currentSum, vector<int>& currentSub, const vector<int>& nums);
void printVector (vector<int>& sub);

int main() {
    vector<int> testNums = {3, 5, 6, 7, 8};
    task_1 (testNums);
    
    cout << endl;
    vector<int> testNums2 = {1, 2, 3, 4, 5, 6, 7, 8};
    task_1 (testNums2);

    return 0;
}

void task_1 (const vector<int>& nums) {
    vector<int> currentSub;
    findSubs (0, 0, currentSub, nums);
}

void findSubs(int index, int currentSum, vector<int>& currentSub, const vector<int>& nums) {
            
    if (currentSum > 12) return;

    if (index == nums.size()) {
        if (currentSum == 12) {
            printVector(currentSub);
        }
        return;
    }
    // 1. Ներառել nums[index]
    currentSub.push_back(nums[index]); // add next element
    findSubs(index + 1, currentSum + nums[index], currentSub, nums);
    currentSub.pop_back();
    
    // 2. Չներառել nums[index]
    findSubs(index + 1, currentSum, currentSub, nums);
}

void printVector (vector<int>& sub) {
    cout << "{ ";
    for (const auto& num : sub) {
        cout << num << " ";
    }
    cout << "}" << endl;
}

