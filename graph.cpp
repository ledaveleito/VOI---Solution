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
const int mod = 1e9+7;

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
}

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

int dp[2005][2005], A[2005], n, b;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("graph.inp", "r", stdin);
    freopen("graph.out", "w", stdout);
    cin>>n>>b;
    for (int i=1; i<=n; i++) cin>>A[i];
    dp[n+1][0] = 1;
    for (int i=n+1; i>=1; i--){
        for (int j=0; j<=n; j++){
            if (dp[i][j]==0) continue;
//            cerr<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
            if (A[i]==0){
                if (j<=b) add (dp[i-1][j], dp[i][j]);
            }
            else if (A[i]>0){
                if (A[i]<=i-1 && A[i]+j<=b) add (dp[i-1][j+1], dp[i][j]);
            }
            else{
                // th1: cur = 0
                if (j<=b) add (dp[i-1][j], dp[i][j]);
                // th2: cur>0
                if (min(b-j, i-1)>0){
                    add (dp[i-1][j+1], dp[i][j]*min(b-j, i-1)%mod);
                }
            }
        }
    }
    int ret = 0;
    //for (int i=0; i<=n; i++) cerr<<dp[0][i]<<" ";
    for (int i=0; i<=n; i++) add(ret, dp[0][i]);
    cout<<ret;
}
