/*
3121. Count the Number of Special Characters II
You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
Return the number of special letters in word.
Example 1:
Input: word = "aaAbcBC"
Output: 3
Explanation:
The special characters are 'a', 'b', and 'c'.
Example 2

Input: word = "abc
Output: 0
Explanation:
There are no special characters in word.
Example 3:
Input: word = "AbBCab"
Output: 0
Explanation:
There are no special characters in word.
Constraints:
1 <= word.length <= 2 * 105
word consists of only lowercase and uppercase English letters.
*/
// Online C++ compiler to run C++ program online
class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int>mpl(26 , -1);
        vector<int>mpu(26 , -1);
        int n = word.size(); 
        for(int i = 0 ; i < n ; i++){
            char a = word[i]; 
            if(islower(a)){
                mpl[a-'a'] = i ; 
            }else{
                if(mpu[a-'A'] != -1){
                    continue ;
                }else{
                    mpu[a-'A'] = i; 
                }
            }
        }
        int ans = 0 ; 
        for(int i = 0 ; i < 26 ; i++){
            if(mpu[i] != -1 && mpl[i] != -1){
                if(mpl[i] < mpu[i]) ans++; 
                else continue ; 
            }
        }
        return ans;
    }
};