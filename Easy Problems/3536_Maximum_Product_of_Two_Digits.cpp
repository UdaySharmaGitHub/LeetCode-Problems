/*
3536. Maximum Product of Two Digits
You are given a positive integer n.
Return the maximum product of any two digits in n.
Note: You may use the same digit twice if it appears more than once in n.

Example 1:
Input: n = 31
Output: 3
Explanation:
The digits of n are [3, 1].
The possible products of any two digits are: 3 * 1 = 3.
The maximum product is 3.
Example 2:
Input: n = 22
Output: 4
Explanation:
The digits of n are [2, 2].
The possible products of any two digits are: 2 * 2 = 4.
The maximum product is 4.
Example 3:
Input: n = 124
Output: 8
Explanation:
The digits of n are [1, 2, 4].
The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8.
The maximum product is 8.
Constraints:
10 <= n <= 109
*/
/*
    APPROACH:
    Step:
    1. Initialize two variables max1 and max2 to 0.
    2. While n is not equal to 0, do the following:
        a. Get the last digit of n by taking n modulo 10.
        b. If the last digit is greater than max1, update max2 to be max1 and max1 to be the last digit.
        c. Otherwise, update max2 to be the maximum of max2 and the last digit.
        d. Remove the last digit from n by dividing n by 10.
    3. Return the product of max1 and max2.

    Time Complexity: O(log n) - We are iterating through the digits of n, which takes logarithmic time.
    Space Complexity: O(1) - We are using a constant amount of space to store the two maximum digits.
*/
class Solution {
public:
    int maxProduct(int n) {
        int max1 = 0 , max2 = 0;
        while(n){
            int digit = n%10;
            if(max1<digit){max2 = max1;max1 = digit;}
            else max2 = max(max2,digit);
            n/=10;
        }
        return max1*max2;
    }
};