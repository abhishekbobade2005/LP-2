#include <iostream>
#include <vector>
using namespace std;

// Print solution
void printSolution(vector<vector<int>> &board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// isSafe using Branch & Bound
bool isSafe(int row, int col, vector<bool> &leftRow,
            vector<bool> &upperDiagonal,
            vector<bool> &lowerDiagonal, int N) {

    return (!leftRow[row] &&
            !lowerDiagonal[row + col] &&
            !upperDiagonal[N - 1 + col - row]);
}

// Backtracking function
bool solveNQUtil(int col, vector<vector<int>> &board, int N,
                 vector<bool> &leftRow,
                 vector<bool> &upperDiagonal,
                 vector<bool> &lowerDiagonal) {

    if (col >= N)
        return true;

    for (int row = 0; row < N; row++) {

        if (isSafe(row, col, leftRow, upperDiagonal, lowerDiagonal, N)) {

            // Place queen
            board[row][col] = 1;
            leftRow[row] = true;
            lowerDiagonal[row + col] = true;
            upperDiagonal[N - 1 + col - row] = true;

            // Recur
            if (solveNQUtil(col + 1, board, N, leftRow, upperDiagonal, lowerDiagonal))
                return true;

            // Backtrack
            board[row][col] = 0;
            leftRow[row] = false;
            lowerDiagonal[row + col] = false;
            upperDiagonal[N - 1 + col - row] = false;
        }
    }

    return false;
}

// Main
int main() {
    int N;
    cout << "Enter value of N: ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    vector<bool> leftRow(N, false);
    vector<bool> upperDiagonal(2 * N - 1, false);
    vector<bool> lowerDiagonal(2 * N - 1, false);

    if (!solveNQUtil(0, board, N, leftRow, upperDiagonal, lowerDiagonal)) {
        cout << "Solution does not exist\n";
        return 0;
    }

    cout << "\nSolution:\n";
    printSolution(board, N);

    return 0;
}