/*
3464. Maximize the Distance Between Points on a Square
You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.
You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.
You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.
Return the maximum possible minimum Manhattan distance between the selected k points.
The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
Example 1:
Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
Output: 2
Explanation:
Select all four points.
Example 2:
Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4
Output: 1
Explanation:
Select the points (0, 0), (2, 0), (2, 2), and (2, 1).
Example 3:
Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5
Output: 1
Explanation:
Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).
Constraints:
1 <= side <= 109
4 <= points.length <= min(4 * side, 15 * 103)
points[i] == [xi, yi]
The input is generated such that:
points[i] lies on the boundary of the square.
All points[i] are unique.
4 <= k <= min(25, points.length)
*/
class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> res;
        for (auto& p : points) {
            int x = p[0], y = p[1];
            if (x == 0) res.push_back(y);
            else if (y == side) 
                res.push_back((long long)side + x);
            else if (x == side) 
                res.push_back((long long)side * 3 - y);
            else res.push_back((long long)side * 4 - x);
        }
        sort(res.begin(), res.end());

        auto check = [&](int n) {
            int m = res.size();
            vector<int> idx(k);
            long long curr = res[0];
            idx[0] = 0;
            for (int i = 1; i < k; i++) {
                auto it = lower_bound(res.begin(), res.end(), curr + n);
                if (it == res.end()) 
                    return false;
                idx[i] = distance(res.begin(), it);
                curr = *it;
            }
            if (res[idx[k - 1]] - res[0] <= (long long)side * 4 - n) 
                return true;

            for (idx[0] = 1; idx[0] < idx[1]; idx[0]++) {
                for (int j = 1; j < k; j++) {
                    while (idx[j] < m && res[idx[j]] < res[idx[j - 1]] + n) {
                        idx[j]++;
                    }
                    if (idx[j] == m) 
                        return false;
                }
                if (res[idx[k - 1]] - res[idx[0]] <= (long long)side * 4 - n) 
                    return true;
            }
            return false;
        };

        int left = 1;
        int right = (1LL * side * 4) / k + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) 
                left = mid;
            else right = mid;
        }
        return left;
    }
};