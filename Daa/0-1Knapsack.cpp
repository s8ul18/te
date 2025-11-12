#include <bits/stdc++.h>
using namespace std;

int knapsack_dp(int n, int M, int w[], int p[]) {
    int i, j;
    int knapsack[n + 1][M + 1];

    // Initialize base cases
    for (j = 0; j <= M; j++)
        knapsack[0][j] = 0;
    for (i = 0; i <= n; i++)
        knapsack[i][0] = 0;

    // Build the DP table
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= M; j++) {
            if (w[i - 1] <= j) {
                knapsack[i][j] = max(
                    knapsack[i - 1][j], 
                    p[i - 1] + knapsack[i - 1][j - w[i - 1]]
                );
            } else {
                knapsack[i][j] = knapsack[i - 1][j];
            }
        }
    }

    return knapsack[n][M];
}

int main() {
    int n, M;

    cout << "Enter number of items: ";
    cin >> n;

    int w[n], p[n];

    cout << "Enter weight and profit of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (weight profit): ";
        cin >> w[i] >> p[i];
    }

    cout << "Enter capacity of knapsack: ";
    cin >> M;

    int maxProfit = knapsack_dp(n, M, w, p);

    cout << "\nMaximum profit = " << maxProfit << endl;

    return 0;
}
