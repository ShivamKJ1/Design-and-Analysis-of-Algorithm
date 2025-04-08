#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the maximum sum subarray using Kadane's Algorithm
int maxSubArraySum(vector<int>& nums) {
    int max_sum = nums[0];
    int current_sum = nums[0];

    for (size_t i = 1; i < nums.size(); i++) {
        current_sum = max(nums[i], current_sum + nums[i]);
        max_sum = max(max_sum, current_sum);
    }

    return max_sum;
}

int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int max_sum = maxSubArraySum(nums);
    cout << "Maximum sum of the subarray is: " << max_sum << endl;

    return 0;
}