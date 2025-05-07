/*
1007. Minimum Domino Rotations For Equal Row

In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.
If it cannot be done, return -1.
Example 1:
Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
Output: 2
Explanation: 
The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
Example 2:
Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
Output: -1
Explanation: 
In this case, it is not possible to rotate the dominoes to make one row of values equal.
Constraints:
2 <= tops.length <= 2 * 104
bottoms.length == tops.length
1 <= tops[i], bottoms[i] <= 6
*/
class Solution {
    public:
    int checkEqual(vector<int> tops, vector<int> bottoms,int maxa){
                int count =0 ;
            for(int i=0;i<tops.size();i++){
                if(tops[i] != maxa && bottoms[i] == maxa){bottoms[i] = tops[i]; tops[i] = maxa; count++;}}
                for(int i:tops) if(i!=maxa) return -1;
                return count;
    }
        int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
            unordered_map<int,int> map;
            for(int i:tops) map[i]++;
            for(int i:bottoms) map[i]++;
            int maxa = INT_MIN,occ = 0;
            for(auto i:map){ if(i.second >occ){occ = i.second ; maxa = i.first;}   }
            if(occ<tops.size()) return -1;
            int topCount = checkEqual(tops,bottoms,maxa);
            int bottomCount = checkEqual(bottoms,tops,maxa);
    
        if(topCount == -1 && bottomCount == -1)return -1;
        return min(topCount,bottomCount);
        }
    };