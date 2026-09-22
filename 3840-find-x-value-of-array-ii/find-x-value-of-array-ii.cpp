class Solution
{
public:

    struct Node
    {
        int prod;
        int cnt[5];

        Node()
        {
            prod = 1;

            for (int i = 0; i < 5; i++)
            {
                cnt[i] = 0;
            }
        }
    };

    int n, k;
    vector<int> nums;
    vector<Node> tree;

    Node mergeNode(const Node &left, const Node &right)
    {
        Node res;

        res.prod = (left.prod * right.prod) % k;

        // Prefixes completely inside left
        for (int i = 0; i < k; i++)
        {
            res.cnt[i] = left.cnt[i];
        }

        // Prefixes that contain all of left
        // and some non-empty prefix of right
        for (int p = 0; p < k; p++)
        {
            int newRem = (left.prod * p) % k;
            res.cnt[newRem] += right.cnt[p];
        }

        return res;
    }

    void build(int node, int l, int r)
    {
        if (l == r)
        {
            int rem = nums[l] % k;

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = mergeNode(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, int value)
    {
        if (l == r)
        {
            int rem = value % k;

            tree[node] = Node();
            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
        {
            update(node * 2, l, mid, pos, value);
        }
        else
        {
            update(node * 2 + 1, mid + 1, r, pos, value);
        }

        tree[node] = mergeNode(tree[node * 2], tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return tree[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid)
        {
            return query(node * 2, l, mid, ql, qr);
        }

        if (ql > mid)
        {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    )
    {
        this->nums = nums;
        this->k = k;
        this->n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> result;

        for (auto &q : queries)
        {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // Need prefix products of nums[start..r]
            Node cur = query(1, 0, n - 1, start, n - 1);

            result.push_back(cur.cnt[x]);
        }

        return result;
    }
};