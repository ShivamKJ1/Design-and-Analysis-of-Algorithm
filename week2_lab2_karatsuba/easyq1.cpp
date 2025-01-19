#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// Function to make the numbers of equal length by padding zeros
string makeEqualLength(string str1, string str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 < len2) {
        for (int i = 0; i < len2 - len1; i++)
            str1 = '0' + str1;
    }
    return str1;
}
// Function to add two strings
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
// Function to subtract two strings
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
    
    // Remove leading zeros
    while (result.length() > 1 && result[0] == '0')
        result.erase(0, 1);
    
    return result;
}
// Main Karatsuba multiplication function
string karatsuba(string num1, string num2) {
    // Base cases
    if (num1.length() == 1 && num2.length() == 1) {
        int n1 = num1[0] - '0';
        int n2 = num2[0] - '0';
        int product = n1 * n2;
        return to_string(product);
    }
    
    // Make numbers of equal length by padding zeros
    int len = max(num1.length(), num2.length());
    num1 = makeEqualLength(num1, num2);
    num2 = makeEqualLength(num2, num1);
    
    // If length is odd, make it even by padding zero
    if (len % 2 == 1) {
        num1 = "0" + num1;
        num2 = "0" + num2;
        len++;
    }
    
    // Split the numbers
    int mid = len / 2;
    string a = num1.substr(0, len - mid);
    string b = num1.substr(len - mid);
    string c = num2.substr(0, len - mid);
    string d = num2.substr(len - mid);
    
    // Recursive steps
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string abcd = karatsuba(addStrings(a, b), addStrings(c, d));
    
    // Calculate (a+b)(c+d) - ac - bd
    string temp = subtractStrings(subtractStrings(abcd, ac), bd);
    
    // Final result: ac*10^(2*mid) + (abcd-ac-bd)*10^mid + bd
    for (int i = 0; i < 2 * mid; i++) ac += "0";
    for (int i = 0; i < mid; i++) temp += "0";
    
    string result = addStrings(addStrings(ac, temp), bd);
    
    // Remove leading zeros
    while (result.length() > 1 && result[0] == '0')
        result.erase(0, 1);
    
    return result;
}
int main() {
    string x, y;
    cin >> x >> y;
    cout << karatsuba(x, y) << endl;
    return 0;
}