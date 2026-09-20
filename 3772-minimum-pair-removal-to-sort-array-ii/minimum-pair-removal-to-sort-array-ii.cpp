class Solution
{
public:
    int minimumPairRemoval(vector<int>& nums)
    {
        int n = nums.size();
        int inv = 0;

        set<pair<long long, int>> sl;
        set<int> idx;
        vector<long long> arr(nums.begin(), nums.end());

        for (int i = 0; i < n; i++)
            idx.insert(i);

        for (int i = 0; i < n - 1; i++)
        {
            if (nums[i] > nums[i + 1])
                inv++;

            sl.insert({(long long)nums[i] + nums[i + 1], i});
        }

        int ans = 0;

        while (inv > 0)
        {
            ans++;

            auto it = sl.begin();

            long long s = it->first;
            int i = it->second;

            sl.erase(it);

            auto jIt = idx.upper_bound(i);
            int j = *jIt;

            if (arr[i] > arr[j])
                inv--;

            auto iIt = idx.find(i);

            if (iIt != idx.begin())
            {
                auto hIt = std::prev(iIt);
                int h = *hIt;

                if (arr[h] > arr[i])
                    inv--;

                sl.erase({arr[h] + arr[i], h});

                if (arr[h] > s)
                    inv++;

                sl.insert({arr[h] + s, h});
            }

            auto kIt = std::next(jIt);

            if (kIt != idx.end())
            {
                int k = *kIt;

                if (arr[j] > arr[k])
                    inv--;

                sl.erase({arr[j] + arr[k], j});

                if (s > arr[k])
                    inv++;

                sl.insert({s + arr[k], i});
            }

            arr[i] = s;
            idx.erase(j);
        }

        return ans;
    }
};