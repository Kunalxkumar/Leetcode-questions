class Solution {
public:
    int n;
    vector<int> pre;
    vector<vector<int>> dp;

    int solve(int l, int r) {
        if (l == r) return 0;

        if (dp[l][r] != -1)
            return dp[l][r];

        int ans = 0;

        for (int k = l; k < r; k++) {
            int left = pre[k + 1] - pre[l];
            int right = pre[r + 1] - pre[k + 1];

            if (left < right) {
                // Bob throws away right
                // Alice keeps left
                ans = max(ans, left + solve(l, k));
            }
            else if (left > right) {
                // Bob throws away left
                // Alice keeps right
                ans = max(ans, right + solve(k + 1, r));
            }
            else {
                // Equal: Alice can choose either side
                ans = max(ans, left + solve(l, k));
                ans = max(ans, right + solve(k + 1, r));
            }
        }

        return dp[l][r] = ans;
    }

    int stoneGameV(vector<int>& stoneValue) {
        n = stoneValue.size();

        // Prefix sums
        pre.resize(n + 1, 0);

        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + stoneValue[i];

        // dp[l][r] = maximum score from stones l...r
        dp.assign(n, vector<int>(n, -1));

        return solve(0, n - 1);
    }
};