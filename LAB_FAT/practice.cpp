#include<bits/stdc++.h>

using namespace std;

void printSolution(vector<vector<string>>& solutions){
    for(int i=0; i<solutions.size() ; i++){
        for(int j=0 ; j<solutions[i].size(); j++){
            cout<<solutions[i][j];
        }
        cout<<endl;

    }

}

bool isSafe(){

}

vector<vector<string>> solveNQueens(int N){

}


int main(){
    int N=4;

    vector<vector<string>> solutions = solveNQueens(N);

    cout<<"Number of solutions "<<solutions.size();
    printSolution(solutions);

    return 0;
}