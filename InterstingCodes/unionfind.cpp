#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int findx(vector<int>&par,int u){
    if(u==par[u])return u;
    return par[u]=findx(par,u);
}
void unionx(vector<int>&par,int u,int v,vector<int>&sz){
    int a = findx(par,u);
    int b = findx(par,v);
    if(a==b)cout<<"cycle Detected"<<endl;
    if(a!=b){
        if(sz[a]<sz[b]){
            swap(a,b);
        }
        par[b]=a;
        sz[a]+=sz[b];
    }
}
int main(){
    int n,k;
    cin>>n>>k;
    vector<int>par(n+1);
    vector<int>sz(n+1,1);
    for(int i=1;i<=n;i++){
        par[i]=i;
    }
    while(k--){
        int u,v;
        cin>>u>>v;
        unionx(par,u,v,sz);
    }

}