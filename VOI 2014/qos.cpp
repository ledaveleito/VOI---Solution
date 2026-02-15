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
const string name = "qos";
const int inf = 1e9+5;

struct ele{
    int u, diff, tot;
};

int n, m, t, k, cmin;
vector <pii> adj[123456], rev[123456];
int d[123456];
int dp[1234][123];
ele stat[123456];
int numstat;

bool comp (const ele&a, const ele&b){
    return a.tot<b.tot;
}

void dijkstra (){
    priority_queue < pii, vector<pii>, greater<pii> > q;
    q.push({0, t});
    for (int i=1; i<=n; i++) d[i] = inf;
    d[t] = 0;
    while (!q.empty()){
        pii tmp = q.top();
        q.pop();
        if (d[tmp.se]<tmp.fi) continue;
        for (pii x:rev[tmp.se]){
            if (minimize (d[x.fi], x.se+tmp.fi)){
                q.push({d[x.fi], x.fi});
            }
        }
    }
}

void add (int &a, const int &b){
    a+=b;
    minimize (a, inf);
}

void process(){
    dijkstra();
    for (int i=1; i<=n; i++){
        for (int j=0; j<=cmin; j++){
            stat[++numstat] = {i, j, d[i]+j};
        }
    }
    sort (stat+1, stat+numstat+1, comp);
    dp[t][0] = 1;
    for (int i=1; i<=numstat; i++){
        int u = stat[i].u, diff = stat[i].diff, tot = stat[i].tot;
        if (dp[u][diff]!=0){
//            cerr<<u<<" "<<diff<<" "<<dp[u][diff]<<"\n";
            for (pii x:rev[u]){
                int v = x.fi, w = x.se;
                if (tot+w<=d[v]+cmin){
                    add (dp[v][tot+w-d[v]], dp[u][diff]);
                }
            }
        }
    }
    //
    int tm = 0;
    for (int i=0; i<=cmin; i++) add (tm, dp[1][i]);
    if (tm<k){
        cout<<"-1";
        return;
    }
    vector <int> ret;
    ret.pb(1);
    int dist = 0;
    while (1){
        int last = ret.back();
        if (last==t && dist>d[1]) break;
        if (last==t && dist==d[1]){
            for (pii x:adj[last]){
                int v = x.fi, w = x.se;
                if (v==t && w==cmin){
                    ret.pb(v);
                    break;
                }
            }
            break;
        }
        for (pii x:adj[last]){
            int v = x.fi, w = x.se;
            if (dist+w+d[v]>d[1]+cmin) continue;
            int ovr = 0;
            for (int diff=0; diff<=cmin; diff++){
                if (dist+w+d[v]+diff<=d[1]+cmin){
                    add (ovr, dp[v][diff]);
                }
                else break;
            }
            if (ovr>=k){
                ret.pb(v);
                dist+=w;
                break;
            }
            else{
                k-=ovr;
            }
        }
    }
    cout<<ret.size()<<"\n";
    for (int x:ret) cout<<x<<" ";
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
    cin>>n>>m>>t>>k;
    cmin = inf;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        minimize (cmin, w);
        adj[u].pb({v, w});
        rev[v].pb({u, w});
    }
    for (int i=1; i<=n; i++) sort(adj[i].begin(), adj[i].end());
    process();
}
