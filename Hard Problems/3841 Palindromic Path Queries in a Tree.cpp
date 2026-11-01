/*
3841. Palindromic Path Queries in a Tree
You are given an undirected tree with n nodes labeled 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an undirected edge between nodes ui and vi.

You are also given a string s of length n consisting of lowercase English letters, where s[i] represents the character assigned to node i.

You are also given a string array queries, where each queries[i] is either:

"update ui c": Change the character at node ui to c. Formally, update s[ui] = c.
"query ui vi": Determine whether the string formed by the characters on the unique path from ui to vi (inclusive) can be rearranged into a palindrome.
Return a boolean array answer, where answer[j] is true if the jth query of type "query ui vi"​​​​​​​ can be rearranged into a palindrome, and false otherwise.

 

Example 1:

Input: n = 3, edges = [[0,1],[1,2]], s = "aac", queries = ["query 0 2","update 1 b","query 0 2"]

Output: [true,false]

Explanation:

"query 0 2": Path 0 → 1 → 2 gives "aac", which can be rearranged to form "aca", a palindrome. Thus, answer[0] = true.
"update 1 b": Update node 1 to 'b', now s = "abc".
"query 0 2": Path characters are "abc", which cannot be rearranged to form a palindrome. Thus, answer[1] = false.
Thus, answer = [true, false].

Example 2:

Input: n = 4, edges = [[0,1],[0,2],[0,3]], s = "abca", queries = ["query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"]

Output: [false,false,true]

Explanation:

"query 1 2": Path 1 → 0 → 2 gives "bac", which cannot be rearranged to form a palindrome. Thus, answer[0] = false.
"update 0 b": Update node 0 to 'b', now s = "bbca".
"query 2 3": Path 2 → 0 → 3 gives "cba", which cannot be rearranged to form a palindrome. Thus, answer[1] = false.
"update 3 a": Update node 3 to 'a', s = "bbca".
"query 1 3": Path 1 → 0 → 3 gives "bba", which can be rearranged to form "bab", a palindrome. Thus, answer[2] = true.
Thus, answer = [false, false, true].

 

Constraints:

1 <= n == s.length <= 5 * 104
edges.length == n - 1
edges[i] = [ui, vi]
0 <= ui, vi <= n - 1
s consists of lowercase English letters.
The input is generated such that edges represents a valid tree.
1 <= queries.length <= 5 * 104​​​​​​​
queries[i] = "update ui c" or
queries[i] = "query ui vi"
0 <= ui, vi <= n - 1
c is a lowercase English letter.
*/
struct Tree {  // Euler tour: the subtree of x is tin[x] .. tout[x] - 1; LCA by a sparse table over the DFS order
    vector<int> parent, tin, tout, order;  // the root is its own parent; order: the nodes in DFS order
    vector<vector<int>> first;  // first[k][i]: the earliest parent among order[i .. i + 2^k - 1]

    Tree(int n, vector<vector<int>>& edges) : parent(n), tin(n), tout(n) {
        vector<int> head(n + 1), adj(2 * n);  // the neighbors of x are adj[head[x] .. head[x + 1] - 1]
        for (auto& e : edges) head[e[0] + 1]++, head[e[1] + 1]++;
        partial_sum(head.begin(), head.end(), head.begin());
        vector<int> pos(head.begin(), head.end() - 1);
        for (auto& e : edges) adj[pos[e[0]]++] = e[1], adj[pos[e[1]]++] = e[0];

        vector<int> stack = {0};
        while (!stack.empty()) {  // DFS without recursion; ~x marks the moment x's subtree is done
            int x = stack.back();
            stack.pop_back();
            if (x < 0) {
                tout[~x] = order.size();
                continue;
            }
            tin[x] = order.size();
            order.push_back(x);
            stack.push_back(~x);
            for (int i = head[x]; i < head[x + 1]; i++)
                if (int y = adj[i]; y != parent[x]) {
                    parent[y] = x;
                    stack.push_back(y);
                }
        }

        first.emplace_back(n);
        for (int i = 0; i < n; i++) first[0][i] = tin[parent[order[i]]];
        for (int k = 1; 1 << k <= n; k++) {
            first.emplace_back(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) <= n; i++) first[k][i] = min(first[k - 1][i], first[k - 1][i + (1 << (k - 1))]);
        }
    }

    int lca(int u, int v) {  // the parent that comes first in DFS order among the nodes after u up to v
        if (u == v) return u;
        auto [l, r] = minmax(tin[u], tin[v]);
        int k = bit_width(unsigned(r - l)) - 1;
        return order[min(first[k][l + 1], first[k][r - (1 << k) + 1])];
    }
};

struct RootPaths {  // paths[x]: XOR of the letter bits from the root down to x
    Tree& tree;
    vector<int> start, fenwick;  // the masks for the initial letters, and a Fenwick tree over the Euler tour with the changes since the start

    RootPaths(Tree& tree, vector<int>& bit) : tree(tree), start(bit), fenwick(bit.size() + 1) {
        for (int x : tree.order)  // a parent comes before its children in DFS order
            if (x != tree.parent[x]) start[x] ^= start[tree.parent[x]];
    }

    void flip(int x, int d) {  // XOR d into the root path of every node in x's subtree
        for (int i : {tree.tin[x] + 1, tree.tout[x] + 1})  // d starts at x's subtree and cancels out after it
            for (; i < (int)fenwick.size(); i += i & -i) fenwick[i] ^= d;
    }

    int operator[](int x) {
        int mask = start[x];
        for (int i = tree.tin[x] + 1; i > 0; i -= i & -i) mask ^= fenwick[i];
        return mask;
    }
};

class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        Tree tree(n, edges);
        vector<int> bit(n);  // bit[x]: the bit of x's letter
        for (int x = 0; x < n; x++) bit[x] = 1 << (s[x] - 'a');
        RootPaths paths(tree, bit);

        vector<bool> ans;
        for (auto& q : queries) {
            if (q[0] == 'u') {  // "update x c"
                int x = number(q, 7), newBit = 1 << (q.back() - 'a');
                paths.flip(x, bit[x] ^ newBit);  // the new letter changes the root path of every node in x's subtree
                bit[x] = newBit;
            } else {  // "query u v"
                int u = number(q, 6), v = number(q, q.rfind(' ') + 1);
                int mask = paths[u] ^ paths[v] ^ bit[tree.lca(u, v)];  // the LCA cancels out in paths[u] ^ paths[v], so add it back
                ans.push_back(popcount(unsigned(mask)) <= 1);  // at most one letter is odd
            }
        }
        return ans;
    }

private:
    static int number(const string& q, int i) {  // the number that starts at q[i]
        int x = 0;
        for (; i < (int)q.size() && isdigit(q[i]); i++) x = x * 10 + (q[i] - '0');
        return x;
    }
};