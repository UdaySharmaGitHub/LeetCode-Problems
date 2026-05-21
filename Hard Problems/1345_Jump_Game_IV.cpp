/*
1345. Jump Game IV
Given an array of integers arr, you are initially positioned at the first index of the array.
In one step you can jump from index i to index:
i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.
Notice that you can not jump outside of the array at any time.
Example 1:
Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:
Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You do not need to jump.
Example 3:
Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.

Constraints:
1 <= arr.length <= 5 * 104
-108 <= arr[i] <= 108
*/
/*
    APPROACH: BFS
    1. We can use a queue to perform BFS and a map to store the indices of the same values in the array.
    2. We start from the first index and explore all possible jumps (i + 1, i - 1, and j where arr[i] == arr[j]).
    3. We keep track of the visited indices to avoid cycles and ensure we do not revisit the same index.
    4. We also clear the list of indices for the current value after processing to prevent redundant jumps in future iterations.
    5. The BFS continues until we reach the last index, at which point we return the number of steps taken. If we exhaust the queue without reaching the last index, we return -1 (though this case should not occur given the problem constraints).

    TIME COMPLEXITY: O(n) - Each index is visited at most once.
    SPACE COMPLEXITY: O(n) - The queue and the map can both grow up to O(n) in the worst case.
*/
class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n=arr.size();
        if(n==1)return 0;
        unordered_map<int,vector<int>>mp;
        for (int i=0;i<n;i++){
            mp[arr[i]].push_back(i);
        }
        queue<pair<int,int>>q;
        q.push({0,0});
        vector<int>vis(n,0);
        vis[0]=1;
        while(!q.empty()){
            int node=q.front().first;
            int dist=q.front().second;
            q.pop();
            if(node==n-1)return dist;
            if(node-1>=0 && !vis[node-1]){
                vis[node-1]=1;
                q.push({node-1,dist+1});
            }
            if(node+1<n && !vis[node+1]){
                vis[node+1]=1;
                q.push({node+1,dist+1});
            }
            for (int next:mp[arr[node]]){
                if (!vis[next]){
                    vis[next]=1;
                    q.push({next,dist+1});
                }
            }
            mp[arr[node]].clear();
        }
        return -1;
    }
};