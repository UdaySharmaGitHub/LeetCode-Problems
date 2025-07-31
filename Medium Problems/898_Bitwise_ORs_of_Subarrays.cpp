/*
898. Bitwise ORs of Subarrays
Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
A subarray is a contiguous non-empty sequence of elements within an array.
Example 1:
Input: arr = [0]
Output: 1
Explanation: There is only one possible result: 0.
Example 2:
Input: arr = [1,1,2]
Output: 3
Explanation: The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.
Example 3:
Input: arr = [1,2,4]
Output: 6
Explanation: The possible results are 1, 2, 3, 4, 6, and 7.
Constraints:
1 <= arr.length <= 5 * 104
0 <= arr[i] <= 109
*/
#include <vector>
#include <unordered_set>

class Solution {
public:
    int subarrayBitwiseORs(std::vector<int>& arr) {
        // This set will store all unique OR values found across all subarrays.
        std::unordered_set<int> result_ors;
        
        // This set stores the distinct ORs of all subarrays ending at the previous position.
        std::unordered_set<int> current_ors;

        for (int x : arr) {
            // `next_ors` will store the ORs of subarrays ending at the current element `x`.
            std::unordered_set<int> next_ors;
            
            // The subarray of just the element x gives an OR of x.
            next_ors.insert(x);

            // Compute new ORs by extending previous subarrays with the current element x.
            for (int y : current_ors) {
                next_ors.insert(x | y);
            }

            // Add all newly found ORs to the main result set.
            result_ors.insert(next_ors.begin(), next_ors.end());
            
            // For the next iteration, the current results become the previous results.
            current_ors = next_ors;
        }

        return result_ors.size();
    }
};