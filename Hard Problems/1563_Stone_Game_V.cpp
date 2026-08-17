/*
1563. Stone Game V
There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.
The game ends when there is only one stone remaining. Alice's score is initially zero.
Return the maximum score that Alice can obtain.
 
Example 1:
Input: stoneValue = [6,2,3,4,5,5]
Output: 18
Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.
Example 2:
Input: stoneValue = [7,7,7,7,7,7,7]
Output: 28
Example 3:
Input: stoneValue = [4]
Output: 0
Constraints:
1 <= stoneValue.length <= 500
1 <= stoneValue[i] <= 106
*/
int dp[501][501];
int Sum[501];
class Solution {
public:
    static int f(int l, int r){
        if (dp[l][r]!=-1)  return dp[l][r];
        int ans=0;
        for (int m=l; m<r; m++){
            int Lsum=Sum[m+1]-Sum[l], Rsum=Sum[r+1]-Sum[m+1];
            
            if (Lsum<=Rsum) ans=max(ans, Lsum+f(l, m));
            if (Lsum>=Rsum) ans=max(ans, Rsum+f(m+1, r));
            //Pruning branch
            if (2*min(Lsum, Rsum)<=ans) break;
        }
        return dp[l][r]=ans;
    }

    static int stoneGameV(vector<int>& stoneValue) {
        const int n=stoneValue.size();
        partial_sum(stoneValue.begin(), stoneValue.end(), Sum+1);
        for(int i=0; i<=n; i++)
            memset(dp[i], -1, sizeof(int)*(n+1));
        return f(0, n-1);
    }
};


auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();