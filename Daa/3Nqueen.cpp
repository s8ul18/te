
#include <iostream>
using namespace std;

const int MAX = 20;
int mat[MAX][MAX];
int n;
int solutionCount = 0;

bool isSafe(int row, int col)
{
    for (int i = 0; i < row; i++)
        if (mat[i][col] == 1)
            return false;

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (mat[i][j] == 1)
            return false;

    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (mat[i][j] == 1)
            return false;
    return true;
}

void printBoard()
{
    cout << "Solution " << solutionCount << ":\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 1)
                cout << "Q";
            else
                cout << ". ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void placeQueens(int row)
{
    if (row == n)
    {
        solutionCount++;
        printBoard();
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col))
        {
            mat[row][col] = 1;
            placeQueens(row + 1);
            mat[row][col] = 0;
        }
    }
}

int main()
{
    cout << "Enter the size of the board (n): ";
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;

    placeQueens(0);

    cout << "Total number of solutions:  " << solutionCount << "\n";

    return 0;
}
