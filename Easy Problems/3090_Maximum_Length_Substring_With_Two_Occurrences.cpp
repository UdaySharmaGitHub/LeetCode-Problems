/*
3090. Maximum Length Substring With Two Occurrences
Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.
Example 1:
Input: s = "bcbbbcba"
Output: 4
Explanation:
The folloing substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
Example 2:
Input: s = "aaaa"
Output: 2
Explanation:
The following substring has a length of 2 and contains at most two occurrences of each character: "aaaa".
 
Constraints:
2 <= s.length <= 100
s consists only of lowercase English letters.
*/
class Solution {
public:
    int maximumLengthSubstring(string s) {
        unordered_map<char,int> map;
        int res = 0,i=0;
        for(int j =0;j<s.size();j++){
            map[s[j]]++;
                while(map[s[j]]>2){
                    map[s[i]]--;
                    if(map[s[i]]==0)map.erase(s[i]);
                    i++;
                }
                res = max(res,j-i+1);
        }       
        return res;
    }
};