class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // 1. Build the adjacency list representing method invocations
        vector<vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // 2. Identify all suspicious methods using BFS starting from k
        vector<bool> suspicious(n, false);
        suspicious[k] = true;
        
        queue<int> q;
        q.push(k);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!suspicious[neighbor]) {
                    suspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // 3. Verify if any non-suspicious method invokes a suspicious method
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            // If u is NOT suspicious but invokes v which IS suspicious, we cannot remove anything
            if (!suspicious[u] && suspicious[v]) {
                vector<int> all_methods(n);
                iota(all_methods.begin(), all_methods.end(), 0); // Fills 0, 1, ..., n-1
                return all_methods;
            }
        }

        // 4. Return only the non-suspicious methods
        vector<int> remaining;
        for (int i = 0; i < n; ++i) {
            if (!suspicious[i]) {
                remaining.push_back(i);
            }
        }

        return remaining;
    }
};
