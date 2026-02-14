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
const string name = "wpro";
const int inf = 4e18;

int N, L1, L2, C, D;
int A[232143];

namespace sub567{
    int x0, y0, Gcd, dp[10005], sum[10005];
    void eeuclid (int a, int b, int&x, int &y){
        if (b==0){
            x = 1; y = 0; Gcd = a;
            return;
        }
        eeuclid (b, a%b, x, y);
        int yo = y, xo = x;
        x = yo; y = xo-(a/b)*yo;
    }
    int get (int c){
        if (c%Gcd!=0) return inf;
        int a = L1, b = L2;
        int mink = ceil (-1.0*x0*c/b);
        int maxk = floor (1.0*y0*c/a);
        if (mink>maxk) return inf;
        int tmp = min ((b-a)/Gcd*mink, (b-a)/Gcd*maxk);
        return tmp+c/Gcd*(x0+y0);
    }
    //
    int cost (int l, int r){
        int tmp = get(sum[r]-sum[l-1]);
        if (tmp==inf) return inf;
        return (tmp-1)*C+(r-l)*D;
    }
    //
    void process(){
        if (L1>L2) swap(L1, L2);
        eeuclid (L1, L2, x0, y0);
        //
        for (int i=1; i<=N; i++) sum[i] = sum[i-1]+A[i];
        //
        for (int i=1; i<=N; i++){
            dp[i] = inf;
            for (int j=0; j<i; j++) minimize (dp[i], dp[j]+cost(j+1, i));
        }
        cout<<dp[N];
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
    //
    cin>>N>>L1>>L2>>C>>D;
    for (int i=1; i<=N; i++) cin>>A[i];
    sub567::process();
}
