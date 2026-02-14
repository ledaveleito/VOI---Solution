#include <bits/stdc++.h>
#define pq priority_queue
#define int long long
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define MASK(i) (1ll<<(i))
#define next __next
#define pos __pos
using namespace std;
const double PI = acos(-1);
/*const int mod = ;

void sub (int&a, const int&b){
    a-=b;
    if (a<0) a+=mod;
}

void mul (int&a, const int&b){
    a = (1ll*a*b)%mod;
}

void add (int&a, const int&b){
    a+=b;
    if (a>=mod) a-=mod;
}*/

bool minimize (ll&a, const ll&b){
    if (a<=b) return false;
    a=b;
    return true;
}

bool maximize (ll&a, const ll&b){
    if (a>=b) return false;
    a=b;
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
const int limit = 2e5+5;

struct doan{
    int l, r, w;
};

doan range[limit];
int n, maxval;
vector <int> num;

int finds (int val){
    int l = 1, r = num.size()-1, ret = -1;
    while (l<=r){
        int mid = (l+r)/2;
        if (num[mid]>=val){
            ret = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return ret;
}

void compress(){
    for (int i=1; i<=n; i++){
        num.pb(range[i].l);
        num.pb(range[i].r);
    }
    num.pb(0);
    sort(num.begin(), num.end());
    for (int i=1; i<=n; i++){
        range[i].l = finds (range[i].l);
        range[i].r = finds (range[i].r);
        maximize (maxval, range[i].l);
        maximize (maxval, range[i].r);
    }
}

namespace sub1{
    void process(){
        int ret = 0;
        for (int i=1; i<=maxval; i++) for (int j=i; j<=maxval; j++){
            int cur = 0;
            for (int z=1; z<=n; z++){
                if (range[z].l>=i && range[z].r<=j) cur+=range[z].w;
            }
            maximize (ret, cur);
        }
        cout<<ret;
    }
}

namespace sub2{
    int ST[4*limit], lazy[4*limit];
    void push (int id, int l, int r){
        if (lazy[id]==0) return;
        ST[id]+=lazy[id];
        if (l<r){
            lazy[id*2]+=lazy[id];
            lazy[id*2+1]+=lazy[id];
        }
        lazy[id]=0;
    }
    //
    void update (int id, int l, int r, int lcon, int rcon, int val){
        push(id, l, r);
        if (l>rcon || r<lcon) return;
        if (l>=lcon && r<=rcon){
            lazy[id]+=val;
            push(id, l, r);
            return;
        }
        int mid = (l+r)/2;
        update (id*2, l, mid, lcon, rcon, val);
        update (id*2+1, mid+1, r, lcon, rcon, val);
        ST[id] = max (ST[id*2], ST[id*2+1]);
    }
    //
    bool comp (const doan&a, const doan&b){
        return a.l<b.l;
    }
    //
    void process(){
        for (int i=1; i<=n; i++) update(1, 1, maxval, range[i].r, maxval, range[i].w);
        int ret = ST[1];
        sort(range+1, range+n+1, comp);
        int cur = 1;
        for (int i=1; i<=maxval; i++){
            while (cur<=n && range[cur].l<=i){
                update (1, 1, maxval, range[cur].r, maxval, -range[cur].w);
                cur++;
            }
            maximize (ret, ST[1]);
        }
        cout<<ret;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("sseq.inp", "r", stdin);
    freopen("sseq.out", "w", stdout);
    cin>>n;
    for (int i=1; i<=n; i++) cin>>range[i].l>>range[i].r>>range[i].w;
    compress();
    sub2::process();
}
