#include <bits/stdc++.h>
//#define int long long
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
const string name = "";
const int lim = 5e4, limit = lim+5;

int n, q;
pii A[limit];
vector <int> inside[limit];

bool check (int maxi){
    priority_queue < int, vector<int>, greater<int> > qq;
    for (int i=1; i<=n; i++){
        for (int x:inside[i]){
            if (x>maxi) break;
            qq.push (A[x].se);
        }
        if (!qq.empty()){
            if (qq.top()<i) return false;
            qq.pop();
        }
    }
    return qq.empty();
}

void process(){
    //
    for (int i=1; i<=n; i++) inside[i].clear();
    for (int i=1; i<=q; i++) inside[A[i].fi].pb(i);
    //
    int left = 1, right = q, ret = q;
    while (left<=right){
        int mid = (left+right)/2;
        if (check(mid)){
            ret = mid;
            left = mid+1;
        }
        else right = mid-1;
    }
    cout<<ret<<"\n";
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
    int t;
    cin>>t;
    while (t--){
        cin>>n>>q;
        for (int i=1; i<=q; i++) cin>>A[i].fi>>A[i].se;
        process();
    }
}
