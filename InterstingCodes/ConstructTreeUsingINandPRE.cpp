#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int preindex = 0;
struct Node{
    int val;
    Node*left;
    Node*right;
    Node(int k){
        val=k;
        left=right=NULL;
    }
};
Node*construct(vector<int>&preorder,vector<int>&inorder,int s,int e){
    if(s>e)return NULL;
    Node*curr = new Node(preorder[preindex++]);
    int idx;
    for(int i=0;i<inorder.size();i++){
        if(curr->val==inorder[i]){
            idx=i;
            break;
        }
    }
    curr->left = construct(preorder,inorder,s,idx-1);
    curr->right = construct(preorder,inorder,idx+1,e);
    return curr;
}
int main(){
    int n;
    cin>>n;
    vector<int>preorder;
    vector<int>inorder;
    for(int i=0;i<n;i++){
        cin>>preorder[i];
    }
    for(int i=0;i<n;i++){
        cin>>inorder[i];
    }
    int s=0;
    int e = n-1;
    Node* root = construct(preorder,inorder,s,e);
}
