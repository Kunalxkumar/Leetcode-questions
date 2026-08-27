class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            if (col >= 2 && col <= 9)
                rows[row] |= (1 << (col - 2));
        }

        int ans = (n - rows.size()) * 2;

        for (auto &[row, mask] : rows) {
            bool left = (mask & 0b00001111) == 0;        // seats 2-5
            bool middle = (mask & 0b00111100) == 0;      // seats 4-7
            bool right = (mask & 0b11110000) == 0;       // seats 6-9

            if (left && right)
                ans += 2;
            else if (left || middle || right)
                ans += 1;
        }

        return ans;
    }
};