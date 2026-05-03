/*
2451. Odd String Difference
You are given an array of equal-length strings words. Assume that the length of each string is n.

Each string words[i] can be converted into a difference integer array difference[i] of length n - 1 where difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2. Note that the difference between two letters is the difference between their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1, and 'z' is 25.

For example, for the string "acb", the difference integer array is [2 - 0, 1 - 2] = [2, -1].
All the strings in words have the same difference integer array, except one. You should find that string.

Return the string in words that has different difference integer array.

 

Example 1:

Input: words = ["adc","wzy","abc"]
Output: "abc"
Explanation: 
- The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
- The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
- The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1]. 
The odd array out is [1, 1], so we return the corresponding string, "abc".
Example 2:

Input: words = ["aaa","bob","ccc","ddd"]
Output: "bob"
Explanation: All the integer arrays are [0, 0] except for "bob", which corresponds to [13, -13].
 

Constraints:

3 <= words.length <= 100
n == words[i].length
2 <= n <= 20
words[i] consists of lowercase English letters.
*/
/*
    OPTIMZIED APPROACH:
    1. Calculate the difference array for the first three strings and compare them.
    2. If one of the first three strings has a different difference array, return that string.
    3. If all three strings have the same difference array, store that difference array and compare it with the difference array of the remaining strings.
    4. If any string has a different difference array, return that string.
    5. If no string has a different difference array, return an empty string.
*/
class Solution {
public:
    string oddString(vector<string>& words) {
        const int m = words[0].size() - 1;
        vector<int> same(m , 0);
        for(int j = 0; j < m; ++j){
            int diff1 = words[0][j + 1] - words[0][j];
            int diff2 = words[1][j + 1] - words[1][j];
            int diff3 = words[2][j + 1] - words[2][j];
            if(diff1 != diff2 && diff1 != diff3) return words[0];
            if(diff2 != diff1 && diff2 != diff3) return words[1];
            if(diff3 != diff1 && diff3 != diff2) return words[2];
            same[j] = diff1;
        }
        for(int i = 3, n = words.size(); i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(words[i][j + 1] - words[i][j] != same[j]) return words[i];
            }
        }
        return "";
    }
};
/*
    APPRAOCH: Lengthy Approach
    1. Create a map to store the difference array and the corresponding strings.
    2. For each string in the input, calculate the difference array and store it in the map.
    3. Iterate through the map and find the difference array that has only one corresponding string. This will be the odd string out.
    4. Return the odd string.
*/
class Solution {
public:
    string oddString(vector<string>& words) {
        string res = "";
        map< vector<int>,vector<string>> map;
        for(string s:words){
            vector<int> diff;
            for(int i =0 ; i<s.size()-1;i++){
                diff.push_back(s[i+1]-s[i]);
            }
            map[diff].push_back(s);
        }
        for(auto i:map){
            vector<string> arr = i.second;
            if(arr.size()==1){ res =arr[0];break;}
        }
        return res;
    }
};