/*
2265. Count Nodes Equal to Average of Subtree
Given the root of a binary tree, return the number of nodes where the value of the node is equal to the average of the values in its subtree.

Note:

The average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
A subtree of root is a tree consisting of root and all of its descendants.
 

Example 1:


Input: root = [4,8,5,0,1,null,6]
Output: 5
Explanation: 
For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1 + 6) / 6 = 24 / 6 = 4.
For the node with value 5: The average of its subtree is (5 + 6) / 2 = 11 / 2 = 5.
For the node with value 0: The average of its subtree is 0 / 1 = 0.
For the node with value 1: The average of its subtree is 1 / 1 = 1.
For the node with value 6: The average of its subtree is 6 / 1 = 6.
Example 2:


Input: root = [1]
Output: 1
Explanation: For the node with value 1: The average of its subtree is 1 / 1 = 1.
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 1000
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
/*
    OPTIMIZED APPROACH:
*/
class Solution {
public:
    vector<int> find(TreeNode *root, int &ans)
    {
        if(root == NULL) {
            return {0, 0};
        }

        vector<int> l = find(root->left, ans);
        vector<int> r = find(root->right, ans);

        int sum = root->val + l[0] + r[0];
        int n = 1 + l[1] + r[1];

        if(sum / n == root->val) {
            ans = ans + 1;
        }

        return {root->val + l[0] + r[0], 1 + l[1] + r[1]};
    }
    int averageOfSubtree(TreeNode* root) {
        
        int ans = 0;
        find(root, ans);
        return ans;
    }
};
/*
    Lengthy Approach
*/
class Solution {
public:
int sumSubTreefunction(TreeNode* root,int&subTreeSize){
    if(!root) return 0;
    subTreeSize++;
    return (root->val+sumSubTreefunction(root->left,subTreeSize)+sumSubTreefunction(root->right,subTreeSize));
}
    int averageOfSubtree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int res = 0 ;
        while(!q.empty()){
            int n =q.size();
            for(int i =0 ; i<n;i++){
                TreeNode* frontNode  =q.front();
                int subTreeSize = 0;
                int sumSubTree = sumSubTreefunction(frontNode,subTreeSize);
                // cout<<sumSubTree<<":"<<subTreeSize<<"="<<sumSubTree/subTreeSize<<endl;
                if(subTreeSize!=0 && ((sumSubTree/subTreeSize)==frontNode->val))res++;
                q.pop();
                if(frontNode->left) q.push(frontNode->left);
                if(frontNode->right) q.push(frontNode->right);
            }
        }
        return res;
    }
};