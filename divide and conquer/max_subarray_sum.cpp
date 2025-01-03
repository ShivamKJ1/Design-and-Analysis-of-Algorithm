int maxSubArray(int* nums, int numsSize) {
   int currentSum=0;
   int maxSum = -2147483648;

   int i;
   for(i=0;i<numsSize;i++){
    currentSum+=nums[i];
    maxSum=(currentSum>maxSum)?currentSum:maxSum;

    if(currentSum<0){
        currentSum=0;
    }


   }
return maxSum;
}



