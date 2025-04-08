#include <iostream>
#include <string>
#include <vector>
using namespace std;

int longestCommonSubsequence(string text1, string text2){
    int m=text1.length();
    int n=text2.length();
    
    //the line below is the most important line of this code

    vector<vector<int>> dp(m+1, vector<int>(n+1,0));

    //the line above is the most important line of this code


    for(int i=1;i<=m;i++){
        for(int j=1; j<=n;j++){
            if(text1[i-1]==text2[j-1]){  //very important condition
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else{
                dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
     
    return dp[m][n];
}

int main(){
    
    string text1,text2;
    
    getline(cin,text1);
    getline(cin,text2);
    
    cout<<longestCommonSubsequence(text1,text2)<<endl;
    
    return 0;
}