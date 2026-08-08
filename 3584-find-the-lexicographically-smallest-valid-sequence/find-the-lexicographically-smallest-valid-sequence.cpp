class Solution
{
public:
    vector<int> validSequence(string word1, string word2)
    {
        int n = word1.size();
        int m = word2.size();

        vector<int> suf(m + 1, -1);

        suf[m] = n;

        int p = n - 1;

        for (int j = m - 1; j >= 0; j--)
        {
            while (p >= 0 && word1[p] != word2[j])
            {
                p--;
            }

            if (p < 0)
            {
                suf[j] = -1;
            }
            else
            {
                suf[j] = p;
                p--;
            }
        }

        vector<int> ans;

        int pos = 0;
        bool changed = false;

        for (int j = 0; j < m; j++)
        {
            int exact = n;

            for (int i = pos; i < n; i++)
            {
                if (word1[i] == word2[j])
                {
                    exact = i;
                    break;
                }
            }

            int different = n;

            if (!changed && suf[j + 1] != -1)
            {
                for (int i = pos; i < suf[j + 1]; i++)
                {
                    if (word1[i] != word2[j])
                    {
                        different = i;
                        break;
                    }
                }
            }

            if (different < exact)
            {
                ans.push_back(different);
                pos = different + 1;
                changed = true;
            }
            else if (exact < n)
            {
                ans.push_back(exact);
                pos = exact + 1;
            }
            else
            {
                return {};
            }
        }

        return ans;
    }
};