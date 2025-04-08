#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));

    // taking input
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    //computing distance
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != 999 && dist[k][j] != 999)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    //prnting the new distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << dist[i][j] << " ";
        cout <<endl;
}
}