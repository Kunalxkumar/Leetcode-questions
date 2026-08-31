class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;
        int maxDist = -1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check if curr is a critical point
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                if (first == -1) {
                    // First critical point
                    first = pos;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - last);

                    // Distance from first critical point
                    maxDist = pos - first;
                }

                last = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        if (first == -1 || first == last) {
            return {-1, -1};
        }

        return {minDist, maxDist};
    }
};