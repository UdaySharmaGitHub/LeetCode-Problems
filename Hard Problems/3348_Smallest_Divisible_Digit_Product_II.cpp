/*
3348. Smallest Divisible Digit Product II
You are given a string num which represents a positive integer, and an integer t.
A number is called zero-free if none of its digits are 0.
Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
 
Example 1:
Input: num = "1234", t = 256
Output: "1488"
Explanation:
The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
Example 2:
Input: num = "12355", t = 50
Output: "12355"
Explanation:
12355 is already zero-free and has the product of its digits divisible by 50, with the product of its digits equal to 150.
Example 3:
Input: num = "11111", t = 26
Output: "-1"
Explanation:
No number greater than 11111 has the product of its digits divisible by 26.


Constraints:

2 <= num.length <= 2 * 105
num consists only of digits in the range ['0', '9'].
num does not contain leading zeros.
1 <= t <= 1014
*/
class Solution {
public:
    vector<int> allowedPrimes = {2, 3, 5, 7};

    // optimization
    int contrib[10][4] = {
        {0,0,0,0},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},
        {0,0,1,0},{1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}
    };

    int maxE2, maxE3, maxE5, maxE7;
    vector<vector<vector<vector<int>>>> dp; // dp[e2][e3][e5][e7] = min digits

    void buildDP(int E2, int E3, int E5, int E7) {
        maxE2 = E2; maxE3 = E3; maxE5 = E5; maxE7 = E7;
        dp.assign(E2 + 1, vector<vector<vector<int>>>(
                  E3 + 1, vector<vector<int>>(
                  E5 + 1, vector<int>(E7 + 1, INT_MAX))));

        dp[0][0][0][0] = 0;

        // iterate in increasing order of total exponent sum so we prepare teh dependencies first
        for (int s = 1; s <= E2 + E3 + E5 + E7; s++) {
            for (int e2 = 0; e2 <= E2; e2++)
            for (int e3 = 0; e3 <= E3; e3++)
            for (int e5 = 0; e5 <= E5; e5++)
            for (int e7 = 0; e7 <= E7; e7++) {
                if (e2 + e3 + e5 + e7 != s) continue;
                int best = INT_MAX;
                for (int d = 2; d <= 9; d++) {
                    // can I add this digit
                    // What it is going to contribute?
                    // means if it's 8 -> it contributes 3 2's.
                    // if 6 -> 1-2 & 1-3.
                    // and so on.
                    int ne2 = max(0, e2 - contrib[d][0]);
                    int ne3 = max(0, e3 - contrib[d][1]);
                    int ne5 = max(0, e5 - contrib[d][2]);
                    int ne7 = max(0, e7 - contrib[d][3]);
                    if (dp[ne2][ne3][ne5][ne7] != INT_MAX)
                        best = min(best, 1 + dp[ne2][ne3][ne5][ne7]);
                }
                // update the memo here.
                dp[e2][e3][e5][e7] = best;
            }
        }
    }

    int minDigits(int e2, int e3, int e5, int e7) {
        return dp[min(e2, maxE2)][min(e3, maxE3)][min(e5, maxE5)][min(e7, maxE7)];
    }

    void applyDigit(vector<int>& freq, int d) {
        // remove the contribution
        freq[2] = max(0, freq[2] - contrib[d][0]);
        freq[3] = max(0, freq[3] - contrib[d][1]);
        freq[5] = max(0, freq[5] - contrib[d][2]);
        freq[7] = max(0, freq[7] - contrib[d][3]);
    }

    bool isReqMet(vector<int>& freq) {
        for (int p : allowedPrimes) if (freq[p] > 0) return false;
        return true;
    }

    // Smallest suffix of exactly length L satisfying freq. Caller must ensure feasibility.
    string greedyFill(vector<int> freq, int L) {
        string res;
        res.reserve(L);
        for (int pos = 0; pos < L; pos++) {
            int slotsAfter = L - pos - 1;
            for (int d = 1; d <= 9; d++) {
                // Save old values
                vector<int> nf = freq;
                applyDigit(nf, d);
                if (minDigits(nf[2], nf[3], nf[5], nf[7]) <= slotsAfter) {
                    freq = nf;
                    res.push_back('0' + d);
                    break;
                }
                // Backtrack (not needed here since nf is a local copy)
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        // number greate than num, and product of digits divisible by t.
        // one thing is 2, 3, 5, 7 should be prime factors of t because
        // if 11 or >= 11 comes then we can not get two digits whose
        // product is a prime number.

        vector<int> freqFull(10, 0);
        for (int p : allowedPrimes) {
            while (t % p == 0) { freqFull[p]++; t /= p; }
        }
        if (t > 1) return "-1"; // not possible.

        buildDP(freqFull[2], freqFull[3], freqFull[5], freqFull[7]);

        // Now we need a number which is greater than num,
        // and whose divisors are 2, 3, 5, 7 using occurences
        // of 2, 3, 5, 7 that we have.

        int len = num.size();
        bool hasZero = false;
        for (char c : num) if (c == '0') { hasZero = true; break; }

        // Case 1: num itself already works
        if (!hasZero) {
            vector<int> freq = freqFull;
            for (char c : num) applyDigit(freq, c - '0');
            if (isReqMet(freq)) return num;
        }

        // Precompute prefix freq (freq remaining BEFORE placing digit at position i)
        vector<vector<int>> prefixFreq(len + 1);
        prefixFreq[0] = freqFull;
        for (int i = 0; i < len; i++) {
            prefixFreq[i + 1] = prefixFreq[i];
            if (num[i] != '0') applyDigit(prefixFreq[i + 1], num[i] - '0');
        }

        int limit = hasZero ? (int)num.find('0') : len - 1;

        // build for length n
        // First we try to form for exact length length = n.
        // If not possible, just keep adding 1 to it until we get our answer.
        string answer;
        for (int pos = limit; pos >= 0 && answer.empty(); pos--) {
            vector<int>& freqBefore = prefixFreq[pos];
            int origDigit = num[pos] - '0';
            for (int d = origDigit + 1; d <= 9; d++) {
                vector<int> nf = freqBefore;
                applyDigit(nf, d);
                int slotsAfter = len - pos - 1;
                if (minDigits(nf[2], nf[3], nf[5], nf[7]) <= slotsAfter) {
                    answer = num.substr(0, pos) + char('0' + d) + greedyFill(nf, slotsAfter);
                    break;
                }
            }
        }

        if (!answer.empty()) return answer;

        // keep adding one's here as same length we didn't get any anser. 
        int totalNeeded = minDigits(freqFull[2], freqFull[3], freqFull[5], freqFull[7]);
        int L = max(len + 1, totalNeeded);
        return greedyFill(freqFull, L);
    }
};