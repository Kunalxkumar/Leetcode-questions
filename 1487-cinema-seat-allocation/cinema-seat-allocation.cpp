class Solution
{
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats)
    {
        unordered_map<int, int> rows;

        for (auto seat : reservedSeats)
        {
            int row = seat[0];
            int s = seat[1];

            if (s >= 2 && s <= 9)
            {
                rows[row] |= (1 << s);
            }
        }

        int ans = (n - rows.size()) * 2;

        for (auto p : rows)
        {
            int mask = p.second;

            bool left = (mask & (1 << 2)) == 0 &&
                        (mask & (1 << 3)) == 0 &&
                        (mask & (1 << 4)) == 0 &&
                        (mask & (1 << 5)) == 0;

            bool middle = (mask & (1 << 4)) == 0 &&
                          (mask & (1 << 5)) == 0 &&
                          (mask & (1 << 6)) == 0 &&
                          (mask & (1 << 7)) == 0;

            bool right = (mask & (1 << 6)) == 0 &&
                         (mask & (1 << 7)) == 0 &&
                         (mask & (1 << 8)) == 0 &&
                         (mask & (1 << 9)) == 0;

            if (left && right)
                ans += 2;
            else if (left || middle || right)
                ans += 1;
        }

        return ans;
    }
};