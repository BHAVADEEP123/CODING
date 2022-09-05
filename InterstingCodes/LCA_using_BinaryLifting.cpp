#include<bits/stdc++.h>
#include <iostream>
using namespace std;
int LOG;
void dfs(int u,int par,vector<vector<int>>&up,vector<int>&depth,vector<int>adj[]){
    up[u][0]=par;
    if(u!=par){
        depth[u]=depth[par]+1;
        //cout<<depth[u]<<endl;
    }

    for(int i=1;i<=LOG;i++){
        up[u][i]=up[up[u][i-1]][i-1];
    }
    for(auto ch:adj[u]){
        if(ch!=par){
            dfs(ch,u,up,depth,adj);
        }
    }

}
int lca(int u,int v,vector<vector<int>>&up,vector<int>&depth){
    if(depth[u]>depth[v]){
        swap(u,v);
    }
    int k = depth[v]-depth[u];
    for(int j=LOG;j>=0;j--){
        if(k&(1<<j)){
            v = up[v][j];
        }
    }
    if(u==v){
        return u;
    }
    for(int j = LOG;j>=0;j--){
        if(up[u][j]!=up[v][j]){
            u=up[u][j];
            v=up[v][j];
        }

    }
    return up[u][0];
}
int main(){
    int n;
    cin>>n;
    vector<int>adj[n];
    int e;
    cin>>e;
    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LOG = ceil(log2(n));
    vector<int>depth(n);
    depth[0]=0;
    vector<vector<int>>up(n,vector<int>(LOG+1));

    dfs(0,0,up,depth,adj);
    for(int i=0;i<depth.size();i++){
        cout<<depth[i]<<endl;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=LOG;j++){
            cout<<up[i][j]<<' ';
        }
        cout<<endl;
    }
    int u,v;
    cin>>u>>v;
    cout<<lca(u,v,up,depth)<<endl;


}

