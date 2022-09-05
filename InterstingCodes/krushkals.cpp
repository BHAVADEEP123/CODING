#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int findx(vector<int>&par,int u){
    if(u==par[u])return u;
    return par[u]=findx(par,par[u]);
}
bool unionx(vector<int>&par,vector<int>&sz,int u,int v){
    u = findx(par,u);
    v = findx(par,v);
    if(u==v)return false;
    else{
        if(sz[u]<sz[v]){
            swap(u,v);
        }
        par[v]=u;
        sz[u]+=sz[v];
    }
    return true;
}
int main(){
    int n,k;
    cin>>n>>k;
    vector<vector<int>>v;
    vector<int>sz(n+1,1);
    vector<int>par(n+1);
    for(int i=1;i<=n;i++){
        par[i]=i;
    }
    for(int i=0;i<k;i++){
        vector<int>row;
        int t;
        cin>>t;
        row.push_back(t);
        cin>>t;
        row.push_back(t);
        cin>>t;
        row.push_back(t);
        v.push_back(row);

    }
    sort(v.begin(),v.end());
    int sum = 0;
    for(int i=0;i<k;i++){
        if(unionx(par,sz,v[i][1],v[i][2]))sum+=v[i][0];

    }
    cout<<sum<<endl;

}
