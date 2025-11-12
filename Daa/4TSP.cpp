#include <iostream>
#include <climits>
using namespace std;

#define MAX 10       
#define INF INT_MAX

int costMatrix[MAX][MAX];
int N;

int minCost = INF;
int bestPath[MAX+1];

void copyMatrix(int src[MAX][MAX], int dest[MAX][MAX]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dest[i][j] = src[i][j];
}

int rowReduction(int matrix[MAX][MAX]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        int minVal = INF;
        for (int j = 0; j < N; j++)
            if (matrix[i][j] < minVal)
                minVal = matrix[i][j];

        if (minVal != INF && minVal > 0) {
            cost += minVal;
            for (int j = 0; j < N; j++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= minVal;
        }
    }
    return cost;
}

int colReduction(int matrix[MAX][MAX]) {
    int cost = 0;
    for (int j = 0; j < N; j++) {
        int minVal = INF;
        for (int i = 0; i < N; i++)
            if (matrix[i][j] < minVal)
                minVal = matrix[i][j];

        if (minVal != INF && minVal > 0) {
            cost += minVal;
            for (int i = 0; i < N; i++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= minVal;
        }
    }
    return cost;
}

int reduceMatrix(int matrix[MAX][MAX]) {
    return rowReduction(matrix) + colReduction(matrix);
}

void tspRecursion(int matrix[MAX][MAX], int currCost, int level, int currVertex, bool visited[MAX], int path[MAX+1], int pathLen) {

    if (level == N) {
        if (costMatrix[currVertex][0] != INF) {
            int totalCost = currCost + costMatrix[currVertex][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                for (int i = 0; i < pathLen; i++)
                    bestPath[i] = path[i];
                bestPath[pathLen] = 0;
            }
        }
        return;
    }

    for (int next = 0; next < N; next++) {
        if (!visited[next] && matrix[currVertex][next] != INF) {
            int childMatrix[MAX][MAX];
            copyMatrix(matrix, childMatrix);

            for (int j = 0; j < N; j++)
                childMatrix[currVertex][j] = INF;

            for (int i = 0; i < N; i++)
                childMatrix[i][next] = INF;

            childMatrix[next][0] = INF;

            int newCost = currCost + matrix[currVertex][next] + reduceMatrix(childMatrix);

            if (newCost < minCost) {
                visited[next] = true;
                path[pathLen] = next;
                tspRecursion(childMatrix, newCost, level + 1, next, visited, path, pathLen + 1);
                visited[next] = false;
            }
        }
    }
}

int main() {
    cout << "Enter number of cities (max " << MAX << "): ";
    cin >> N;
    if (N > MAX) {
        cout << "Number of cities exceeds max allowed.\n";
        return 1;
    }

    cout << "Enter cost matrix (use -1 for no edge):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val;
            cin >> val;
            costMatrix[i][j] = (val == -1) ? INF : val;
        }
    }

    int reducedMatrix[MAX][MAX];
    copyMatrix(costMatrix, reducedMatrix);
    int initialCost = reduceMatrix(reducedMatrix);

    bool visited[MAX] = {false};
    visited[0] = true;

    int path[MAX+1];
    path[0] = 0;

    tspRecursion(reducedMatrix, initialCost, 1, 0, visited, path, 1);

    cout << "Minimum cost: " << minCost << "\nPath: ";
    for (int i = 0; i <= N; i++)
        cout << bestPath[i] << " ";
    cout << "\n";

    return 0;
}