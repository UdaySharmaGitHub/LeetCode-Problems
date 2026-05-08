/*
3629. Minimum Jumps to Reach End via Prime Teleportation
You are given an integer array nums of length n.

You start at index 0, and your goal is to reach index n - 1.

From any index i, you may perform one of the following operations:

Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] % p == 0.
Return the minimum number of jumps required to reach index n - 1.

 

Example 1:

Input: nums = [1,2,4,6]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index 1.
At index i = 1, nums[1] = 2 is a prime number. Therefore, we teleport to index i = 3 as nums[3] = 6 is divisible by 2.
Thus, the answer is 2.

Example 2:

Input: nums = [2,3,4,7,9]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index i = 1.
At index i = 1, nums[1] = 3 is a prime number. Therefore, we teleport to index i = 4 since nums[4] = 9 is divisible by 3.
Thus, the answer is 2.

Example 3:

Input: nums = [4,6,5,8]

Output: 3

Explanation:

Since no teleportation is possible, we move through 0 → 1 → 2 → 3. Thus, the answer is 3.
 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= 106
*/
class Solution {
    static const int n = 1000005;
    static inline int prime[n];
    static inline int version = 0;
    static inline bool init = []() {
        prime[0] = -1;
        prime[1] = -1;
        for (int i = 2; i <= 1000; i++)
            if (prime[i] == 0)
                for (int j = i * i; j < n; j += i)
                    prime[j] = -1;
        return true;
    }();

public:
    int minJumps(vector<int>& nums) {
        int len = nums.size();
        int max = *max_element(nums.begin(), nums.end());

        vector<int> head(max + 1, -1);
        vector<int> next(len);

        for (int i = 0; i < len; i++) {
            next[i] = head[nums[i]];
            head[nums[i]] = i;
        }

        vector<int> dp(len, -1);
        dp[0] = 0;

        queue<int> queue;
        queue.push(0);

        version++;

        while (!queue.empty()) {
            int dq = queue.front();
            queue.pop();

            if (dq == len - 1)
                return dp[dq];

            int right = dq + 1;
            if (right < len && dp[right] == -1) {
                dp[right] = dp[dq] + 1;
                queue.push(right);
            }

            int left = dq - 1;
            if (left >= 0 && dp[left] == -1) {
                dp[left] = dp[dq] + 1;
                queue.push(left);
            }

            int val = nums[dq];
            if (prime[val] != -1 && prime[val] != version) {
                prime[val] = version;
                for (int i = val; i <= max; i += val) {
                    for (int j = head[i]; j != -1; j = next[j]) {
                        if (dp[j] == -1) {
                            dp[j] = dp[dq] + 1;
                            queue.push(j);
                        }
                    }
                    head[i] = -1;
                }
            }
        }

        return -1;
    }
};