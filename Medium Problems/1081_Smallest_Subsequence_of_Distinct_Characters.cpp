/*
1081. Smallest Subsequence of Distinct Characters
Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.
Example 1:
Input: s = "bcabc"
Output: "abc"
Example 2:
Input: s = "cbacdcbc"
Output: "acdb"
Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.
Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
*/
class Solution {
public:
    string smallestSubsequence(string s) {
        int freq[27] = {0};
        bitset<27> seen;
        string stack;

        for (auto& c : s)
            freq[c & 31]++;

        for (auto& c : s) {
            int x = c & 31;
            freq[x]--;

            if (seen.test(x))
                continue;

            while (stack.length() && stack.back() > c && freq[stack.back() & 31]) {
                seen.reset(stack.back() & 31);
                stack.pop_back();
            }

            stack.push_back(c);
            seen.set(x);
        }

        return stack;
    }
};