/*
3505. Minimum Operations to Make Elements Within K Subarrays Equal
You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):
Increase or decrease any element of nums by 1.
Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, where all elements within each subarray are equal

Example 1:
Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
Output: 8
Explanation:

Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.

Example 2:
Input: nums = [9,-2,-2,-2,1,5], x = 2, k = 2
Output: 3
Explanation:
Use 3 operations to subtract 3 from nums[4]. The resulting array is [9, -2, -2, -2, -2, 5].
Now, all elements within each subarray [-2, -2] (from indices 1 to 2) and [-2, -2] (from indices 3 to 4) are equal. Since 3 operations were used, 3 is the output.
 

Constraints:
2 <= nums.length <= 105
-106 <= nums[i] <= 106
2 <= x <= nums.length
1 <= k <= 15
2 <= k * x <= nums.length
*/
class Window {
    multiset<int> s;
    multiset<int>::iterator mid;  // the (h+1)-th smallest: everything before it is the low half
    long long low, total;
    int odd;

public:
    Window(vector<int>::const_iterator first, vector<int>::const_iterator last)
        : s(first, last), odd(s.size() & 1) {
        mid = next(s.begin(), s.size() / 2);
        low = accumulate(s.begin(), mid, 0LL);
        total = accumulate(s.begin(), s.end(), 0LL);
    }

    long long cost() const {  // larger half minus smaller half
        return total - 2 * low - odd * *mid;
    }

    long long slide(int out, int in) {
        s.insert(in);
        if (in < *mid)  // in joins the low half and pushes its largest up
            low += in - *--mid;
        if (out < *mid) {  // out leaves the low half: mid moves down into it
            low += *mid++ - out;
            s.erase(s.find(out));
        } else if (out == *mid) {
            mid = s.erase(mid);
        } else {
            s.erase(s.find(out));
        }
        total += in - out;
        return cost();
    }
};

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        Window win(nums.begin(), nums.begin() + x);
        vector<long long> cost{win.cost()};
        for (int i = x; i < n; ++i)
            cost.push_back(win.slide(nums[i - x], nums[i]));

        vector<long long> best(n + 1);  // best[i]: min ops for the windows placed so far inside nums[0..i)
        for (int j = 0; j < k; ++j) {
            vector<long long> layer(n + 1, LLONG_MAX / 2);
            for (int i = x; i <= n; ++i)
                layer[i] = min(layer[i - 1], best[i - x] + cost[i - x]);
            best = move(layer);
        }
        return best[n];
    }
};