/*
Given an array nums, return true if the array was originally sorted in 
non-decreasing order, then rotated some number of positions (including zero). 
Otherwise, return false.
There may be duplicates in the original array.
Note: An array A rotated by x positions results in an array B of the same length such that 
A[i] == B[(i+x) % A.length], where % is the modulo operation.
Example 1:
Input: nums = [3,4,5,1,2]
Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 3 positions to begin on the the element of value 3: [3,4,5,1,2].
Example 2:
Input: nums = [2,1,3,4]
Output: false
Explanation: There is no sorted array once rotated that can make nums.
Example 3:
Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.
 
Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
*/
/*
    APPROACH:
    Step:
    1. We will iterate through the array and count the number of times the current element is greater than the next element. This will help us identify the number of rotations.
    2. We will also check if the last element is greater than the first element, which indicates a rotation at the end of the array.
    3. If the count of rotations is less than or equal to 1, it means the array is sorted and rotated at most once, and we will return true. Otherwise, we will return false.

    Time Complexity: O(n) - We need to iterate through the array once.
    Auxiliary Space: O(1) - We are using a constant amount of space to store the count and other variables.
*/
class Solution {
public:
    bool check(vector<int>& nums) {
        int count = 0;
        for(int i =1; i< nums.size();i++){
            if(nums[i-1]>nums[i]){
                count++;
            }
        }
        if(nums[nums.size()-1] >nums[0]){
            count++;
        }
        return count<=1;
    }
};