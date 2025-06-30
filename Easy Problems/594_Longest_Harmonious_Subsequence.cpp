/*
594. Longest Harmonious Subsequence
We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.
Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.
Example 1:
Input: nums = [1,3,2,2,5,2,3,7]
Output: 5
Explanation:
The longest harmonious subsequence is [3,2,2,2,3].
Example 2:
Input: nums = [1,2,3,4]
Output: 2
Explanation:
The longest harmonious subsequences are [1,2], [2,3], and [3,4], all of which have a length of 2.
Example 3:
Input: nums = [1,1,1,1]
Output: 0
Explanation:
No harmonic subsequence exists.
Constraints:
1 <= nums.length <= 2 * 104
-109 <= nums[i] <= 109
*/
/*
    Time Complexity: O(n*log(n))
    Space Complexity: O(1)
*/
class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int j = 0, maxLength = 0;

        for (int i = 0; i < nums.size(); ++i) {
            while (nums[i] - nums[j] > 1) {
                ++j;
            }
            if (nums[i] - nums[j] == 1) {
                maxLength = max(maxLength, i - j + 1);
            }
        }
        return maxLength;
    }
};
/*
    Time Complexity: O(n*n)
    Space Complexity: O(1)
*/
class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int res = 0;
        for(int i=0;i<nums.size()-1;i++){
            for(int j = i+1;j<nums.size();j++){
                if(nums[j] - nums[i] == 1 ) res =max(res,j-i+1);
            }
        }
        return res;
    }
};