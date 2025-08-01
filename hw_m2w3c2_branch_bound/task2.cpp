#include <iostream>
#include <vector>
using namespace std;

void knapsack(const vector<int>& weights, const vector<int>& values, int W) {
    int n = weights.size();
    
    /* dp table
        X           0   1   2      3      4      5
        0           0   0   0      0      0      0
        1(A)        0   0   1000   1000   1000   1000
        2(A,B)      0   0   1000   1400   1400   2400
        3(A,B,C)    0   0   1000   1400   1600   2400 */

    // dp[i][w] – առավելագույն արժեք՝ առաջին i իրերի և w քաշի դեպքում
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Լրացնենք աղյուսակը
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                // Կամ վերցնենք իր i, կամ ոչ
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]], // վերցնում ենք
                    dp[i - 1][w] // չենք վերցնում
                );
            } else {
                dp[i][w] = dp[i - 1][w]; // չի տեղավորվում
            }
        }
    }

    cout << "Max value: " << dp[n][W] << "$" << endl;

    // Հետ գնանք՝ տեսնելու համար, որ իրերն են վերցվել
    int w = W;
    cout << "Things: ";
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << char('A' + (i - 1)) << " "; // Տպում ենք իրի անունը՝ A, B, C...
            w -= weights[i - 1];
        }
    }
    cout << endl;
}

int main() {
    // Մեր օրինակը՝
    vector<int> weights = {2, 3, 4};  // քաշեր
    vector<int> values  = {1000, 1400, 1600}; // արժեքներ
    int W = 5; // Ուսապարկի քաշային սահմանը

    vector<int> weights2 = {2, 5, 1, 4};  // քաշեր
    vector<int> values2  = {4, 10, 7, 20}; // արժեքներ

    knapsack(weights, values, W);
    knapsack(weights2, values2, W);
    return 0;
}

