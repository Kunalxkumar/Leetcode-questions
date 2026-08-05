#include <string>
#include <algorithm>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        if (s.empty()) return "";
        
        int start = 0;
        int maxLength = 0;

        auto expandAroundCenter = [&](int left, int right) {
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                left--;
                right++;
            }
            // Length of the found palindrome is (right - 1) - (left + 1) + 1
            int currentLength = right - left - 1;
            if (currentLength > maxLength) {
                maxLength = currentLength;
                start = left + 1; // Update starting boundary
            }
        };

        for (int i = 0; i < s.length(); ++i) {
            // Case 1: Odd-length palindromes (single-character center, e.g., "aba")
            expandAroundCenter(i, i);
            
            // Case 2: Even-length palindromes (two-character center, e.g., "abba")
            expandAroundCenter(i, i + 1);
        }

        return s.substr(start, maxLength);
    }
};
