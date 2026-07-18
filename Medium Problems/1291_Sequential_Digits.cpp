/*
1291. Sequential Digits
An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
Example 1:
Input: low = 100, high = 300
Output: [123,234]
Example 2:
Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]
Constraints:
10 <= low <= high <= 10^9
*/
class Solution {
public:
    inline static int q[45];
    inline static bool init = []() {
        int n = 0;
        for (int i = 1; i < 10; i++)
            q[n++] = i;

        for (int i = 0; i < n; i++) {
            int d = q[i] % 10;
            if (d < 9) q[n++] = q[i] * 10 + d + 1;
        }

        return 0;
    }();

    vector<int> sequentialDigits(int low, int high) {
        vector<int> res;

        for (auto& x : q)
            if (x >= low && x <= high)
                res.push_back(x);

        return res;
    }
};