/*
Exactly One Path
You are given two integers m and n, representing the number of rows and columns of a grid.
Construct any m x n grid consisting only of the characters '.' and '#', where:
'.' represents a free cell.
'#' represents an obstacle cell.
A valid path is a sequence of free cells that:
Starts at the top-left cell (0, 0).
Ends at the bottom-right cell (m - 1, n - 1).
Moves only:
Right, from (i, j) to (i, j + 1), or
Down, from (i, j) to (i + 1, j).
Return any grid such that there is exactly one valid path from the top-left cell to the bottom-right cell.
Example 1:
Input: m = 2, n = 3
Output: ["..#","#.."]
Explanation:
The only valid path is: (0,0) → (0,1) → (1,1) → (1,2)
Example 2:
Input: m = 3, n = 3
Output: ["..#","#..","##."]
Explanation:

The only valid path is: (0,0) → (0,1) → (1,1) → (1,2) → (2,2)
Example 3:
Input: m = 1, n = 4
Output: ["...."]
Explanation:
The only valid path is: (0,0) → (0,1) → (0,2) → (0,3)
 
Constraints:
1 <= m, n <= 25
*/
/*
    Approach: Zig-Zig Pattern
    Steps;
    1.  Fill the first row with free cells ('.').
    2.  Fill the last column with free cells ('.').
    3.  This ensures there is exactly one valid path from the top-left to the bottom-right cell.

    Time Complexity: O(m + n)
    Space Complexity: O(m * n)
*/
class Solution {
public:
    vector<string> createGrid(int m, int n) {
        // Initialize the grid with all obstacles ('#')
        vector<string> res(m, string(n, '#'));
        
        // Fill the first row with free cells ('.')
        for (int j = 0; j < n; j++) {
            res[0][j] = '.';
        }
        
        // Fill the last column with free cells ('.')
        for (int i = 0; i < m; i++) {
            res[i][n - 1] = '.';
        }
        
        return res;
    }
};

/*
    This Code follow Zig-Zig Pattern in the matrices
*/

class Solution {
public:
    vector<string> createGrid(int m, int n) {
        if(m==1){
            vector<string> s;
            if(n==1) s.push_back(".");
            else s.push_back(string(n,'.'));

            return s;
        }
        if(n==1){
            vector<string> s;
            for(int i =0 ;i<m;i++) s.push_back(".");
            return s;
        }


        vector<string> res(m, string(n, '#'));
        int i = 0 , row = 0;
        for(;row<m && i<n;row++){
            res[row][i++] = '.';
            if(i<n) res[row][i]='.';
        }
        if(row==m){
            row--;
            for(;i<n;i++) res[row][i]='.';
        }
        else if(i==n && row <m){
            i--;
            for(;row<m;row++ ) res[row][i]='.';
        }
        return res;
        
    }
};