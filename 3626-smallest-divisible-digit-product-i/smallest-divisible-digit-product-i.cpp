class Solution {
private:
    // Helper function to calculate the product of the digits of a number
    int getDigitProduct(int num) {
        if (num == 0) return 0;
        int product = 1;
        while (num > 0) {
            product *= (num % 10);
            num /= 10;
        }
        return product;
    }

public:
    int smallestNumber(int n, int t) {
        int curr = n;
        while (true) {
            if (getDigitProduct(curr) % t == 0) {
                return curr;
            }
            curr++;
        }
    }
};
