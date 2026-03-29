/*
2946. Matrix Similarity After Cyclic Shifts
You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.
The following proccess happens k times:
Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.
Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.
Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.

Example 1:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
Output: false
Explanation:
In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).

Example 2:
Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2
Output: true
Explanation:

Example 3:
Input: mat = [[2,2],[2,2]], k = 3
Output: true
Explanation:
As all the values are equal in the matrix, even after performing cyclic shifts the matrix will remain the same.
Constraints:
1 <= mat.length <= 25
1 <= mat[i].length <= 25
1 <= mat[i][j] <= 25
1 <= k <= 50
*/
/*
    Approach-1
    Time Complexity: O(m*n)
    Space Complexity: O(1)
*/
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        k %= n;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(i % 2 == 0) {
                    // even row → left shift
                    if(mat[i][j] != mat[i][(j + k) % n]) return false;
                } else {
                    // odd row → right shift
                    if(mat[i][j] != mat[i][(j - k + n) % n]) return false;
                }
            }
        }
        return true;
    }
};
/*
    Approach-2
    Using Reverse Function
    Time Complexity: O(m*n)
    Space Complexity: O(m*n)
*/
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {

        vector<vector<int>> temp = mat;
        int m = mat.size() , n = mat[0].size();
        if(k>=n)k%=n;
        if(k==0) return 1;

        for(vector<int> &arr:mat){
            if(n&1){
                reverse(arr.begin(),arr.begin()+k);
                reverse(arr.begin()+k,arr.end());
                reverse(arr.begin(),arr.end());
            }
            else{
                reverse(arr.begin()+k,arr.end());
                reverse(arr.begin(),arr.begin()+k);
                reverse(arr.begin(),arr.end());
            }
        }

    for(int i=0;i<m;i++){
        for(int j = 0;j<n;j++){
            if(mat[i][j] != temp[i][j])return 0;
        }
    }
    return 1;
    }
};