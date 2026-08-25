/*
3718. Smallest Missing Multiple of K
Given an integer array nums and an integer k, return the smallest positive multiple of k that is missing from nums.
A multiple of k is any positive integer divisible by k.
Example 1:
Input: nums = [8,2,3,4,6], k = 2
Output: 1

Explanation:
The multiples of k = 2 are 2, 4, 6, 8, 10, 12... and the smallest multiple missing from nums is 10.
Example 2:
Input: nums = [1,4,7,10,15], k = 5
Output: 5
Explanation:
The multiples of k = 5 are 5, 10, 15, 20... and the smallest multiple missing from nums is 5.
 
Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 100
*/
/*
    APPROACH: Based on Given Constraints
    Steps:
    1. Create a boolean vector freq of size 101 initialized to false, which will be used to mark the presence of elements in nums.
    2. Iterate through the nums array and mark the corresponding indices in the freq vector as true for each element in nums.
    3. Initialize a variable i to k, which will be used to check for multiples of k.
    4. Use a while loop to check if i is less than or equal to 100. Inside the loop, check if freq[i] is false, which means i is missing from nums. If it is missing, return i as the result.
    5. If i is present in nums, increment i by k to check the next multiple of k.
    6. If the loop completes and all multiples of k up to 100 are present in nums, return the next multiple of k after 100, which is (( 100 / k) + 1) * k.
    
    Time Complexity: o(n) because we are iterating through the nums array once to populate the freq vector and then checking for the missing multiple in a while loop.
    Space Complexity: o(1) because we are using a fixed-size boolean vector of size 101 to store the presence of elements in nums, which does not depend on the size of the input array.
*/
class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        vector<bool> freq(101,0);

        for(int i=0;i<nums.size();i++)
        freq[nums[i]] = 1;

        int i = k;
        while(i <= 100) {
            if(!freq[i])
            return i;
            i += k;
        }
        return ((100 / k) + 1) * k;
    }
};

/*
    APPROACH: Using HASHMAP
    Steps:
    1. Initialize an unordered_map to store the frequency of elements in nums.
    2. Iterate through the nums array and populate the unordered_map with the frequency of each element.
    3. Initialize a variable res to k, which will be used to find the smallest missing multiple of k.
    4. Use a while loop to check if res is present in the unordered_map. If it is present, increment res by k to check the next multiple.   
    5. Continue this process until res is not found in the unordered_map, which means it is the smallest missing multiple of k.
    6. Return res as the result.

    Time Complexity: o(n) because we are iterating through the nums array once to populate the unordered_map and then checking for the missing multiple in a while loop.
    Space Complexity: o(n) because we are using an unordered_map to store the frequency of elements in nums.
*/
class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        for(int n:nums) map[n]++;
        int res = k;
        while(map.find(res)!=map.end()){
            res+=k;
        }
        return res;
    }
};