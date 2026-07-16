class Solution
{
public:
    long long gcdSum(vector<int>& nums)
    {
        vector<int> prefixGcd;

        int mx = 0;

        for (int num : nums)
        {
            mx = max(mx, num);
            prefixGcd.push_back(gcd(num, mx));
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        long long ans = 0;

        int left = 0;
        int right = prefixGcd.size() - 1;

        while (left < right)
        {
            ans += gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }

        return ans;
    }
};