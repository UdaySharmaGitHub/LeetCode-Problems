/*
3225. Maximum Score From Grid Operations
You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.
The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.
Return the maximum score that can be achieved after some number of operations.
Example 1:
Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
Output: 11
Explanation:
In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.
Example 2:
Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]
Output: 94
Explanation:
We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. The score of the resulting grid is grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4] which is equal to 94.
Constraints:
1 <= n == grid.length <= 100
n == grid[i].length
0 <= grid[i][j] <= 109
 */
 class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();
        if (m == 1) return 0;

        // prefix sum for each column
        vector<vector<long long>> col(m, vector<long long>(n + 1, 0));
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                col[j][i + 1] = col[j][i] + grid[i][j];
            }
        }

        // dp[curr][prev]
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
        vector<vector<long long>> prefMax(n + 1, vector<long long>(n + 1, 0));
        vector<vector<long long>> suffMax(n + 1, vector<long long>(n + 1, 0));

        for (int c = 1; c < m; c++) {

            vector<vector<long long>> newdp(n + 1, vector<long long>(n + 1, 0));

            for (int curr = 0; curr <= n; curr++) {
                for (int prev = 0; prev <= n; prev++) {

                    if (curr <= prev) {
                        long long gain = col[c][prev] - col[c][curr];

                        newdp[curr][prev] = max(
                            newdp[curr][prev],
                            suffMax[prev][0] + gain
                        );
                    }
                    else {
                        long long gain = col[c-1][curr] - col[c-1][prev];

                        newdp[curr][prev] = max({
                            newdp[curr][prev],
                            suffMax[prev][curr],
                            prefMax[prev][curr] + gain
                        });
                    }
                }
            }

            // build prefix max & suffix max
            for (int curr = 0; curr <= n; curr++) {

                prefMax[curr][0] = newdp[curr][0];

                for (int prev = 1; prev <= n; prev++) {

                    long long penalty = 0;
                    if (prev > curr)
                        penalty = col[c][prev] - col[c][curr];

                    prefMax[curr][prev] = max(
                        prefMax[curr][prev-1],
                        newdp[curr][prev] - penalty
                    );
                }

                suffMax[curr][n] = newdp[curr][n];

                for (int prev = n-1; prev >= 0; prev--) {
                    suffMax[curr][prev] = max(
                        suffMax[curr][prev+1],
                        newdp[curr][prev]
                    );
                }
            }

            dp = move(newdp);
        }

        long long ans = 0;
        for (int k = 0; k <= n; k++) {
            ans = max({ans, dp[0][k], dp[n][k]});
        }

        return ans;
    }
};