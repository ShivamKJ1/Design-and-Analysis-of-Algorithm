#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printSolution(vector<vector<string>>& solutions) {
    for (int i = 0; i < solutions.size(); ++i) {
        for (int j = 0; j < solutions[i].size(); ++j) {
            cout << solutions[i][j] << endl;
        }
        cout << endl;
    }
}

// Function to check if a queen can be placed on board[row][col]
bool isSafe(vector<string>& board, int row, int col, int N) {
    for (int i = 0; i < col; i++)
        if (board[row][i] == 'Q') return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q') return false;
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j] == 'Q') return false;
    return true;
}

// A recursive utility function to solve N Queen problem
void solveNQueensUtil(vector<vector<string>>& solutions, vector<string>& board, int col, int N) {
    if (col == N) {
        solutions.push_back(board);
        return;
    }
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 'Q';
            solveNQueensUtil(solutions, board, col + 1, N);
            board[i][col] = '.';
        }
    }
}

// This function solves the N Queens problem using Backtracking.
vector<vector<string>> solveNQueens(int N) {
    vector<vector<string>> solutions;
    vector<string> board(N, string(N, '.'));
    solveNQueensUtil(solutions, board, 0, N);
    return solutions;
}

int main() {
    int N = 4; // Change this value to solve for different sizes of N
    vector<vector<string>> solutions = solveNQueens(N);

    cout << "Number of solutions: " << solutions.size() << endl;
    printSolution(solutions);

    return 0;
}