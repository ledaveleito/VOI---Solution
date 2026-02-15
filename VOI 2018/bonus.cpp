#include <bits/stdc++.h>
#define int long long
#define ll long long
#define double long double
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define MASK(i) (1ll<<(i))
#define next __next
#define pos __pos
#define x1 __x1
#define x2 __x2
#define y1 Y1
#define y2 __y2
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
const int limit = 505;

int n, k, r, p, x1[15], x2[15], y1[15], y2[15];
int sum[limit][limit], A[limit][limit];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
//    freopen(".inp", "r", stdin);
//    freopen(".out", "w", stdout);
    cin>>n>>k>>r>>p;
    for (int i=1; i<=n; i++) for (int j=1; j<=n; j++) cin>>A[i][j];
    for (int i=1; i<=n; i++) for (int j=1; j<=n; j++)
        sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+A[i][j];
    int ret=0;
    for (int tv=1; tv<=k; tv++){
        for (int j=1; j<=p; j++) cin>>x1[j]>>y1[j];
        for (int j=1; j<=p; j++){
            x2[j]=x1[j]+r-1;
            y2[j]=y1[j]+r-1;
        }
        //
        int ALLMASK = MASK(p)-1;
        int cur = 0;
        for (int i=1; i<=ALLMASK; i++){
            int xl = 1, yl = 1, xr = n, yr = n;
            for (int j=1; j<=p; j++) if (MASK(j-1)&i){
                xl = max (xl, x1[j]);
                yl = max (yl, y1[j]);
                xr = min (xr, x2[j]);
                yr = min (yr, y2[j]);
            }
            //cerr<<tv<<" "<<i<<"   "<<xl<<" "<<yl<<"  "<<xr<<" "<<yr<<"\n";
            if (xl>xr || yl>yr) continue;
            int val = sum[xr][yr]-sum[xl-1][yr]-sum[xr][yl-1]+sum[xl-1][yl-1];
            if (__builtin_popcount(i)&1) cur+=val;
            else cur-=val;
        }
        ret = max (ret, cur);
    }
    cout<<ret;
}
