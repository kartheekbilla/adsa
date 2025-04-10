

#include <stdio.h>
#define N 4  

void printSolution(int board[N][N]) {
    for (int i = 0; i< N; i++) {
        for (int j = 0; j < N; j++)
printf("%c ", board[i][j] ? 'Q' : '.');
printf("\n");
    }
printf("\n");
}


int isSafe(int board[N][N], int row, int col) {
    int i, j;

    
    for (i = 0; i< row; i++)
        if (board[i][col]) return 0;

    for (i = row, j = col; i>= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;

    for (i = row, j = col; i>= 0 && j < N; i--, j++)
        if (board[i][j]) return 0;

    return 1;  
}

int solveNQueens(int board[N][N], int row) {
    if (row >= N) {
printSolution(board); 
        return 1;
    }

    int success = 0;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  
            success = solveNQueens(board, row + 1) || success;
            board[row][col] = 0;  
        }
    }
    return success;
}

int main() {
    int board[N][N] = {0};  
    if (!solveNQueens(board, 0))
printf("No solution found\n");
    return 0;
}
