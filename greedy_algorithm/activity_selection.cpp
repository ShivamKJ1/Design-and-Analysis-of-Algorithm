#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main() {
    int act[6]={1,2,3,4,5,6};
    int begin[6] = {0, 3, 1, 5, 5, 8};
    int end[6] = {6, 4, 2, 9, 7, 9};

    // Sort the end time array and corresponding starting times
    for (int i = 0; i < 5; i++) {
        for (int j = i+1; j < 6; j++) {
            if (end[i] > end[j]) {
                // Swap end times
                int temp1 = end[j];
                end[j] = end[i];
                end[i] = temp1;

                // Swap corresponding start times
                int temp2 = begin[j];
                begin[j] = begin[i];
                begin[i] = temp2;

                int temp3 = act[j];
                act[j] = act[i];
                act[i] = temp3;

                
            }
        }
    }
int lastendtime=-1;
int i;
for (i = 0; i < 6; i++) {
    if(begin[i]>=lastendtime){
        printf("Ativity - %d ; start time - %d ; end time - %d \n",act[i], begin[i], end[i]);
        lastendtime=end[i];

    }
        
}

return 0;
}

