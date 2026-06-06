/*
2574. Left and Right Sum Differences
You are given a 0-indexed integer array nums of size n.
Define two arrays leftSum and rightSum where:
leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element, leftSum[i] = 0.
rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element, rightSum[i] = 0.
Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.

Example 1:
Input: nums = [10,4,8,3]
Output: [15,1,11,22]
Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].
Example 2:
Input: nums = [1]
Output: [0]
Explanation: The array leftSum is [0] and the array rightSum is [0].
The array answer is [|0 - 0|] = [0].
 
Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 105
*/
/*
    APPROACH:
    Steps:
    1. Initialize two vectors `left` and `right` of the same size as `nums` with all elements as 0.
    2. Calculate the `left` array where each element at index `i` is the sum of all elements to the left of `i` in `nums`.
    3. Calculate the `right` array where each element at index `i` is the sum of all elements to the right of `i` in `nums`.
    4. Update the `nums` array where each element at index `i` is the absolute difference between `left[i]` and `right[i]`.
    5. Return the updated `nums` array.

    Time Complexity: O(n) - We traverse the `nums` array three times (for calculating `left`, `right`, and updating `nums`), resulting in a linear time complexity.
    Space Complexity: O(n) - We use two additional vectors `left` and `right` of the same size as `nums`, resulting in linear space complexity.
*/
class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
    vector<int>left(nums.size(),0) ,right(nums.size(),0);
    for(int i=1;i<nums.size();i++){
        left[i] = left[i-1]+ nums[i-1];
    }
    for(int i=nums.size()-2;i>=0;i--) right[i] =right[i+1]+nums[i+1];
    for(int i=0;i<left.size();i++) nums[i] = abs(left[i] - right[i]);
    return nums;
    }
};