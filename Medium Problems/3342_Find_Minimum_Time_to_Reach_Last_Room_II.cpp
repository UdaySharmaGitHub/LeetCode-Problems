/*
3342. Find Minimum Time to Reach Last Room II
There is a dungeon with n x m rooms arranged as a grid.
You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.
Return the minimum time to reach the room (n - 1, m - 1).
Two rooms are adjacent if they share a common wall, either horizontally or vertically.
Example 1:
Input: moveTime = [[0,4],[4,4]]
Output: 7
Explanation:
The minimum time required is 7 seconds.
At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.
Example 2:
Input: moveTime = [[0,0,0,0],[0,0,0,0]]
Output: 6
Explanation:
The minimum time required is 6 seconds.
At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in two seconds.
At time t == 3, move from room (1, 1) to room (1, 2) in one second.
At time t == 4, move from room (1, 2) to room (1, 3) in two seconds.
Example 3
Input: moveTime = [[0,1],[1,2]]
Output: 4
Constraints:
2 <= n == moveTime.length <= 750
2 <= m == moveTime[i].length <= 750
0 <= moveTime[i][j] <= 109
*/
class Solution {
    public:
        int minTimeToReach(vector<vector<int>>& moveTime) {
            int n = moveTime.size(), m = moveTime[0].size();
            vector<vector<int>> dp(n, vector<int>(m, INT_MAX));
            priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minh;
            minh.push({0, 0, 0});    
            moveTime[0][0] = 0;
    
            vector<vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            while (!minh.empty()) {
                auto current = minh.top();
                minh.pop();
                int currTime = current[0];
                int currRow  = current[1];
                int currCol  = current[2];
                if (currTime >= dp[currRow][currCol]) continue;
                if (currRow == n - 1 && currCol == m - 1) return currTime;
                dp[currRow][currCol] = currTime;
    
                for (auto& direction : directions) {
                    int nextRow = currRow + direction[0];
                    int nextCol = currCol + direction[1];
                    if (nextRow >= 0 && nextRow < n &&
                        nextCol >= 0 && nextCol < m &&
                        dp[nextRow][nextCol] == INT_MAX) {
                        int cost = (currRow + currCol) % 2 + 1; 
                        int start = max(moveTime[nextRow][nextCol], currTime);
                        int nextTime = start + cost;
                        minh.push({nextTime, nextRow, nextCol});
                    }
                }
            }
            return -1;
        }
    };