/*
1306. Jump Game III
Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
Notice that you can not jump outside of the array at any time.
Example 1:
Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
Example 2:
Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
Example 3:
Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
Constraints:
1 <= arr.length <= 5 * 104
0 <= arr[i] < arr.length
0 <= start < arr.length
*/
/*
    APPROACH: BFS
    1. We can use a queue to perform BFS and a vector to keep track of visited indices.
    2. We start from the given start index and explore all possible jumps (i + arr[i] and i - arr[i]).
    3. We keep track of the visited indices to avoid cycles and ensure we do not revisit the same index.
    4. The BFS continues until we reach an index with value 0, at which point we return true. If we exhaust the queue without reaching an index with value 0, we return false.

    TIME COMPLEXITY: O(n) - Each index is visited at most once.
    SPACE COMPLEXITY: O(n) - The queue and the visited vector can both grow up to O(n) in the worst case.
*/
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();

        vector<bool> visited(n, false);
        queue<int> q;

        q.push(start);

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (i < 0 || i >= n || visited[i])
                continue;

            if (arr[i] == 0)
                return true;

            visited[i] = true;

            q.push(i + arr[i]);
            q.push(i - arr[i]);
        }

        return false;
    }
};