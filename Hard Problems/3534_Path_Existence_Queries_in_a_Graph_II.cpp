/*
3534. Path Existence Queries in a Graph II
You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
You are also given an integer array nums of length n and an integer maxDiff.
An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.
Return an array answer, where answer[i] is the result of the ith query.
Note: The edges between the nodes are unweighted.
 
Example 1:
Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
Output: [1,1]
Explanation:
The resulting graph is:
Query	Shortest Path	Minimum Distance
[0, 3]	0 → 3	1
[2, 4]	2 → 4	1
Thus, the output is [1, 1].

Example 2:
Input: n = 5, nums = [5,3,1,9,10], maxDiff = 2, queries = [[0,1],[0,2],[2,3],[4,3]]
Output: [1,2,-1,1]
Explanation:
The resulting graph is:
Query	Shortest Path	Minimum Distance
[0, 1]	0 → 1	1
[0, 2]	0 → 1 → 2	2
[2, 3]	None	-1
[4, 3]	3 → 4	1
Thus, the output is [1, 2, -1, 1].

Example 3:
Input: n = 3, nums = [3,6,1], maxDiff = 1, queries = [[0,0],[0,1],[1,2]]
Output: [0,-1,-1]
Explanation:
There are no edges between any two nodes because:
Nodes 0 and 1: |nums[0] - nums[1]| = |3 - 6| = 3 > 1
Nodes 0 and 2: |nums[0] - nums[2]| = |3 - 1| = 2 > 1
Nodes 1 and 2: |nums[1] - nums[2]| = |6 - 1| = 5 > 1
Thus, no node can reach any other node, and the output is [0, -1, -1].
Constraints:
1 <= n == nums.length <= 105
0 <= nums[i] <= 105
0 <= maxDiff <= 105
1 <= queries.length <= 105
queries[i] == [ui, vi]
0 <= ui, vi < n
*/
constexpr int L=18, N=1e5+1;
using int2=pair<int, int>;
int up[L][N], pos[N]; 
int2 xId[N];

class Solution {
public:
    static int cnt(int u, int v, int L) {
        if (u==v) return 0;
        if (up[0][u]>=v) return 1;
        // cannot reach v
        if (up[L-1][u]<v) return -1; 

        int step=0;
        for (int j=L-1; j>=0; j--) { 
            if (up[j][u]<v) { // Only jump when satisfied
                step+=(1<<j);
                u=up[j][u];
            }
        }
        return step+1;
    }

    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        int maxL=bit_width((unsigned)n)+1;
        for(int i=0; i<n; i++) 
            xId[i]={nums[i], i};
        
        sort(xId, xId+n);
        for (int i=0; i<n; i++)// pos of index in sorted xId
            pos[xId[i].second]=i;
        
        //sliding window 
        for (int l=0, r=0; l<n; l++) {
            while (r+1<n && xId[r+1].first-xId[l].first<=maxDiff) 
                r++;
            up[0][l]=r;
        }

        // Compute binary lifting tables
        for (int j=1; j<maxL; j++) {
            for (int i=0; i<n; i++) {
                up[j][i]=up[j-1][up[j-1][i]];
            }
        }

        const int qz=queries.size();
        vector<int> ans(qz);
        int i=0;
        for (auto& q : queries) {
            auto [u, v]=minmax(pos[q[0]], pos[q[1]]);
            ans[i++]=cnt(u, v, maxL);
        }
        return ans;
    }
};