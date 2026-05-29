/*
3300. Minimum Element After Replacement With Digit Sum
You are given an integer array nums.
You replace each element in nums with the sum of its digits.
Return the minimum element in nums after all replacements.
Example 1:
Input: nums = [10,12,13,14]
Output: 1
Explanation:
nums becomes [1, 3, 4, 5] after all replacements, with minimum element 1.
Example 2:
Input: nums = [1,2,3,4]
Output: 1
Explanation:
nums becomes [1, 2, 3, 4] after all replacements, with minimum element 1.
Example 3:
Input: nums = [999,19,199]
Output: 10
Explanation:
nums becomes [27, 10, 19] after all replacements, with minimum element 10.
Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 104
 */
 /*
    Approach:
        1. Initialize a variable res to store the minimum element, and set it to INT_MAX.
        2. Iterate through each element i in the input array nums.
        3. For each element i, calculate the sum of its digits:
        a. Initialize a variable temp to store the current element i and a variable sum to store the sum of digits, initialized to 0.
        b. While temp is greater than 0:
            i. Add the last digit of temp (temp % 10) to sum.
            ii. Remove the last digit from temp by performing integer division by 10 (temp /= 10).
        4. After calculating the sum of digits for the current element, update res to be the minimum of res and sum.
        5. After iterating through all elements in nums, return res as the minimum element after replacement with digit sum.

        Time Complexity: O(n * m), where n is the number of elements in nums and m is the number of digits in the largest element (at most 4 digits since nums[i] <= 10^4).
        Space Complexity: O(1), as we are using only a constant amount of extra space for variables.
 */
 class Solution {
public:
    int minElement(vector<int>& nums) {
        int res = INT_MAX;
        for(int i:nums){
            int temp = i ,sum = 0;
            while(temp){
                sum+=(temp%10);
                temp/=10;
            }
            res= min(res,sum);
        }
        return res;
    }
};