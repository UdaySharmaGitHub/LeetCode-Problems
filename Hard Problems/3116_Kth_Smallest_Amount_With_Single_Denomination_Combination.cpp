/*
3116. Kth Smallest Amount With Single Denomination Combination
You are given an integer array coins representing coins of different denominations and an integer k.
You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.
Return the kth smallest amount that can be made using these coins
 
Example 1:
Input: coins = [3,6,9], k = 3
Output: 9
Explanation: The given coins can make the following amounts:
Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
All of the coins combined produce: 3, 6, 9, 12, 15, etc.
Example 2:
Input: coins = [5,2], k = 7
Output: 12
Explanation: The given coins can make the following amounts:
Coin 5 produces multiples of 5: 5, 10, 15, 20, etc.
Coin 2 produces multiples of 2: 2, 4, 6, 8, 10, 12, etc.
All of the coins combined produce: 2, 4, 5, 6, 8, 10, 12, 14, 15, etc.
Constraints:
1 <= coins.length <= 15
1 <= coins[i] <= 25
1 <= k <= 2 * 109
coins contains pairwise distinct integers.
 */
 class Solution {
public:
    using ll = long long;
    long long findKthSmallest(vector<int>& coins, int k) {
        ranges::sort(coins);
        vector<int> A;

        for (auto& c : coins)
            if (ranges::none_of(A, [&](int x) { return !(c % x); }))
                A.push_back(c);

        int n = A.size();

        auto check = [&](ll mid) {
            ll tot = 0;
            for (int i = 1; i <= n; i++) {
                int q = (1 << i) - 1;

                while (q < 1 << n) {
                    ll x = 1;
                    for (int j = 0; j < n; j++)
                        if ((q >> j) & 1)
                            x = lcm(x, A[j]);

                    tot += (mid / x) * (((i & 1) << 1) - 1);

                    int c = q & -q;
                    int r = q + c;
                    q = (((r ^ q) >> 2) / c) | r;
                }
            }
            return tot >= k;
        };

        ll low = k, high = 1ll * A[0] * k;
        return *ranges::lower_bound(views::iota(low, high + 1), true, {},
                                    [&](ll mid) { return check(mid); });
    }
};