#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to create the longest prefix suffix (lps) array
void computeLPSArray(const string& pat, int M, vector<int>& lps) {
    int length = 0; // length of the previous longest prefix suffix
    lps[0] = 0; // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[length]) {
            length++;
            lps[i] = length;
            i++;
        } 
        
        else { // (pat[i] != pat[length])
            if (length != 0) {
                length = lps[length - 1];
            } else { // if (length == 0)
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algorithm to find all occurrences of the pattern in the text
void KMPSearch(const string& txt, const string& pat) {
    int N = txt.size();
    int M = pat.size();

    // Create lps[] that will hold the longest prefix suffix values for pattern
    vector<int> lps(M);

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    
    while (i < N) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        }

        if (j == M) {
            // Pattern found at index (i - j), output the 1-indexed starting and ending positions
            cout << (i - j + 1) << " " << i << endl;
            j = lps[j - 1];
        } 
        
        else if (i < N && pat[j] != txt[i]) { // mismatch after j matches
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string txt;
    string pat;

    // Read input
    getline(cin, txt);
    getline(cin, pat);

    // Perform KMP search
    KMPSearch(txt, pat);

    return 0;
}