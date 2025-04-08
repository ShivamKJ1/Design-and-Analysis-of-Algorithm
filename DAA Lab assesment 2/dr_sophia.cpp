#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Solution {
private:
    vector<vector<int>> dp;
    set<string> result;
    
    void findAllLCS(string& s1, string& s2, int i, int j, string current) {
        if (i == 0 || j == 0) {
            if (current.length() == dp[s1.length()][s2.length()]) {
                result.insert(current);
            }
            return;
        }
        
        if (s1[i - 1] == s2[j - 1]) {
            findAllLCS(s1, s2, i - 1, j - 1, s1[i - 1] + current);
        } else {
            if (dp[i - 1][j] == dp[i][j]) {
                findAllLCS(s1, s2, i - 1, j, current);
            }
            if (dp[i][j - 1] == dp[i][j]) {
                findAllLCS(s1, s2, i, j - 1, current);
            }
        }
    }

public:
    void findLCS(string& s1, string& s2) {
        int m = s1.length();
        int n = s2.length();
        
        if (m == 0 || n == 0) {
            cout << "All possible unique LCS combinations:" << endl;
            cout << "Length of LCS: 0" << endl;
            return;
        }

        dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        findAllLCS(s1, s2, m, n, "");
        
        cout << "All possible unique LCS combinations:" << endl;
        for (const string& s : result) {
            cout << s << endl;
        }
        cout << "Length of LCS: " << dp[m][n] << endl;
    }
};

int main() {
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    
    Solution sol;
    sol.findLCS(s1, s2);
    
    return 0;
}
