#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int matrixChainMultiplication(vector<int>& dimensions) {
    int n = dimensions.size() - 1; 
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    
    for (int chainLen = 2; chainLen <= n; chainLen++) {
        for (int i = 0; i < n - chainLen + 1; i++) {  //most important part of code
            int j = i + chainLen - 1;
            dp[i][j] = INT_MAX;
            
            
            for (int k = i; k < j; k++) {
                int operations = dp[i][k] + dp[k+1][j] + dimensions[i] * dimensions[k+1] * dimensions[j+1];
                               
                if (operations < dp[i][j]) {
                    dp[i][j] = operations;
                }
            }
        }
    }
    
    
    return dp[0][n-1];
}

int main() {
    
    int n;
    cin >> n;
    
    vector<int> dimensions(n);
    for (int i = 0; i < n; i++) {
        cin >> dimensions[i];
    }
    
    cout << matrixChainMultiplication(dimensions) << endl;
    
    return 0;
}