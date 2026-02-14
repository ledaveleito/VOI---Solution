#include "bits/stdc++.h"
#define int long long
#define pii pair<int, int>
#define fi first
#define se second
#define vi vector<int>
#define pb push_back
#define y0 ___y0
#define y1 ___y1
#define y2 ___y2
#define next fdsfsdfjs
#define prev fasdfasd
#define tm tetsdg
#define have ___have
#define norm ___norm
#define MASK(i) (1ll<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define pq priority_queue
using namespace std;

//const int mod = ;
//void add (int&a, const int&b){
//    a+=b;
//    if (a>=mod) a-=mod;
//}
//
//void sub (int&a, const int&b){
//    a-=b;
//    if (a<0) a+=mod;
//}
//
//void mul (int&a, const int&b){
//    a = 1ll*a*b%mod;
//}

template <class X, class Y>
    bool maximize (X&x, const Y&y){
        if (x>=y) return false;
        x = y;
        return true;
    }

template <class X, class Y>
    bool minimize (X&x, const Y&y){
        if (x<=y) return false;
        x = y;
        return true;
    }
/////////////////////////////////////////////////////////////////////////////////
const int lim = 2e5, limit = lim+5;

int n, q;
int A[limit], query[limit];
vector <int> ds;

void compress(){
    ds.pb(-1);
    for (int i=1; i<=n; i++) ds.pb(A[i]);
    sort (ds.begin(), ds.end());
    ds.erase (unique (ds.begin(), ds.end()), ds.end());
    for (int i=1; i<=n; i++){
        A[i] = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin();
    }
}

namespace sub3{
    int cnt[limit];
    bool check(){
        if (q==1) return true;
        return false;
    }
    int calc (int l, int r){
        if (l>r) return 0;
        for (int i=1; i<=n; i++) cnt[i] = 0;
        for (int i=l; i<=r; i++) cnt[A[i]]++;
        int ret = 1;
        for (int i=l; i<=r; i++){
            int val = A[i];
            cnt[val]--;
            ret += (r-i)-cnt[val];
        }
        return ret;
    }
    void process(){
        compress();
        cout<<max(calc(1, query[1]-1), calc(query[1]+1, n));
    }
}

namespace sub2{
    bool comp (const vi&a, const vi&b){
        for (int i=0; i<(int)a.size(); i++){
            if (a[i]<b[i]){
                return true;
            }
            else if (a[i]>b[i]) return false;
        }
        return false;
    }
    bool operator == (const vi&a, const vi&b){
        for (int i=0; i<(int)a.size(); i++){
            if (a[i]!=b[i]) return false;
        }
        return true;
    }
    int calc (int l, int r){
        if (l>r) return 0;
        vector < vector <int> > vv;
        for (int s = l; s<=r; s++){
            for (int e = s; e<=r; e++){
                for (int d = 1; s+d-1<e-d+1; d++) swap(A[s+d-1], A[e-d+1]);
                vector <int> tm;
                for (int i=1; i<=n; i++) tm.pb(A[i]);
                vv.pb(tm);
                for (int d = 1; s+d-1<e-d+1; d++) swap(A[s+d-1], A[e-d+1]);
            }
        }
        sort (vv.begin(), vv.end());
        int ret = 1;
        for (int i=1; i<(int)vv.size(); i++){
            if (!(vv[i]==vv[i-1])) ret++;
        }
        return ret;
    }
    void process(){
        cout<<max(calc(1, query[1]-1), calc(query[1]+1, n));
    }
}

namespace sub4{
    int par[limit];
    bool banned[limit];
    int sz[limit];
    multiset <int> existing;
    int ans[limit];
    int finret[limit];
    map <int, int> mp[limit];
    int finds (int u){
        if (u==par[u]) return u;
        return par[u] = finds (par[u]);
    }
    bool unions (int u, int v){
        int a = finds (u), b = finds (v);
        if (a==b) return false;
        if (sz[a]<sz[b]) swap(a, b);
        par[b] = a;
//        cerr<<u<<" "<<v<<"\n";
        existing.erase (existing.lower_bound(ans[b]));
        existing.erase (existing.lower_bound(ans[a]));
//        cerr<<u<<" "<<v<<"\n";
        ans[a] += (sz[a]+sz[b])*(sz[a]+sz[b]-1)/2 - sz[a]*(sz[a]-1)/2;
        sz[a]+=sz[b];
        for (pii x:mp[b]){
            int key = x.fi, val = x.se;
            int old = mp[a][key];
            ans[a] += old*(old-1)/2;
            mp[a][key]+=val;
            int tmp = old+val;
            ans[a] -=tmp*(tmp-1)/2;
        }
//        cerr<<ans[a]<<" "<<sz[a]<<"\n";
        mp[b].clear();
        existing.insert(ans[a]);
        return true;
    }
    void process(){
//        cerr<<"ok\n";
        for (int i=1; i<=q; i++){
            banned[query[i]] = true;
        }
        for (int i=1; i<=n; i++){
            if (!banned[i]){
                sz[i] = 1;
                par[i] = i;
                mp[i][A[i]]=1;
                ans[i] = 1;
                existing.insert(1);
                if (i>1 && !banned[i-1]) unions (i, i-1);
            }
        }
//        cerr<<existing.size()<<"\n";
//        cerr<<"ok\n";
        for (int i=q; i>=1; i--){
            finret[i] = (*(existing.rbegin()));
//            cerr<<i<<"\n";
            int where = query[i];
            banned[where] = false;
            sz[where] = 1;
            par[where] = where;
            mp[where][A[where]]++;
            ans[where] = 1;
            existing.insert(1);
//            cerr<<i<<"\n";
//            cerr<<where<<"\n";
            if (where>1 && !banned[where-1]) unions (where, where-1);
            if (where<n && !banned[where+1]) unions (where, where+1);
//            cerr<<i<<"\n";
        }
        for (int i=1; i<=q; i++) cout<<finret[i]<<"\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    freopen("TET.INP", "r", stdin);
    freopen("TET.OUT", "w", stdout);
    cin>>n>>q;
    for (int i=1; i<=n; i++) cin>>A[i];
    for (int i=1; i<=q; i++) cin>>query[i];
    if (q==1) sub3::process();
    else sub4::process();
}
