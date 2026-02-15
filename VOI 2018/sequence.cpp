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
const string name = "sequence";
const int lim = 3e5, limit = lim+5;

vi add[limit];
vi sub[limit];
int n, A[limit];
multiset <int> ms;

void process(){
    //
    int ret = 0;
    for (int i=1; i<=n; i++){
        int val = A[i] - i;
        add[i].pb(val);
        ms.insert(val);
        int topval = (*ms.rbegin());
        if (topval>val){
            ret+=topval-val;
            sub[i].pb(topval);
            ms.erase(--ms.end());
            add[i].pb(val);
            ms.insert(val);
        }
    }
    //
    // gi (v) -> Ai = v
    // fi (v) -> Ai <=v
    // gi(v) = abs(Ai-v) + f[i-1](v)
    vector <int> ans;
    int cur = (*ms.rbegin());
    for (int i=n; i>=1; i--){
        ans.pb(cur+i);
        for (int x:sub[i]) ms.insert(x);
        for (int x:add[i]) ms.erase(ms.lower_bound(x));
        if (!ms.empty() && cur>(*ms.rbegin())){
            cur = (*ms.rbegin());
        }
    }
    reverse (ans.begin(), ans.end());
    cout<<ret<<"\n";
    for (int x:ans) cout<<x<<" ";
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
    //
    cin>>n;
    for (int i=1; i<=n; i++) cin>>A[i];
    process();
}
