class Solution {
public:
    bool check(vector<int>& nums, int target) {
        int minEven = INT_MAX;
        int minOdd = INT_MAX;

        for (int x : nums) {
            if (x % 2 == 0)
                minEven = min(minEven, x);
            else
                minOdd = min(minOdd, x);
        }

        for (int x : nums) {
            int p = x % 2;

            // We can simply keep x.
            if (p == target)
                continue;

            // Need a y such that (x - y) % 2 == target.
            int requiredParity = p ^ target;

            if (requiredParity == 0) {
                // Need a smaller even number.
                if (minEven >= x)
                    return false;
            } else {
                // Need a smaller odd number.
                if (minOdd >= x)
                    return false;
            }
        }

        return true;
    }

    bool uniformArray(vector<int>& nums) {
        // Try making everything even OR everything odd.
        return check(nums, 0) || check(nums, 1);
    }
};