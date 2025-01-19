#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Helper function to make strings equal length
string makeEqualLength(string str1, string str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 < len2) {
        for (int i = 0; i < len2 - len1; i++)
            str1 = '0' + str1;
    }
    return str1;
}

// Helper function to add two strings
string addStrings(string first, string second) {
    string result;
    int carry = 0;
    int i = first.length() - 1;
    int j = second.length() - 1;
    
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += first[i--] - '0';
        if (j >= 0) sum += second[j--] - '0';
        carry = sum / 10;
        result = char(sum % 10 + '0') + result;
    }
    return result;
}

// Helper function to subtract strings
string subtractStrings(string first, string second) {
    string result;
    int carry = 0;
    int n1 = first.length(), n2 = second.length();
    
    for (int i = n1 - 1; i >= 0; i--) {
        int sub = ((first[i] - '0') - (i >= n1 - n2 ? second[i - (n1 - n2)] - '0' : 0) - carry);
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else
            carry = 0;
        result = char(sub + '0') + result;
    }
    
    while (result.length() > 1 && result[0] == '0')
        result.erase(0, 1);
    
    return result;
}

// Karatsuba multiplication
string karatsuba(string num1, string num2) {
    if (num1.length() == 1 && num2.length() == 1) {
        int n1 = num1[0] - '0';
        int n2 = num2[0] - '0';
        int product = n1 * n2;
        return to_string(product);
    }
    
    int len = max(num1.length(), num2.length());
    num1 = makeEqualLength(num1, num2);
    num2 = makeEqualLength(num2, num1);
    
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
    
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string abcd = karatsuba(addStrings(a, b), addStrings(c, d));
    
    string temp = subtractStrings(subtractStrings(abcd, ac), bd);
    
    for (int i = 0; i < 2 * mid; i++) ac += "0";
    for (int i = 0; i < mid; i++) temp += "0";
    
    string result = addStrings(addStrings(ac, temp), bd);
    
    while (result.length() > 1 && result[0] == '0')
        result.erase(0, 1);
    
    return result;
}

// Function to compute power using Karatsuba multiplication
string computePower(string base, int exponent) {
    if (exponent == 0) return "1";
    if (exponent == 1) return base;
    
    string result = computePower(base, exponent / 2);
    result = karatsuba(result, result);
    
    if (exponent % 2 == 1) {
        result = karatsuba(result, base);
    }
    
    return result;
}

int main() {
    string x;
    int y;
    cin >> x >> y;
    cout << computePower(x, y) << endl;
    return 0;
}