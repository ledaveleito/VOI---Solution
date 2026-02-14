#include <bits/stdc++.h>
#define ll long long
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

const int mod = 1e9+7;
void add (int &a, const int&b){
    a+=b;
    if (a>=mod) a-=mod;
}

void sub (int&a, const int&b){
    a-=b;
    if (a<0) a+=mod;
}

void mul (int&a, const int&b){
    a = 1ll*a*b%mod;
}

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
const int lim = 1e5, limit = lim+5;

namespace lehmer{
    // s(v, p) so cac so (<=v) la so nguyen to / co cac uoc nguyen to
    // LON HON p
    // s(v, p) = s(v, p-1)
    // <=>
    // a. p not prime
    // b. p*p>v (so dau tien co cac uoc nguyen to >p)

    // others : s(v, p) = s(v, p-1) - ( s(v/p, p-1) - s(p-1, p-1) )
    // tru di cac so co dang p * r (r gom cac so nguyen to >=p)

    // a(1)...a(sqrt) <=> s(i, p)
    // b(1)...b(sqrt) <=> s(n/i, p)
    vector <int> get (int n){
        ll BLOCK = sqrt(n);
        vector <ll> a(BLOCK+5, 0), b(BLOCK+5, 0);
        for (ll i=1; i<=BLOCK; i++){
            // tinh toan voi p = 1
            a[i] = i-1;
            b[i] = n/i - 1;
        }
        vector <int> ret;
        ret.pb(b[1]);
        for (ll p=2; p<=BLOCK; p++){
            // Ta can tinh s(n, sqrt(n)) vi den day la toan
            // cac so nguyen to roi
            if (a[p] == a[p-1]){
                continue;
                // s(p, p-1) = s(p-1, p-1)
                // => p khong phai la so nguyen to
                // => s(i, p) (1<=i<=n) khong thai doi (a)
            }
            // Theo (b), p*p <= v = n/i
            // <=> n/i >= p*p
            // <=> i<= n/(p*p)
            ll p2 = p*p;
            ll maxI = min(n/p2, BLOCK);
            for (ll i = 1; i<=maxI; i++){
                ll tmp = i*p;
                if (tmp<=BLOCK) b[i] -= b[tmp] - a[p-1];
                else b[i] -= a[n/tmp] - a[p-1];
            }
            for (ll i = BLOCK; i>=p2; i--){
                a[i] -= a[i/p] - a[p-1];
            }
            ret.pb(b[1]);
        }
        return ret;
    }
}

vector <int> operator - (const vector <int>&a, const vector<int>&b){
    vector <int> ret;
    for (int i=0; i<=30; i++){
//            cerr<<a[i]<<" "<<b[i]<<"\n";
        ret.pb(a[i]-b[i]);
    }
    return ret;
}
//
vector <int> operator + (const vector <int>&a, const vector<int>&b){
    vector <int> ret;
    for (int i=0; i<=30; i++) ret.pb(a[i]+b[i]);
    return ret;
}

vector <int> only (int n){
    vector <int> ret;
    for (int i=0; i<=30; i++){
        ret.pb(n&1);
        n>>=1;
    }
    return ret;
}

namespace dpdigit{
    int dp[50][2];
    vector <int> digit;
    int get (int pos, bool tight, bool ison, int cur){
        if (pos==-1){
            return ison;
        }
        if (!tight && dp[pos][ison]!=-1) return dp[pos][ison];
        //
        int bound = (tight) ? digit[pos] : 1;
        int ret = get(pos-1, (bound==0) ? tight : false, ison, cur);
        if (bound==1) ret += get(pos-1, tight, (ison || (cur==pos)), cur);
        if (!tight) dp[pos][ison] = ret;
        return ret;
    }
    //
    vector <int> cnt(int n){
        digit.clear();
        digit = only(n);
//        for (int x:digit) cerr<<x<<" ";
//        cerr<<"\n";
        vector <int> ret;
        for (int i=0; i<=30; i++){
            memset(dp, -1, sizeof(dp));
            ret.pb(get(30, true, false, i));
        }
        return ret;
    }
    //
    vector <int> get_range (int l, int r){
        return cnt(r) - cnt(l) + only(l);
    }
}

int n, m;
int uoc[limit];

namespace sub1{
    vector <int> A[10005];
    bool vis[10005];
    void process(){
        for (int i=1; i<=n; i++) A[i].resize(m+5, 0);
        for (int i=1; i<=n; i++) for (int j=1; j<=m; j++){
            for (int z=1; z<=n+m; z++) vis[z] = false;
            for (int z=1; z<i; z++) if (__gcd(i, z)==1){
                vis[A[z][j]] = true;
            }
            for (int z=1; z<j; z++) if (__gcd(j, z)==1){
                vis[A[i][z]] = true;
            }
            for (int z=1; z<=n+m; z++) if (!vis[z]){
                A[i][j] = z;
                break;
            }
        }
        int ret = 0;
        for (int i=1; i<=n; i++){
            for (int j=1; j<=m; j++){
                add (ret, A[i][j]);
//                cerr<<A[i][j]<<" ";
            }
//            cerr<<"\n";
        }
        cout<<ret%mod;
    }
}

ll get_prefix (ll num){
    return num*(num+1)/2;
}

ll get_sum (ll l, ll r){
    return get_prefix(r) - get_prefix(l-1);
}

bool is_prime (int num){
    return (uoc[num]==0);
}

namespace sub2{
    void process(){
        vector <int> cnt = lehmer::get(m);
        int ret = 1;
        int ranks = 1;
        for (int i=0; i+1<(int)cnt.size(); i++){
            ranks++;
            add (ret, 1ll*(cnt[i]-cnt[i+1]+1)*ranks%mod);
        }
//        for (int x:cnt) cerr<<x<<" ";
//        cerr<<"\n";
        add (ret, get_sum(ranks+1, cnt.back()+1)%mod);
        cout<<ret;
    }
}

namespace sub4{
    //
    vector <int> oned (int d){
        vector <int> cnt = lehmer::get(d);
        vector <int> ans(31, 0 );
        int ret = 1;
        int ranks = 1;
        for (int i=0; i+1<(int)cnt.size(); i++){
            int tmp = cnt[i] - cnt[i+1] +1;
            for (int j=0; j<=30; j++) if (MASK(j)&ranks){
                ans[j] += tmp;
            }
            ranks++;
        }
        ans = ans + dpdigit::get_range(ranks, cnt.back());
        return ans;
    }
    //
    void process(){
        vector <int> c = oned(m);
        vector <int> r = oned(n);
        int ret = 1ll*n*m%mod;
        for (int i=0; i<=30; i++){
            int cur = (1ll*c[i]*(n-r[i])%mod + 1ll*(m-c[i])*r[i]%mod)%mod;
            add (ret, 1ll*cur*MASK(i)%mod);
        }
        cout<<ret;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // uoc[0] = uoc[1] = 1;
    // for (int i=2; i*i<=lim; i++){
    //     if (uoc[i]==0) for (int j=i*i; j<=lim; j+=i) uoc[j] = i;
    // }
    //
    freopen ("matrix.inp", "r", stdin);
    freopen ("matrix.out", "w", stdout);
    cin>>n>>m;
    sub4::process();
//    if (n==1) sub2::process();
//    else sub1::process();
}
