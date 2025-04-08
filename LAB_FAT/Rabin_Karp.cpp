#include <iostream>
#include <string>
using namespace std;

#define d 256 // Number of characters in the input alphabet

int rabinKarpCount(string text, string pattern, int q) {
    int count = 0;
    int m = pattern.length();
    int n = text.length();
    int i, j;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int h = 1;

    // The value of h would be "pow(d, m-1)%q"
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values of current window of text and pattern.
        // If the hash values match then only check for characters one by one
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // If p == t and pattern[0...m-1] = text[i, i+1, ...i+m-1]
            if (j == m)
                count++;
        }

        // Calculate hash value for next window of text: Remove leading digit,
        // add trailing digit
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }

    return count;
}

int main() {
    string text;
    string pattern;
    getline(cin, text);
    getline(cin, pattern);

    int result = rabinKarpCount(text, pattern, 101);
    cout << result << endl;

    return 0;
}