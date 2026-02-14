#include <bits/stdc++.h>
#define int long long
using namespace std;
const int limit=2e3+5;

struct datas{
    int val,l,r;
};

bool comparater1 (datas a, datas b){
    return a.val<b.val;
}

bool comparater2 (datas a, datas b){
    if (a.l<b.l) return true;
    else if (a.l==b.l) return a.r>b.r;
    return false;
}

int n,d,A[limit],cnt=0,posi[limit*limit],len=0,res=0;
datas F[limit*limit];

void input(){
    cin>>n>>d;
    for (int i=1; i<=n; i++) cin>>A[i];
}

void process(){
    sort(A+1,A+n+1);
    for (int i=1; i<=n; i++)
        for (int j=i+1; j<=n; j++)
            F[++cnt]={A[i]+A[j],i,j};
    sort (F+1, F+cnt+1, comparater1);
    posi[++len]=1;
    for (int i=2; i<=cnt; i++)
        if (F[i].val!=F[i-1].val) posi[++len]=i;
    posi[++len]=cnt+1;
    for (int i=1; i<=len-d-1; i++){
        vector <datas> tmp;
        for (int j=posi[i]; j<posi[i+d+1]; j++)
            tmp.push_back(F[j]);
        sort(tmp.begin(), tmp.end(), comparater2);
        datas cur=tmp[0];
        int restmp=1;
        for (int i=1; i<tmp.size(); i++){
            if (tmp[i].l==cur.l) continue;
            if (tmp[i].r<cur.r){
                restmp++;
                cur=tmp[i];
            }
        }
        res=max(res,restmp);
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("PAIR.INP", "r", stdin);
    freopen("PAIR.OUT", "w", stdout);
    input();
    process();
    cout<<res;
}
