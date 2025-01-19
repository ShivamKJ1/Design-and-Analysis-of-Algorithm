#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Helper function to multiply two numbers using Karatsuba
string karatsuba(string num1, string num2) {
    if (num1.length() == 1 && num2.length() == 1) {
        long long n1 = stoll(num1);
        long long n2 = stoll(num2);
        return to_string(n1 * n2);
    }
    
    int len = max(num1.length(), num2.length());
    while (num1.length() < len) num1 = "0" + num1;
    while (num2.length() < len) num2 = "0" + num2;
    
    if (len % 2 == 1) {
        num1 = "0" + num1;
        num2 = "0" + num2;
        len++;
    }
    
    int mid = len / 2;
    string a = num1.substr(0, len - mid);
    string b = num1.substr(len - mid);
    string c = num2.substr(0, len - mid);
    string d = num2.substr(len - mid);
    
    // Recursive steps
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    
    // Calculate (a+b)(c+d)
    string ab_sum = to_string(stoll(a) + stoll(b));
    string cd_sum = to_string(stoll(c) + stoll(d));
    string abcd = karatsuba(ab_sum, cd_sum);
    
    // Calculate middle term
    string middle = to_string(stoll(abcd) - stoll(ac) - stoll(bd));
    
    // Combine results
    for (int i = 0; i < 2 * mid; i++) ac += "0";
    for (int i = 0; i < mid; i++) middle += "0";
    
    string result = to_string(stoll(ac) + stoll(middle) + stoll(bd));
    return result;
}

// Function to multiply matrices element-wise
vector<vector<string>> multiplyMatrices(vector<vector<string>>& mat1, vector<vector<string>>& mat2, int n) {
    vector<vector<string>> result(n, vector<string>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = karatsuba(mat1[i][j], mat2[i][j]);
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    
    // Read first matrix
    vector<vector<string>> matrix1(n, vector<string>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix1[i][j];
        }
    }
    
    // Read second matrix
    vector<vector<string>> matrix2(n, vector<string>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix2[i][j];
        }
    }
    
    // Compute element-wise product
    vector<vector<string>> result = multiplyMatrices(matrix1, matrix2, n);
    
    // Print result
    cout << "Resultant matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}