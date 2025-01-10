#include <stdio.h>
#include <limits.h>

// Function to find the maximum of three integers
int max(int a, int b, int c) {
    return (a > b) ? (a > c ? a : c) : (b > c ? b : c);
}

// Function to find the maximum sum of a subarray that crosses the midpoint
int maxCrossingSum(int arr[], int left, int mid, int right) {
    int sum = 0;
    int left_sum = INT_MIN;

    // Traverse from mid to left
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;

    // Traverse from mid+1 to right
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    // Return the maximum sum of the crossing subarray
    return left_sum + right_sum;
}

// Function to find the maximum sum subarray using divide and conquer
int maxSubarraySum(int arr[], int left, int right) {
    // Base case: only one element
    if (left == right)
        return arr[left];

    int mid = (left + right) / 2;

    // Return the maximum of:
    // 1. Maximum subarray sum in the left half
    // 2. Maximum subarray sum in the right half
    // 3. Maximum subarray sum crossing the midpoint
    return max(
        maxSubarraySum(arr, left, mid),
        maxSubarraySum(arr, mid + 1, right),
        maxCrossingSum(arr, left, mid, right)
    );
}

// Main function to test the code
int main() {
    int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int max_sum = maxSubarraySum(arr, 0, n - 1);
    printf("Maximum sum of the subarray is: %d\n", max_sum);

    return 0;
}
