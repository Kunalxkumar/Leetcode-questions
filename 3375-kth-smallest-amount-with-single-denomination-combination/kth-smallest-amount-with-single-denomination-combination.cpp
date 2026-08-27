class Solution {
public:

    long long lcm(long long a, long long b)
    {
        return a / gcd(a,b) * b;
    }


    long long count(vector<int>& coins, long long x)
    {
        long long ans = 0;
        int n = coins.size();

        for(int mask = 1; mask < (1<<n); mask++)
        {
            long long cur = 1;
            int bits = 0;
            bool overflow = false;

            for(int i=0;i<n;i++)
            {
                if(mask&(1<<i))
                {
                    bits++;

                    cur = lcm(cur, coins[i]);

                    if(cur > x)
                    {
                        overflow=true;
                        break;
                    }
                }
            }


            if(overflow)
                continue;


            long long add = x/cur;


            if(bits%2)
                ans += add;
            else
                ans -= add;
        }

        return ans;
    }


    long long findKthSmallest(vector<int>& coins, int k)
    {

        sort(coins.begin(), coins.end());


        vector<int> filtered;


        for(int c:coins)
        {
            bool ok=true;

            for(int x:filtered)
            {
                if(c%x==0)
                {
                    ok=false;
                    break;
                }
            }

            if(ok)
                filtered.push_back(c);
        }


        coins=filtered;


        long long left=1;
        long long right=1LL*coins[0]*k;


        while(left<right)
        {
            long long mid=left+(right-left)/2;


            if(count(coins,mid)>=k)
                right=mid;
            else
                left=mid+1;
        }


        return left;
    }
};