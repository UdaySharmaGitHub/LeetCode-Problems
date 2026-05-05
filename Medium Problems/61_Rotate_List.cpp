/*
61. Rotate List
Given the head of a linked list, rotate the list to the right by k places.
Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
Example 2:
Input: head = [0,1,2], k = 4
Output: [2,0,1]
Constraints:
The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 109
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 /*
 
    APPROACH: 
    steps:
    1. find the length of the linked list and the tail node.
    2. connect the tail node to the head node to make it circular.
    3. find the new tail node which is (len-k%len)th node from the beginning and the new head node which is (len-k%len+1)th node
    4. break the circular connection by setting the next of the new tail node to null.
    5. return the new head node.

    Time Complexity: O(n) where n is the number of nodes in the linked list.
    Space Complexity: O(1) as we are using only constant extra space.
 */
class Solution {
private:
ListNode* FindNthNode(ListNode* head,int k){
    int i =1;
    while(head!=nullptr){
        if(i==k){
            return head;
        }
        i++;
        head=head->next;
    }
    return head;
}
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==nullptr || k ==0){
            return head;
        }
        int len = 1;
        ListNode* tail = head;
        while(tail->next!=nullptr){
            tail=tail->next;
            len++;
        }
        if(k%len==0) return head;
        tail->next = head;
        k%=len;
        ListNode* newEndNode = FindNthNode(head,len-k);
        head= newEndNode->next;
        newEndNode ->next=nullptr;
        return head;

    }
};