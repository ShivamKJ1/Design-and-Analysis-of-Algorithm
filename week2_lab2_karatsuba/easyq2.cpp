#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

// Function to count decimal places in a floating point number
int countDecimals(string num) {
    size_t pos = num.find('.');
    if (pos == string::npos) return 0;
    return num.length() - pos - 1;
}

// Function to remove decimal point and convert to string
string removeDecimal(string num) {
    size_t pos = num.find('.');
    if (pos != string::npos) {
        return num.substr(0, pos) + num.substr(pos + 1);
    }
    return num;
}

// Reusing the integer Karatsuba multiplication functions from previous solution
string makeEqualLength(string str1, string str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (len1 < len2) {
        for (int i = 0; i < len2 - len1; i++)
            str1 = '0' + str1;
    }
    return str1;
}

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

// Function to insert decimal point in the result
string insertDecimalPoint(string result, int decimalPlaces) {
    if (decimalPlaces == 0) return result;
    
    while (result.length() <= decimalPlaces) {
        result = "0" + result;
    }
    
    return result.substr(0, result.length() - decimalPlaces) + "." + 
           result.substr(result.length() - decimalPlaces);
}

int main() {
    string x, y;
    cin >> x >> y;
    
    // Count decimal places
    int dec1 = countDecimals(x);
    int dec2 = countDecimals(y);
    
    // Remove decimal points
    string num1 = removeDecimal(x);
    string num2 = removeDecimal(y);
    
    // Calculate product
    string result = karatsuba(num1, num2);
    
    // Insert decimal point in correct position
    int totalDecimals = dec1 + dec2;
    result = insertDecimalPoint(result, totalDecimals);
    
    // Print result rounded to 3 decimal places
    double finalResult = stod(result);
    cout << fixed << setprecision(3) << finalResult << endl;
    
    return 0;
}