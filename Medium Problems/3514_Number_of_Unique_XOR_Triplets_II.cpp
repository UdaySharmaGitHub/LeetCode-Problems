/*
3514. Number of Unique XOR Triplets II
You are given an integer array nums.
A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
Return the number of unique XOR triplet values from all possible triplets (i, j, k).
 
Example 1:
Input: nums = [1,3]
Output: 2
Explanation:
The possible XOR triplet values are:
(0, 0, 0) → 1 XOR 1 XOR 1 = 1
(0, 0, 1) → 1 XOR 1 XOR 3 = 3
(0, 1, 1) → 1 XOR 3 XOR 3 = 1
(1, 1, 1) → 3 XOR 3 XOR 3 = 3
The unique XOR values are {1, 3}. Thus, the output is 2.
Example 2:
Input: nums = [6,7,8,9]
Output: 4
Explanation:
The possible XOR triplet values are {6, 7, 8, 9}. Thus, the output is 4.
Constraints:
1 <= nums.length <= 1500
1 <= nums[i] <= 1500
*/
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int max_xor = 2048;

        vector<bool> pair_xor(max_xor, false);
        vector<bool> triplet_xor(max_xor, false);

        int n = nums.size();

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                pair_xor[nums[i] ^ nums[j]] = true;
            }
        }

        for (int x = 0; x < max_xor; x++) {
            if (!pair_xor[x]) continue;
            for (int v : nums) {
                triplet_xor[x ^ v] = true;
            }
        }

        int count = 0;
        for(int i = 0; i < max_xor; i++){
            if(triplet_xor[i]) count++;
        }

        return count;
    }
};