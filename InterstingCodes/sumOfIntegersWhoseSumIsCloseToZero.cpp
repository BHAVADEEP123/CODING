#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int diffMax = INT_MAX;
    int s=0,e=n-1;
    int anss=s,enss=e;
    while(s<e){
        if(abs(a[s]+a[e])<diffMax){
            diffMax=abs(a[s]+a[e]);
            anss=s;
            enss=e;

        }
        if(abs(a[s])>abs(a[e])){
            s++;
        }
        else{
            e--;
        }

    }
    cout<<anss<<' '<<enss<<endl;
}
