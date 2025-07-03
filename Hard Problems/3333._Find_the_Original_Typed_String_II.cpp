/*
3333. Find the Original Typed String II
Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
Since the answer may be very large, return it modulo 109 + 7.
Example 1:
Input: word = "aabbccdd", k = 7
Output: 5
Explanation:
The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
Example 2:
Input: word = "aabbccdd", k = 8
Output: 1
Explanation:
The only possible string is "aabbccdd".
Example 3:
Input: word = "aaabbb", k = 3
Output: 8
Constraints:
1 <= word.length <= 5 * 105
word consists only of lowercase English letters.
1 <= k <= 2000
*/
class Solution {
    static const int MOD = 1e9 + 7;

public:
    int possibleStringCount(std::string word, int k) {
        if (word.empty()) return 0;

        std::vector<int> groups;
        int count = 1;
        for (size_t i = 1; i < word.size(); ++i) {
            if (word[i] == word[i - 1]) count++;
            else {
                groups.push_back(count);
                count = 1;
            }
        }
        groups.push_back(count);

        long long total = 1;
        for (int num : groups)
            total = (total * num) % MOD;

        if (k <= (int)groups.size()) return total;

        std::vector<int> dp(k, 0);
        dp[0] = 1;

        for (int num : groups) {
            std::vector<int> newDp(k, 0);
            long long sum = 0;
            for (int s = 0; s < k; ++s) {
                if (s > 0) sum = (sum + dp[s - 1]) % MOD;
                if (s > num) sum = (sum - dp[s - num - 1] + MOD) % MOD;
                newDp[s] = sum;
            }
            dp = newDp;
        }

        long long invalid = 0;
        for (int s = groups.size(); s < k; ++s)
            invalid = (invalid + dp[s]) % MOD;

        return (total - invalid + MOD) % MOD;
    }
};