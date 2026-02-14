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

const int mod = 998244353;
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
const int lim = 1e5, limit = lim+5, inf = 1e9+5;

struct ele{
    int u, dist, cmin;
};

bool comp (const ele&a, const ele&b){
    return a.cmin<b.cmin;
}

vector <pii> adj[limit];
int n;

namespace chuan{
    int firet[limit];
    bool banned[limit];
    int numChild[limit], numBranch, sum0[limit], sum1[limit], sum2[limit];
    ele branch[limit];
    //
    void count_child (int u, int pre){
        numChild[u] = 1;
        for (pii x:adj[u]){
            int v = x.fi;
            if (v==pre || banned[v]) continue;
            count_child (v, u);
            numChild[u]+=numChild[v];
        }
    }
    //
    int find_centroid(int u, int pre, int aim){
        for (pii x:adj[u]){
            int v = x.fi;
            if (v==pre || banned[v] || numChild[v]<aim) continue;
            return find_centroid (v, u, aim);
        }
        return u;
    }
    //
    void dfs (int u, int pre, int dist, int cmin){
        branch[++numBranch] = {u, dist, cmin};
        for (pii x:adj[u]){
            int v = x.fi, w = x.se;
            if (v==pre || banned[v]) continue;
            dfs(v, u, dist+1, min(cmin, w));
        }
    }
    //
    void clusion( int kind){
        if (numBranch==1) return;
        sort(branch+1, branch+numBranch+1, comp);
        sum1[numBranch] = branch[numBranch].dist;
        sum2[numBranch] = 1ll*branch[numBranch].dist*branch[numBranch].dist%mod;
        for (int i=numBranch-1; i>=2; i--){
            sum1[i] = (sum1[i+1] + branch[i].dist)%mod;
            sum2[i] = (1ll*branch[i].dist*branch[i].dist+sum2[i+1])%mod;
        }
        for (int i=1; i<numBranch; i++){
            int u = branch[i].u, cmin = branch[i].cmin, dist = branch[i].dist;
            int sl = numBranch - i;
            int a = (1ll*dist*dist%mod*sl + sum2[i+1])%mod*cmin%mod;
            add (a, 2ll*cmin*dist%mod*sum1[i+1]%mod);
            if (kind==1) add (firet[u], a);
            else sub (firet[u], a);
        }
        for (int i=1; i<numBranch; i++){
            int cur = branch[i].cmin;
            sum0[i] = (sum0[i-1] + cur)%mod;
            mul (cur, branch[i].dist);
            sum1[i] = (sum1[i-1] + cur)%mod;
            mul (cur, branch[i].dist);
            sum2[i] = (sum2[i-1] + cur)%mod;
        }
        for (int i=2; i<=numBranch; i++){
            int u = branch[i].u, dist = branch[i].dist;
            int a = (1ll*sum0[i-1]*dist%mod*dist + sum2[i-1] + 2ll*sum1[i-1]*dist%mod)%mod;
            if (kind==1) add (firet[u], a);
            else sub (firet[u] , a);
        }
    }
    //
    void broke (int u){
        count_child(u, u);
        u = find_centroid(u, u, numChild[u]/2);
        banned [u] = true;
        //
        numBranch = 0;
        branch[++numBranch] = {u, 0, inf};
        for (pii x:adj[u]){
            int v = x.fi, w = x.se;
            if (banned[v]) continue;
            dfs(v, u, 1, w);
        }
        //
        clusion(1);
        //
        for (pii x:adj[u]){
            int v = x.fi, w = x.se;
            if (banned[v]) continue;
            numBranch = 0;
            dfs(v, u, 1, w);
            clusion(0);
        }
        //
        for (pii x:adj[u]){
            int v = x.fi;
            if (banned[v]) continue;
            broke(v);
        }
    }
    //
    void process(){
        broke (1);
        for (int i=1; i<=n; i++) cout<<firet[i]<<"\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    freopen ("netw.inp", "r", stdin);
    freopen ("netw.out", "w", stdout);
    cin>>n;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin>>u>>v>>w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    chuan::process();
}
