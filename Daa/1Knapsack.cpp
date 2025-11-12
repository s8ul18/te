#include <bits/stdc++.h>
using namespace std;

// ---------------------- FRACTIONAL KNAPSACK ------------------------
struct Item {
    double weight;
    double value;
    double ratio;
};

double fractionalKnapsack(int n, double capacity, Item arr[]) {
    // Calculate ratio
    for (int i = 0; i < n; i++)
        arr[i].ratio = arr[i].value / arr[i].weight;

    // Sort by ratio (descending)
    sort(arr, arr + n, [](Item a, Item b) {
        return a.ratio > b.ratio;
    });

    double profit = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= capacity) {
            profit += arr[i].value;
            capacity -= arr[i].weight;
        } else { 
            profit += (capacity / arr[i].weight) * arr[i].value;
            break;
        }
    }
    return profit;
}

// ---------------------- 0/1 KNAPSACK (DP) ------------------------
int knapsack_dp(int n, int M, int w[], int p[]) {
    int dp[n + 1][M + 1];

    // Base initialization
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= M; j++)
            dp[i][j] = 0;

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= M; j++) {
            if (w[i - 1] <= j) {
                dp[i][j] = max(dp[i - 1][j],p[i - 1] + dp[i - 1][j - w[i - 1]]);

            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][M];  
}

// ---------------------- MAIN PROGRAM ------------------------
int main() {
    int choice;
    cout << "Select Knapsack Method:\n";
    cout << "1. Fractional Knapsack (Greedy)\n";
    cout << "2. 0/1 Knapsack (Dynamic Programming)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int n;
        double capacity;
        cout << "\nEnter number of items: ";
        cin >> n;
        Item arr[n];

        cout << "Enter value & weight of each item:\n";
        for (int i = 0; i < n; i++) {
            cout << "Item " << i + 1 << " (value weight): ";
            cin >> arr[i].value >> arr[i].weight;
        }

        cout << "Enter knapsack capacity: ";
        cin >> capacity;

        double profit = fractionalKnapsack(n, capacity, arr);
        cout << "\nMaximum Profit (Fractional) = " << profit << endl;
    }

    else if (choice == 2) {
        int n, M;
        cout << "\nEnter number of items: ";
        cin >> n;

        int w[n], p[n];

        cout << "Enter weight and profit of each item:\n";
        for (int i = 0; i < n; i++) {
            cout << "Item " << i + 1 << " (weight profit): ";
            cin >> w[i] >> p[i];
        }

        cout << "Enter knapsack capacity: ";
        cin >> M;

        int maxProfit = knapsack_dp(n, M, w, p);
        cout << "\nMaximum Profit (0/1 DP) = " << maxProfit << endl;
    }

    else {
        cout << "Invalid choice!";
    }

    return 0;
}
