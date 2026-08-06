#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    string convert(string s, int numRows) {
        // Edge case: If there is only 1 row or the string is shorter than numRows, no conversion is needed
        if (numRows <= 1 || s.length() <= numRows) {
            return s;
        }

        // Vector of strings to keep track of characters in each row
        std::vector<std::string> rows(std::min(numRows, (int)s.length()));
        int currentRow = 0;
        bool goingDown = false;

        // Iterate through each character in the string
        for (char c : s) {
            rows[currentRow] += c;

            // Reverse direction when we reach the top or bottom row
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown;
            }

            // Move up or down based on the current direction
            currentRow += goingDown ? 1 : -1;
        }

        // Concatenate all row strings to produce the final result
        std::string result;
        for (const std::string& row : rows) {
            result += row;
        }

        return result;
    }
};
