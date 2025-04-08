#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define N 4

// Function to find the minimum cost using Branch and Bound
int jobAssignmentBranchAndBound(int costMatrix[N][N], int person, vector<bool>& assigned, int currentCost) {
    if (person >= N) {
        return currentCost;
    }

    int minCost = INT_MAX;

    for (int job = 0; job < N; ++job) {
        if (!assigned[job]) {
            assigned[job] = true;
            int cost = jobAssignmentBranchAndBound(costMatrix, person + 1, assigned, currentCost + costMatrix[person][job]);
            minCost = min(minCost, cost);
            assigned[job] = false;
        }
    }

    return minCost;
}

int main() {
    int costMatrix[N][N] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4} 
    };

    vector<bool> assigned(N, false);
    int minCost = jobAssignmentBranchAndBound(costMatrix, 0, assigned, 0);

    cout << "The minimum cost to assign all jobs is: " << minCost << endl;

    return 0;
}