#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fi first
#define se second
#define vi vector <int>
#define pq priority_queue
#define MASK(i) (1ll<<(i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define x0 ___x0
#define y0 ___y0
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define pos pisosi
#define pb push_back
#define pf push_front
using namespace std;

//const int mod = ;
//void add (int &a, const int&b){
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
//    a*=b;
//    a%=mod;
//}

template<class X, class Y>
    bool minimize(X &x, const Y&y){
        if (x<=y) return false;
        else{
            x = y;
            return true;
        }
    }
template<class X, class Y>
    bool maximize (X &x, const Y&y){
        if (x>=y) return false;
        else{
            x = y;
            return true;
        }
    }

/////////////////////////////////////////////////////////////////////////////////

//// dang nhap ham
//#ifndef davele
//
//#endif // davele
//
//// chay thu ham main:
//
//#ifdef davele
//
//#endif // davele

////////////////////////////////////////////////////////////////////////////
//const int lim = , limit = , inf = ;
const string name = "post";
const long long inf = 8e18;
const int lim = 3e5, limit = lim+5;
const int BLOCKSIZE = 600 ;

mt19937_64 rng (chrono::high_resolution_clock::now().time_since_epoch().count());

int rand (int l, int r){
    return uniform_int_distribution <int> (l, r) (rng);
}

int c2n (int nn){
    return nn*(nn-1)/2;
}

struct tv{
    int l, r, id;
};

bool comp (const tv&a, const tv&b){
    int ia = a.l/BLOCKSIZE, ib = b.l/BLOCKSIZE;
    if (ia!=ib) return ia<ib;
    return a.r<b.r;
}

int n, q, A[limit];
tv query[limit];

namespace ban{
    vector <int> ds;
    int cnt[limit], ans[limit];
    vector <int> inside[limit];
    void compressa(){
        ds.clear();
        ds.pb(0);
        for (int i=1; i<=n; i++) ds.pb(A[i]);
        sort (ds.begin(), ds.end());
        ds.erase (unique (ds.begin(), ds.end()), ds.end());
//        for (int x:ds)  cerr<<x<<"  ";
//        cerr<<"\n";
        for (int i=0; i<=n; i++){
            A[i] = lower_bound (ds.begin(), ds.end(), A[i])-ds.begin()+1;
        }
    }
    void process(){
        compressa();
//        for (int i=1; i<=n; i++) cerr<<A[i]<<" ";
//        cerr<<"\n";
        for (int i=1; i<=n; i++){
            inside[A[i]].pb(i);
        }
        for (int i=1; i<=n; i++){
            shuffle(inside[i].begin(), inside[i].end(), rng);
        }
        for (int i=1; i<=n; i++){
            if (inside[i].empty()) continue;
            int sx = 0;
            for (int x:inside[i]){
                A[x] = rand (1, inf);
                sx^=A[x];
            }
            A[inside[i][0]]^=sx;
        }
//        for (int i=1; i<=n; i++) cerr<<A[i]<<" ";
//        cerr<<"\n";
        for (int i=1; i<=n; i++){
            A[i]^=A[i-1];
        }
//        for (int i=1; i<=n; i++) cerr<<A[i]<<" ";
//        cerr<<"\n";
        compressa();
//        for (int i=0; i<=n; i++) cerr<<A[i]<<" ";
//        cerr<<"\n";
        for (int i=1; i<=q; i++) query[i].l--;
        sort (query+1, query+q+1, comp);
        int le = query[1].l, ri = query[1].r;
        int ret = 0;
        for (int i=le; i<=ri; i++){
            ret-=c2n(cnt[A[i]]);
            cnt[A[i]]++;
            ret+=c2n(cnt[A[i]]);
        }
        ans[query[1].id] = ret;
        for (int i=2; i<=q; i++){
            int l = query[i].l, r = query[i].r, id = query[i].id;
            while (le>l){
                le--;
                int val = A[le];
                ret+=cnt[val];
                cnt[val]++;
            }
            while (le<l){
                int val = A[le];
                cnt[val]--;
                le++;
                ret-=cnt[val];
            }
            while (ri<r){
                ri++;
                int val = A[ri];
                ret+=cnt[val];
                cnt[val]++;
            }
            while (ri>r){
                int val = A[ri];
                cnt[val]--;
                ri--;
                ret-=cnt[val];
            }
            ans[id] = ret;
        }
        for (int i=1; i<=q; i++) cout<<ans[i]<<"\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    if (fopen((name+".inp").c_str(), "r")){
        freopen ((name+".inp").c_str(), "r", stdin);
        freopen ((name+".out").c_str(), "w", stdout);
    }
    cin>>n>>q;
    for (int i=1; i<=n; i++) cin>>A[i];
    for (int i=1; i<=q; i++) cin>>query[i].l>>query[i].r;
    for (int i=1; i<=q; i++) query[i].id = i;
    ban::process();
}
