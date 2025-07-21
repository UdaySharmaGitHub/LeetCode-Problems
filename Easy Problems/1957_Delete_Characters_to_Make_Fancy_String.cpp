/*
1957. Delete Characters to Make Fancy String
A fancy string is a string where no three consecutive characters are equal.
Given a string s, delete the minimum possible number of characters from s to make it fancy.
Return the final string after the deletion. It can be shown that the answer will always be unique.
Example 1:
Input: s = "leeetcode"
Output: "leetcode"
Explanation:
Remove an 'e' from the first group of 'e's to create "leetcode".
No three consecutive characters are equal, so return "leetcode".
Example 2:
Input: s = "aaabaaaa"
Output: "aabaa"
Explanation:
Remove an 'a' from the first group of 'a's to create "aabaaaa".
Remove two 'a's from the second group of 'a's to create "aabaa".
No three consecutive characters are equal, so return "aabaa".
Example 3:
Input: s = "aab"
Output: "aab"
Explanation: No three consecutive characters are equal, so return "aab".
Constraints:
1 <= s.length <= 105
s consists only of lowercase English letters.
*/
//----------------------------------Using Counting--------------------------------------//
class Solution {
public:
    string makeFancyString(string s) {
        string ans = "";
        ans.push_back(s[0]);
        int n = s.size(),cnt = 1;
        for(int i=1;i<n;i++){
            if(s[i] == ans.back()){
                cnt++;
                if(cnt < 3)ans.push_back(s[i]);
            }
            else{
                cnt = 1;
                ans.push_back(s[i]);
            }
        }
        return ans;
    }
};
//----------------------------------Extra String-----------------------------------------------//
class Solution {
public:
    string makeFancyString(string s) {
        if(s.size()<3) return s;
        string str ="";
        int i =0 ;
        for(;i<s.size()-2;i++){
            if(s[i] == s[i+1] && s[i+1] == s[i+2] && s[i] == s[i+2]) continue;
            else str+=s[i];
        }
        for(;i<s.size();i++) str+=s[i];
        return str;
    }
};
