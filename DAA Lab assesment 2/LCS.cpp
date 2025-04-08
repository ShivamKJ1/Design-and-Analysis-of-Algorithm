#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

class Solution {
    vector<vector<int>> dp;
    set<string> result;

    void findAll(vector<string>& words1, vector<string>& words2, int i, int j, string curr) {
        while (i > 0 && j > 0) {
            if (words1[i - 1] == words2[j - 1]) {
                curr = words1[i - 1] + (curr.empty() ? "" : " ") + curr;
                i--;
                j--;
            } else {
                if (dp[i - 1][j] > dp[i][j - 1])
                    i--;
                else if (dp[i][j - 1] > dp[i - 1][j])
                    j--;
                else {
                    findAll(words1, words2, i - 1, j, curr);
                    findAll(words1, words2, i, j - 1, curr);
                    return;
                }
            }
        }
        if (curr.length() == dp[words1.size()][words2.size()])
            result.insert(curr);
    }

public:
    void LCS(string s1, string s2) {
        vector<string> words1, words2;
        string word;

        // Split s1 into words
        stringstream ss1(s1);
        while (ss1 >> word) words1.push_back(word);

        // Split s2 into words
        stringstream ss2(s2);
        while (ss2 >> word) words2.push_back(word);

        int m = words1.size(), n = words2.size();
        dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

        // Fill DP table using words, not characters
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (words1[i - 1] == words2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + words1[i - 1].length() + (dp[i - 1][j - 1] ? 1 : 0);
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // Find all LCS sequences
        findAll(words1, words2, m, n, "");

        // Print results
        for (const string& s : result)
            cout << s << endl;

        // Print the length of the LCS (including spaces)
        cout << "The length of the Longest Common Subsequence is: " << dp[m][n] << endl;
    }
};

int main() {
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    Solution sol;
    sol.LCS(s1, s2);

    return 0;
}
