#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
   void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
     /*
             vector<int> ans(m+n);
        int i=0,j=0,k=0;
        while(i<m && j<n){
           if(nums1[i] > nums2[j]){
               ans[k]=nums2[j];
               k++,j++;
           }
           else{
             ans[k]=nums1[i];
               k++,i++;
           }
        }
        while(i<m){
              ans[k]=nums1[i];
               k++,i++;
        }
              while(j<n){
              ans[k]=nums2[j];
               k++,j++;
        }
        for(auto x:ans){
            cout<<x<<"\t";
        }
     */
         int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
    }
    
};
int main(){
    Solution s;
    int n,m;
    cin>>m;
    vector<int> nums1(m);
    for(int i=0;i<m;i++){
        cin>>nums1[i];
    }
    cin>>n;
    vector<int> nums2(n);
    for(int i=0;i<n;i++){
        cin>>nums2[i];
    }
    s.merge(nums1,m,nums2,n);
}