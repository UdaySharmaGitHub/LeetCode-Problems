/*
3863. Minimum Operations to Sort a String
You are given a string s consisting of lowercase English letters.
In one operation, you can select any substring of s that is not the entire string and sort it in non-descending alphabetical order.
Return the minimum number of operations required to make s sorted in non-descending order. If it is not possible, return -1.
 
Example 1:
Input: s = "dog"
Output: 1
Explanation:​​​​​​​
Sort substring "og" to "go".
Now, s = "dgo", which is sorted in ascending order. Thus, the answer is 1.
Example 2:
Input: s = "card"
Output: 2
Explanation:
Sort substring "car" to "acr", so s = "acrd".
Sort substring "rd" to "dr", making s = "acdr", which is sorted in ascending order. Thus, the answer is 2.
Example 3:
Input: s = "gf"
Output: -1
Explanation:
It is impossible to sort s under the given constraints. Thus, the answer is -1.

Constraints:
1 <= s.length <= 105
s consists of only lowercase English letters.
*/
class Solution {
public:
    int minOperations(auto& s) {
        int n = s.length();
        char mn = s[0], mx = s[0];
        bool isSorted = 1;

        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) isSorted = 0;
            mn = min(mn, s[i]);
            mx = max(mx, s[i]);
        }

        if (isSorted) return 0;
        if (n == 2) return -1;
        if (s.front() == mn || s.back() == mx)
            return 1;

        for (int i = 1; i < n - 1; i++)
            if (s[i] == mn || s[i] == mx)
                return 2;

        return 3;
    }
};