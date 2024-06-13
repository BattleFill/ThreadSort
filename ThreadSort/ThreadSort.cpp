#include <iostream>
#include <vector>
#include <thread>
using namespace std;
class MergeSort {
public:
    void Sort(vector<int>& arr) {
        if (arr.size() <= 1) return;
        vector<int> left(arr.begin(), arr.begin() + arr.size() / 2); vector<int> right(arr.begin() + arr.size() / 2, arr.end());
        thread leftThread(&MergeSort::Sort, this, ref(left)); thread rightThread(&MergeSort::Sort, this, ref(right));
        leftThread.join(); rightThread.join();
        Merge(arr, left, right);
    }
private:
    void Merge(vector<int>& arr, vector<int>& left, vector<int>& right) {
        size_t leftIndex = 0, rightIndex = 0, mergeIndex = 0;
        while (leftIndex < left.size() && rightIndex < right.size()) {
            if (left[leftIndex] < right[rightIndex]) {
                arr[mergeIndex++] = left[leftIndex++];
            }
            else {
                arr[mergeIndex++] = right[rightIndex++];
            }
        }
        while (leftIndex < left.size()) {
            arr[mergeIndex++] = left[leftIndex++];
        }
        while (rightIndex < right.size()) {
            arr[mergeIndex++] = right[rightIndex++];
        }
    }
};
int main() {
    vector<int> arr(10);
    cout << "You can write here 10 nummers!!!\n";
    for (int& num : arr) {
        cin >> num;
    }
    MergeSort mergeSort;
    thread mergeSortThread([&mergeSort, &arr]() {
        mergeSort.Sort(arr);
        });
    mergeSortThread.join();
    cout << "Sorted array: ";
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}