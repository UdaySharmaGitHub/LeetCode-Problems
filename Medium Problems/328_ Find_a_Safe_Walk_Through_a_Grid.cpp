/*
3286. Find a Safe Walk Through a Grid
You are given an m x n binary matrix grid and an integer health.
You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).
You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.
Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.
Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.

Example 1:
Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.

Example 2:
Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3
Output: false
Explanation:
A minimum of 4 health points is needed to reach the final cell safely.

Example 3:
Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.
Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 50
2 <= m * n
1 <= health <= m + n
grid[i][j] is either 0 or 1.
*/
const int N=5000;
int q[N], front, back;// implement deque
int maxH[N];
int d[5]={0, 1, 0, -1, 0};
class Solution {
public:
    static inline int idx(int i, int j, int c){ return i*c+j; }
    static bool outSide(int i, int j, int r, int c){
        return i<0||i>=r||j<0||j>=c;
    }
    static bool findSafeWalk(vector<vector<int>>& grid, int health) {
        const int r=grid.size(), c=grid[0].size();
        memset(maxH, -1, r*c*sizeof(int));
        front=back=N/2;// reset q
        q[back++]=0; 
        maxH[0]=health-grid[0][0];
        while(front<back){
            int ij=q[front++];// pop front
            int curH=maxH[ij];
            if (ij==r*c-1) return curH>0;
            auto [i, j]=div(ij, c);
            for(int a=0; a<4; a++){
                const int s=i+d[a], t=j+d[a+1];
                if (outSide(s, t, r, c)) continue;
                const int st=idx(s,t, c);
                int H2=curH-grid[s][t];
                if(H2>maxH[st]){
                    maxH[st]=H2;
                    if (grid[s][t]==0) q[--front]=st;
                    else q[back++]=st;
                }
            }
        }
        return 0;
    }
};