/*
2615. Sum of Distances
You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.

Return the array arr.

 

Example 1:

Input: nums = [1,3,1,1,2]
Output: [5,0,3,4,0]
Explanation: 
When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
When i = 1, arr[1] = 0 because there is no other index with value 3.
When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
When i = 4, arr[4] = 0 because there is no other index with value 2. 

Example 2:

Input: nums = [0,5,3]
Output: [0,0,0]
Explanation: Since each element in nums is distinct, arr[i] = 0 for all i.
 

Constraints:
1 <= nums.length <= 105
0 <= nums[i] <= 109
 */
 /*
    Optimnized Approach
    Time Complexity: O(n)
    Space Complexity: O(n)
 */
 class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> res(n, 0);
        unordered_map<int, vector<int>> mp;

        // Store indices
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }

        // Process each group
        for (auto &p : mp) {
            vector<int>& v = p.second;
            int m = v.size();

            vector<long long> prefix(m, 0);
            prefix[0] = v[0];

            for (int i = 1; i < m; i++) {
                prefix[i] = prefix[i - 1] + v[i];
            }

            for (int i = 0; i < m; i++) {
                long long left = 0, right = 0;

                if (i > 0) {
                    left = (long long)v[i] * i - prefix[i - 1];
                }

                if (i < m - 1) {
                    right = (prefix[m - 1] - prefix[i]) - (long long)v[i] * (m - i - 1);
                }

                res[v[i]] = left + right;
            }
        }

        return res;
    }
};
/*
    Brute Force Approach
    Time Complexity: O(n^2)
    Space Complexity: O(n)
*/
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        vector<long long> arr(nums.size(),0);
        unordered_map<int,vector<int>> map;
        for(int i=0;i<nums.size();i++) map[nums[i]].push_back(i);
        for(int i =0;i<nums.size();i++){
            if(map[nums[i]].size()>0){ // Check for the Condition of nums[i] == nums[j]
                for(int j:map[nums[i]]){ // traversing the array of map[nums[i]]
                    if(i!=j && abs(i-j)!=0) // Checking the Condition i!=j && nums[i] ==abs(i-j)
                    arr[i] += abs(i-j); 
                }
            }
        }
        return arr;
    }
};