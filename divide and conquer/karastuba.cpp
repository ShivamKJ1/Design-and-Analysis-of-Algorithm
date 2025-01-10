#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

// Function to multiply two numbers using the Karatsuba algorithm
long long karatsuba(long long x, long long y) {
    // Base case for recursion
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Calculate the size of the numbers
    int n1 = to_string(x).length();
    int n2 = to_string(y).length();
    int n = max(n1, n2);
    int half = n / 2;

    // Split the digit sequences in the middle
    long long high1 = x / pow(10, half);
    long long low1 = x % (long long)pow(10, half);
    long long high2 = y / pow(10, half);
    long long low2 = y % (long long)pow(10, half);

    // 3 recursive calls
    long long z0 = karatsuba(low1, low2); // z0 = low1 * low2
    long long z1 = karatsuba((low1 + high1), (low2 + high2)); // z1 = (low1 + high1) * (low2 + high2)
    long long z2 = karatsuba(high1, high2); // z2 = high1 * high2

    // Combine the results
    return (z2 * pow(10, 2 * half)) + ((z1 - z2 - z0) * pow(10, half)) + z0;
}

int main() {
    long long x, y;
    cout << "Enter two numbers to multiply: ";
    cin >> x >> y;

    long long result = karatsuba(x, y);
    cout << "Result: " << result << endl;

    return 0;
}