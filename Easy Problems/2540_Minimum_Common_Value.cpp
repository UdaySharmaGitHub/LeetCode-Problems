/*
2540. Minimum Common Value
Given two integer arrays nums1 and nums2, sorted in non-decreasing order, return the minimum integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.
Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one occurrence of that integer.
 
Example 1:
Input: nums1 = [1,2,3], nums2 = [2,4]
Output: 2
Explanation: The smallest element common to both arrays is 2, so we return 2.

Example 2:
Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
Output: 2
Explanation: There are two common elements in the array 2 and 3 out of which 2 is the smallest, so 2 is returned.

Constraints:
1 <= nums1.length, nums2.length <= 105
1 <= nums1[i], nums2[j] <= 109
Both nums1 and nums2 are sorted in non-decreasing order.
*/
/*
    APPROACH:
    1. We can use two pointers to traverse both arrays simultaneously.
    2. We compare the current elements of both arrays:
       - If they are equal, we have found the minimum common value, and we return it.
       - If the element in nums1 is smaller than the element in nums2, we move the pointer in nums1 to the right to find a larger value.
       - If the element in nums2 is smaller than the element in nums1, we move the pointer in nums2 to the right to find a larger value.
    3. If we reach the end of either array without finding a common value, we return -1.

    TIME COMPLEXITY: O(n + m), where n and m are the lengths of nums1 and nums2 respectively.
    SPACE COMPLEXITY: O(1), as we are using only a constant amount of
*/
class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int i=0 , j =0;
        while(i<nums1.size() && j < nums2.size()){
            int n1 = nums1[i] , n2 = nums2[j];
            if(n1 == n2){return n1 ;}
            else if(n1 > n2){j++;}
            else{i++;}
        }
        return -1;
    }
};