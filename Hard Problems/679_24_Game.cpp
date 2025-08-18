/*
679. 24 Game
You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
You are restricted with the following rules:
The division operator '/' represents real division, not integer division.
For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
You cannot concatenate numbers together
For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
Return true if you can get such expression that evaluates to 24, and false otherwise
Example 1:
Input: cards = [4,1,8,7]
Output: true
Explanation: (8-4) * (7-1) = 24
Example 2:
Input: cards = [1,2,1,2]
Output: false
Constraints:
cards.length == 4
1 <= cards[i] <= 9
*/
class Solution {
    const double EPS = 1e-6;

public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;
        for (int n : cards) nums.push_back((double)n);
        return dfs(nums);
    }

private:
    bool dfs(vector<double>& nums) {
        if (nums.size() == 1) {
            return fabs(nums[0] - 24.0) < EPS;
        }

        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i == j) continue;

                vector<double> next;
                for (int k = 0; k < nums.size(); k++) {
                    if (k != i && k != j) next.push_back(nums[k]);
                }

                for (double val : compute(nums[i], nums[j])) {
                    next.push_back(val);
                    if (dfs(next)) return true;
                    next.pop_back();
                }
            }
        }
        return false;
    }

    vector<double> compute(double a, double b) {
        vector<double> res;
        res.push_back(a + b);
        res.push_back(a - b);
        res.push_back(b - a);
        res.push_back(a * b);
        if (fabs(b) > EPS) res.push_back(a / b);
        if (fabs(a) > EPS) res.push_back(b / a);
        return res;
    }
};