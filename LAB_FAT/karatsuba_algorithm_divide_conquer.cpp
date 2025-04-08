#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Helper function to add leading zeros to make the lengths of the numbers equal
string addLeadingZeros(string str, int num) {
    for (int i = 0; i < num; i++) {
        str = "0" + str;
    }
    return str;
}

// Helper function to remove leading zeros from a string
string removeLeadingZeros(string str) {
    while (str.length() > 1 && str[0] == '0') {
        str = str.substr(1);
    }
    return str;
}

// Function to add two large numbers represented as strings
string addStrings(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    
    if (len1 < len2) {
        num1 = addLeadingZeros(num1, len2 - len1);
    } else if (len2 < len1) {
        num2 = addLeadingZeros(num2, len1 - len2);
    }
    
    int carry = 0;
    string result = "";
    for (int i = num1.length() - 1; i >= 0; i--) {
        int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        carry = sum / 10;
        result = char(sum % 10 + '0') + result;
    }
    
    if (carry > 0) {
        result = char(carry + '0') + result;
    }
    
    return result;
}

// Function to subtract two large numbers represented as strings
string subtractStrings(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    
    if (len2 < len1) {
        num2 = addLeadingZeros(num2, len1 - len2);
    }
    
    int borrow = 0;
    string result = "";
    for (int i = num1.length() - 1; i >= 0; i--) {
        int diff = (num1[i] - '0') - (num2[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = char(diff + '0') + result;
    }
    
    return removeLeadingZeros(result);
}

// Karatsuba multiplication function
string karatsuba(string x, string y) {
    int n = x.length();
    if (n == 1) {
        return to_string((x[0] - '0') * (y[0] - '0'));
    }
    
    int half = n / 2;
    
    string a = x.substr(0, half);
    string b = x.substr(half);
    string c = y.substr(0, half);
    string d = y.substr(half);
    
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string ab_cd = karatsuba(addStrings(a, b), addStrings(c, d));
    
    string ad_bc = subtractStrings(ab_cd, addStrings(ac, bd));
    
    for (int i = 0; i < n; i++) {
        ac += "0";
    }
    for (int i = 0; i < (n/2); i++) {
        ad_bc += "0";
    }
    
    return removeLeadingZeros(addStrings(addStrings(ac, ad_bc), bd));
}

int main() {
    string num1, num2;
    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;
    
    // Make the lengths of the numbers equal by adding leading zeros
    int maxLength = max(num1.length(), num2.length());
    if (num1.length() < maxLength) {
        num1 = addLeadingZeros(num1, maxLength - num1.length());
    }
    if (num2.length() < maxLength) {
        num2 = addLeadingZeros(num2, maxLength - num2.length());
    }
    
    string result = karatsuba(num1, num2);
    cout << "Product: " << result << endl;
    
    return 0;
}