/*
3336. Find the Number of Subsequences With Equal GCD
You are given an integer array nums.
Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
Return the total number of such pairs.
Since the answer may be very large, return it modulo 109 + 7.
 
Example 1:
Input: nums = [1,2,3,4]
Output: 10
Explanation:
The subsequence pairs which have the GCD of their elements equal to 1 are:
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
Example 2:
Input: nums = [10,20,30]
Output: 2
Explanation:
The subsequence pairs which have the GCD of their elements equal to 10 are:
([10, 20, 30], [10, 20, 30])
([10, 20, 30], [10, 20, 30])
Example 3:
Input: nums = [1,1,1,1]
Output: 50
Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= 200
*/
class Solution {
    static constexpr int MOD = 1000000007;
    static constexpr int LIM = 201;

    static inline int μ[LIM];
    static inline int lcms[LIM][LIM];
    static inline int pow2[LIM], pow3[LIM];

    static inline int init = [] {
        for (int i = 1; i < LIM; i++)
            for (int j = 1; j < LIM; j++)
                lcms[i][j] = ::lcm(i, j);

        pow2[0] = pow3[0] = 1;

        for (int i = 1; i < LIM; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
            pow3[i] = ((long long)pow3[i - 1] * 3) % MOD;
        }

        μ[1] = 1;
        for (int i = 1; i < LIM; i++)
            for (int j = i * 2; j < LIM; j += i)
                μ[j] -= μ[i];

        return false;
    }();

public:
    int subsequencePairCount(vector<int>& nums) {
        int mx = *std::max_element(nums.begin(), nums.end());

        vector<int> count(mx + 1);

        for (int n : nums)
            count[n]++;

        for (int i = 1; i <= mx; i++)
            for (int j = i * 2; j <= mx; j += i)
                count[i] += count[j];

        vector<vector<int>> dp(mx + 1, vector<int>(mx + 1));
        for (int i = 1; i <= mx; i++) {
            for (int j = 1; j <= mx; j++) {
                int l = lcms[i][j];
                int c = 0;
                if (l <= mx) c = count[l];                
                
                int ci = count[i];
                int cj = count[j];
                dp[i][j] = ((long long)pow3[c] * pow2[ci + cj - c * 2] - pow2[ci] - pow2[cj] + 1) % MOD;
            }
        }

        long long res = 0;

        for (int i = 1; i <= mx; i++)
            for (int j = 1; j <= mx / i; j++)
                for (int k = 1; k <= mx / i; k++)
                    res += (long long)μ[j] * μ[k] * dp[j * i][k * i];

        return (res % MOD + MOD) % MOD;
    }
};