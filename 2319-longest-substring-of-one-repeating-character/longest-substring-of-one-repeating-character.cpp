class Solution {
public:
    struct Node
    {
        char leftChar;
        char rightChar;
        int leftLen;
        int rightLen;
        int best;
        int len;
    };

    vector<Node> tree;
    string str;

    Node merge(Node a, Node b)
    {
        if (a.len == 0)
            return b;

        if (b.len == 0)
            return a;

        Node res;

        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.leftLen = a.leftLen;
        if (a.leftLen == a.len && a.rightChar == b.leftChar)
        {
            res.leftLen += b.leftLen;
        }

        res.rightLen = b.rightLen;
        if (b.rightLen == b.len && a.rightChar == b.leftChar)
        {
            res.rightLen += a.rightLen;
        }

        res.best = max(a.best, b.best);

        if (a.rightChar == b.leftChar)
        {
            res.best = max(res.best, a.rightLen + b.leftLen);
        }

        return res;
    }


    void build(int node, int l, int r)
    {
        if (l == r)
        {
            tree[node] = {
                str[l],
                str[l],
                1,
                1,
                1,
                1
            };
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }


    void update(int node, int l, int r, int idx, char c)
    {
        if (l == r)
        {
            tree[node] = {
                c,
                c,
                1,
                1,
                1,
                1
            };
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
        {
            update(node * 2, l, mid, idx, c);
        }
        else
        {
            update(node * 2 + 1, mid + 1, r, idx, c);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }


    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices)
    {
        str = s;

        int n = s.size();

        tree.assign(4 * n, {});

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++)
        {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};