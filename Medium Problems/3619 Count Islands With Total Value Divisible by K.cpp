/*
3619. Count Islands With Total Value Divisible by K
You are given an m x n matrix grid and a positive integer k. An island is a group of positive integers (representing land) that are 4-directionally connected (horizontally or vertically).
The total value of an island is the sum of the values of all cells in the island.
Return the number of islands with a total value divisible by k.
 
Example 1:
Input: grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5
Output: 2
Explanation:
The grid contains four islands. The islands highlighted in blue have a total value that is divisible by 5, while the islands highlighted in red do not.
Example 2:

Input: grid = [[3,0,3,0], [0,3,0,3], [3,0,3,0]], k = 3
Output: 6
Explanation:
The grid contains six islands, each with a total value that is divisible by 3.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
0 <= grid[i][j] <= 106
1 <= k <= 106
*/
class Solution {
private:
    // DFS function to explore the island and calculate its total sum
    long long dfs(int r, int c, int m, int n, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        // Mark the current cell as visited
        visited[r][c] = true;
        long long current_sum = grid[r][c];
        
        // 4 possible directions: Up, Down, Left, Right
        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; i++) {
            int nextRow = r + dRow[i];
            int nextCol = c + dCol[i];
            
            // Check boundaries, whether it's land (> 0), and if it has been visited
            if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n && 
                grid[nextRow][nextCol] > 0 && !visited[nextRow][nextCol]) {
                current_sum += dfs(nextRow, nextCol, m, n, grid, visited);
            }
        }
        
        return current_sum;
    }

public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int validIslandCount = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If we find an unvisited land cell, start exploring the island
                if (grid[i][j] > 0 && !visited[i][j]) {
                    long long islandSum = dfs(i, j, m, n, grid, visited);
                    
                    // Check if the total sum of the island is divisible by k
                    if (islandSum % k == 0) {
                        validIslandCount++;
                    }
                }
            }
        }
        
        return validIslandCount;
    }
};