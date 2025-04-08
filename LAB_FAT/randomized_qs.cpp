// randomixed qs and  difference of sum of two halves of sorted array
#include <bits/stdc++.h>
using namespace std;

// Function to partition the array using a random pivot
int partition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to perform Randomized QuickSort
void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    int n;
    cin >> n;
    
    if (n % 2 != 0) {
        cout << "Invalid input! Please enter an even number." << endl;
        return 0;
    }
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    srand(time(0)); // Seed for random pivot selection
    randomizedQuickSort(arr, 0, n - 1);
    
    // Print sorted array
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    // Compute absolute difference between sums of two halves
    int sum1 = accumulate(arr.begin(), arr.begin() + n / 2, 0);
    int sum2 = accumulate(arr.begin() + n / 2, arr.end(), 0);
    cout << abs(sum1 - sum2) << endl;
    
    return 0;
}
