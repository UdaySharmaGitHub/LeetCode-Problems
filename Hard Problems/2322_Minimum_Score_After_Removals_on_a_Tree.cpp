/*
2322. Minimum Score After Removals on a Tree
There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
Remove two distinct edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:
Get the XOR of all the values of the nodes for each of the three components respectively.
The difference between the largest XOR value and the smallest XOR value is the score of the pair.
For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and the smallest XOR value is 3. The score is then 8 - 3 = 5.
Return the minimum score of any possible pair of edge removals on the given tree.
Example 1:
Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
Output: 9
Explanation: The diagram above shows a way to make a pair of removals.
- The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
- The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
- The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
It can be shown that no other pair of removals will obtain a smaller score than 9.
Example 2:
Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
Output: 0
Explanation: The diagram above shows a way to make a pair of removals.
- The 1st component has nodes [3,4] with values [4,4]. Its XOR value is 4 ^ 4 = 0.
- The 2nd component has nodes [1,0] with values [5,5]. Its XOR value is 5 ^ 5 = 0.
- The 3rd component has nodes [2,5] with values [2,2]. Its XOR value is 2 ^ 2 = 0.
The score is the difference between the largest and smallest XOR value which is 0 - 0 = 0.
We cannot obtain a smaller score than 0.
Constraints:
n == nums.length
3 <= n <= 1000
1 <= nums[i] <= 108
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.
*/
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

class Solution {
public:
    std::vector<int> subtree_xor;
    std::vector<std::unordered_set<int>> descendants;
    std::vector<std::vector<int>> graph;

    void dfs(int node, int parent, const std::vector<int>& nums) {
        subtree_xor[node] = nums[node];
        descendants[node].insert(node);

        for (int neighbor : graph[node]) {
            if (neighbor != parent) {
                dfs(neighbor, node, nums);
                subtree_xor[node] ^= subtree_xor[neighbor];
                descendants[node].insert(descendants[neighbor].begin(), descendants[neighbor].end());
            }
        }
    }

    int minimumScore(std::vector<int>& nums, std::vector<std::vector<int>>& edges) {
        int n = nums.size();
        graph.assign(n, std::vector<int>());
        subtree_xor.assign(n, 0);
        descendants.assign(n, std::unordered_set<int>());

        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        dfs(0, -1, nums);

        int total_xor = subtree_xor[0];
        int min_score = INT_MAX;

        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int xor_i = subtree_xor[i];
                int xor_j = subtree_xor[j];
                int val1, val2, val3;

                if (descendants[i].count(j)) { // j is in i's subtree
                    val1 = xor_j;
                    val2 = xor_i ^ xor_j;
                    val3 = total_xor ^ xor_i;
                } else if (descendants[j].count(i)) { // i is in j's subtree
                    val1 = xor_i;
                    val2 = xor_j ^ xor_i;
                    val3 = total_xor ^ xor_j;
                } else { // Independent subtrees
                    val1 = xor_i;
                    val2 = xor_j;
                    val3 = total_xor ^ xor_i ^ xor_j;
                }
                
                int score = std::max({val1, val2, val3}) - std::min({val1, val2, val3});
                min_score = std::min(min_score, score);
            }
        }

        return min_score;
    }
};