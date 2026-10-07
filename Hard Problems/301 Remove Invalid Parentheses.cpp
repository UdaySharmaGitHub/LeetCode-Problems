/*
301. Remove Invalid Parentheses
Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
Example 1:
Input: s = "()())()"
Output: ["(())()","()()()"]
Example 2:
Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
Example 3:
Input: s = ")("
Output: [""]

Constraints:
1 <= s.length <= 25
s consists of lowercase English letters and parentheses '(' and ')'.
There will be at most 20 parentheses in s.
*/
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        forward(s, res, 0, 0);

        return res;
    }

private:
    void forward(string s, auto& res, int li, int lj) {
        int bal = 0;

        for (int i = li; i < s.length(); i++) {
            bal += (s[i] == '(') - (s[i] == ')');

            if (bal >= 0) continue;

            for (int j = lj; j <= i; j++)
                if (s[j] == ')' && (j == lj || s[j - 1] != ')'))
                    forward(s.substr(0, j) + s.substr(j + 1), res, i, j);

            return;
        }

        backward(s, res, s.length() - 1, s.length() - 1);
    }

    void backward(string s, auto& res, int ri, int rj) {
        int bal = 0;

        for (int i = ri; i >= 0; i--) {
            bal += (s[i] == ')') - (s[i] == '(');

            if (bal >= 0) continue;

            for (int j = rj; j >= i; j--)
                if (s[j] == '(' && (j == rj || s[j + 1] != '('))
                    backward(s.substr(0, j) + s.substr(j + 1), res, i - 1,
                             j - 1);

            return;
        }

        res.push_back(s);
    }
};