#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int matrixChainMultiplication(vector<int>& dimensions) {
    int n = dimensions.size() - 1; // Number of matrices
    
    // Create dp table for storing minimum operations
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // Chain length starts from 2 to n
    for (int chainLen = 2; chainLen <= n; chainLen++) {
        for (int i = 0; i < n - chainLen + 1; i++) {
            int j = i + chainLen - 1;
            dp[i][j] = INT_MAX;
            
            // Try all possible splits and find minimum
            for (int k = i; k < j; k++) {
                int operations = dp[i][k] + dp[k+1][j] + 
                               dimensions[i] * dimensions[k+1] * dimensions[j+1];
                               
                if (operations < dp[i][j]) {
                    dp[i][j] = operations;
                }
            }
        }
    }
    
    // Return minimum operations needed for entire chain
    return dp[0][n-1];
}

int main() {
    // Read number of dimensions
    int n;
    cin >> n;
    
    // Read dimensions array
    vector<int> dimensions(n);
    for (int i = 0; i < n; i++) {
        cin >> dimensions[i];
    }
    
    // Calculate and print result
    cout << matrixChainMultiplication(dimensions) << endl;
    
    return 0;
}