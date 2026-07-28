/*
3517. Smallest Palindromic Rearrangement I
You are given a palindromic string s.
Return the lexicographically smallest palindromic permutation of s.
 
Example 1:
Input: s = "z"
Output: "z"
Explanation
A string of only one character is already the lexicographically smallest palindrome.
Example 2:
Input: s = "babab"
Output: "abbba"
Explanation:
Rearranging "babab" → "abbba" gives the smallest lexicographic palindrome.
Example 3:
Input: s = "daccad"
Output: "acddca"
Explanation

Rearranging "daccad" → "acddca" gives the smallest lexicographic palindrome.
 
Constraints:
1 <= s.length <= 105
s consists of lowercase English letters.
s is guaranteed to be palindromic.
*/
class Solution {
public:
    string smallestPalindrome(string s) {
     int mid = s.size()/2;
     if(s.size()<2) return s;
     vector<int> freq(26,0);
    for(int i =0 ; i<mid ;i++) freq[s[i]-'a']++;
    string str = "";
    for(int i=0;i<freq.size();i++){
        if(freq[i]>0){
            while(freq[i]){
                str+=('a'+i);
                freq[i]--;
            }
        }
    }
    string res = str;
    if(s.size()&1) res+=s[mid];
    reverse(str.begin(),str.end());
    res+=str;
    return res;
    }
};