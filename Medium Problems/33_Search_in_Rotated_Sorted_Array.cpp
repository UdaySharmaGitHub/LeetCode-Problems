/*
33. Search in Rotated Sorted Array
There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].
Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:
Input: nums = [1], target = 0
Output: -1
 

Constraints:
1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-104 <= target <= 104
*/
/*
    APPROACH:
    Step:
    1. We will use a modified binary search algorithm to find the target in the rotated sorted array.
    2. We will initialize two pointers, low and high, to the start and end of the array, respectively.
    3. We will calculate the mid index and check if the element at mid is equal to the target. If it is, we will return the mid index.
    4. If the element at mid is greater than or equal to the element at low, it means the left half of the array is sorted. We will check if the target is within the range of the left half. If it is, we will move the high pointer to mid - 1; otherwise, we will move the low pointer to mid + 1.
    5. If the element at mid is less than the element at low, it means the right half of the array is sorted. We will check if the target is within the range of the right half. If it is, we will move the low pointer to mid + 1; otherwise, we will move the high pointer to mid - 1.
    6. We will repeat this process until the low pointer is less than or equal to the high pointer. If we exit the loop without finding the target, we will return -1.

    Time Complexity: O(log n) - We are using a binary search approach.
    Auxiliary Space: O(1) - We are using a constant amount of space for the pointers and variables.
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] >= nums[low]) {
                if (nums[mid] < target || target < nums[low]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else {
                if (target < nums[mid] || target > nums[high]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return -1;
    }
};