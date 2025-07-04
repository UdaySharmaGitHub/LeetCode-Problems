/*
3307. Find the K-th Character in String Game II
Alice and Bob are playing a game. Initially, Alice has a string word = "a".
You are given a positive integer k. You are also given an integer array operations, where operations[i] represents the type of the ith operation.
Now Bob will ask Alice to perform all operations in sequence:
If operations[i] == 0, append a copy of word to itself.
If operations[i] == 1, generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word. For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
Return the value of the kth character in word after performing all the operations.
Note that the character 'z' can be changed to 'a' in the second type of operation.
Example 1:
Input: k = 5, operations = [0,0,0]
Output: "a"
Explanation:
Initially, word == "a". Alice performs the three operations as follows:
Appends "a" to "a", word becomes "aa".
Appends "aa" to "aa", word becomes "aaaa".
Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".
Example 2:
Input: k = 10, operations = [0,1,0,1]
Output: "b"
Explanation:
Initially, word == "a". Alice performs the four operations as follows:
Appends "a" to "a", word becomes "aa".
Appends "bb" to "aa", word becomes "aabb".
Appends "aabb" to "aabb", word becomes "aabbaabb".
Appends "bbccbbcc" to "aabbaabb", word becomes "aabbaabbbbccbbcc".
Constraints:
1 <= k <= 1014
1 <= operations.length <= 100
operations[i] is either 0 or 1.
The input is generated such that word has at least k characters after all operations.
*/
/*
Bit Manupulation
    Time Complexity: (n)
    Space Complexity: (n)
*/
class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
     vector<long long> res;
     long long len =1;
     for(int i:operations){
        len*=2;
        res.push_back(len);
        if(len>=k) break;
     }   
     char ch ='a';
     for(int i =res.size()-1;i>=0;i--){
       long long half = res[i]/2;
        if(k>half){ k -=half;
         if (operations[i] == 1) {
                    // reversed shifting
                     ch = (ch - 'a' + 1) % 26 + 'a';
                }
        } 
     }
return ch;
    }
};
/*
String Time Limit Exceed TLE
    Time Complexity: (n*n)
    Space Complexity: (n)
*/
class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        string res ="a" ;
        int i  =0;
        while(res.size()<k){
            string temp ="";
            if(operations[i] ==0 ){
                temp =res;
                res+=temp;
            }else{
                for(char ch:res) temp += (ch-'a'+1)%25 +'a';
                res+=temp;
            }
            i++;
        }
        return res[k-1];
    }
};