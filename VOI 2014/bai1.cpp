#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int limit=3e5+5, inf=1e9+5;

int n,a,b,res=inf,sa[limit],sb[limit];
pii A[limit];

int bin_search (int val, int l, int r, int d[limit]){
    int res=-1;
    while (l<=r){
        int mid=(l+r)/2;
        if (d[mid]>val) r=mid-1;
        else{
            res=mid;
            l=mid+1;
        }
    }
    return res;
}

void input(){
    cin>>n>>a>>b;
    for (int i=1; i<=n; i++){
        int d,stat;
        cin>>d>>stat;
        A[i]={d,stat};
    }
}

void process(){
    sort(A+1,A+n+1);
    for (int i=1; i<=n; i++){
        sa[i]=sa[i-1];
        sb[i]=sb[i-1];
        if (A[i].se==1) sa[i]++;
        else sb[i]++;
    }
    for (int i=1; i<=n; i++){
        if (sa[i]<a || sb[i]<b) continue;
        int vtra=bin_search(sa[i]-a,1,i,sa);
        int vtrb=bin_search(sb[i]-b,1,i,sb);
        vtra=min(vtra,vtrb);
        res=min(res,A[i].fi-A[vtra+1].fi);
    }
    if (res==inf) cout<<"-1";
    else cout<<res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    input();
    process();
}
