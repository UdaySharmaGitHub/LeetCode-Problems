/*
3546. Equal Sum Grid Partition I
You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
Each of the two resulting sections formed by the cut is non-empty.
The sum of the elements in both sections is equal.
Return true if such a partition exists; otherwise return false.

Example 1:
Input: grid = [[1,4],[2,3]]
Output: true
Explanation:
A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.
Example 2:
Input: grid = [[1,3],[2,4]]
Output: false
Explanation:
No horizontal or vertical cut results in two non-empty sections with equal sums. Thus, the answer is false.
Constraints:
1 <= m == grid.length <= 105
1 <= n == grid[i].length <= 105
2 <= m * n <= 105
1 <= grid[i][j] <= 105
*/

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        vector<long long int> row , col;
        long long int m = grid.size(), n = grid[0].size();
        
        // finding sum of each rows in grid
        for(long long int i=0;i<m;i++){ long long int sum = 0;
            for(long long int j=0;j<n;j++) sum+=grid[i][j];
            row.push_back(sum);
        }

        // finding sum of each column in grid
        for(int i=0;i<n;i++){ long long int sum = 0;
            for(int j=0;j<m;j++) sum+=grid[j][i];
            col.push_back(sum);
        }

        long long int preRowSum = 0 , preColSum = 0,tempSum =0;
        for(long long int i:row) preRowSum+=i;
        for(long long int i=0;i<row.size()-1;i++){
            tempSum += row[i];
            preRowSum -= row[i];
            if(tempSum == preRowSum ) return 1;
        }
        tempSum =0 ;
        for(long long int i:col) preColSum +=i;
        for(long long int i=0;i<col.size()-1;i++){
            tempSum += col[i];
            preColSum -= col[i];
            if(tempSum == preColSum ) return 1;
        }

        return 0;
    }
};