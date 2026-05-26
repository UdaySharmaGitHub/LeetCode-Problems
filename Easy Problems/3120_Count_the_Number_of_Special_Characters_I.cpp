/*
3120. Count the Number of Special Characters I
You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
Return the number of special letters in word.

Example 1:
Input: word = "aaAbcBC"
Output: 3
Explanation:
The special characters in word are 'a', 'b', and 'c'.

Example 2:
Input: word = "abc"
Output: 0
Explanation:
No character in word appears in uppercase.

Example 3:
Input: word = "abBCab"
Output: 1
Explanation:
The only special character in word is 'b'.

Constraints:
1 <= word.length <= 50
word consists of only lowercase and uppercase English letters.
*/
/*
    APPROACH: Hashing
    Step:
    1. We will create two vectors, small and large, of size 26 to count the occurrences of lowercase and uppercase letters in the word, respectively.
    2. We will iterate through the characters in the word and update the counts in the small and large vectors accordingly.
    3. After counting the occurrences, we will iterate through the small and large vectors and count how many characters appear in both vectors (i.e., how many characters are special).
    4. Finally, we will return the count of special characters. 

    Time Complexity: O(N) - We need to iterate through the word once to count the occurrences and then iterate through the vectors to count special characters.
    Auxiliary Space: O(1) - We are using a constant amount of space for the small and large vectors, which have a fixed size of 26.
*/
class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> small(26,0) , large(26,0);
        for(char ch:word){
            if(ch>='a' && ch<='z') small[ch-'a']++;
            else if(ch>='A' && ch<='Z') large[ch-'A']++;
        }
        int count = 0;
        for(int i =0;i<26;i++){
            if(large[i] && small[i]) count++;
        }        
        return count ;
    }
};