#include <stdio.h>
#include <limits.h>

// Structure to store the result of a subarray
typedef struct {
    int maxSum;
    int left;
    int right;
} SubarrayResult;

// Function to find the maximum crossing subarray
SubarrayResult maxCrossingSubarray(int arr[], int left, int mid, int right) {
    int leftSum = INT_MIN, rightSum = INT_MIN;
    int sum = 0, maxLeft = mid, maxRight = mid + 1;

    // Find the maximum sum of the left half
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    sum = 0; // Reset sum for the right half
    // Find the maximum sum of the right half
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = i;
        }
    }

    SubarrayResult result = {leftSum + rightSum, maxLeft, maxRight};
    return result;
}

// Recursive function to find the maximum subarray using divide and conquer
SubarrayResult maxSubarray(int arr[], int left, int right) {
    if (left == right) {
        SubarrayResult result = {arr[left], left, right};
        return result;
    }

    int mid = (left + right) / 2;

    SubarrayResult leftResult = maxSubarray(arr, left, mid);
    SubarrayResult rightResult = maxSubarray(arr, mid + 1, right);
    SubarrayResult crossResult = maxCrossingSubarray(arr, left, mid, right);

    if (leftResult.maxSum >= rightResult.maxSum && leftResult.maxSum >= crossResult.maxSum)
        return leftResult;
    else if (rightResult.maxSum >= leftResult.maxSum && rightResult.maxSum >= crossResult.maxSum)
        return rightResult;
    else
        return crossResult;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Find the maximum subarray using divide and conquer
    SubarrayResult result = maxSubarray(arr, 0, n - 1);

    // Calculate the average daily sales for the maximum subarray
    double average = 0.0;
    int count = result.right - result.left + 1;
    for (int i = result.left; i <= result.right; i++) {
        average += arr[i];
    }
    average /= count;

    // Output the results
    printf("%d\n", result.maxSum);
    printf("%.2f\n", average);
    printf("[");
    for (int i = result.left; i <= result.right; i++) {
        printf("%d", arr[i]);
        if (i != result.right) {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}
