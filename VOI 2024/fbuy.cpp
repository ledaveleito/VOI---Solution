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

const int mod = 998244353, inv2 = 499122177;
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
const int lim = 2e5, limit = lim+5;

struct ele{
    int root, cnt, del, branch;
};

int numChild[limit], dp[limit], ds[limit], st[limit], en[limit];
vector <pii> in_root[limit];
vector <ele> in_tree[limit];
vector <int> adj[limit];
int numBranch;
bool banned[limit];
int up[limit][18], h[limit];
int sumTree[limit][21], delTree[limit][21];
int sumBranch[limit*2][21];
int len;
int n, q, k;
int cost[limit], color[limit], curret[limit];
pii query[limit];
int ori[limit];


namespace centroid{
    void countChild (int u, int pre){
        numChild[u] = 1;
        for (int v:adj[u]){
            if (v==pre || banned[v]) continue;
            countChild (v, u);
            numChild[u] += numChild[v];
        }
    }
    int findCentroid (int u, int pre, int aim){
        for (int v:adj[u]){
            if (v==pre || banned[v] || numChild[v]<=aim) continue;
            return findCentroid(v, u, aim);
        }
        return u;
    }
    void dfs (int u, int pre, int root){
        in_tree[u].pb({root, 0, 0, numBranch});
        in_root[root].pb({u, in_tree[u].size()-1});
        for (int v:adj[u]){
            if (v==pre || banned[v]) continue;
            dfs(v, u, root);
        }
    }
    void broke (int u){
        countChild (u, u);
        u = findCentroid (u, u, numChild[u]/2);
//        cerr<<u<<"\n";
        //
        banned[u] = true;
        //
        in_tree[u].pb({u, 0, 0, 0});
        in_root[u].pb({u, in_tree[u].size()-1});
        //
        for (int v:adj[u]){
            if (banned[v]) continue;
            numBranch++;
            dfs(v, u, u);
        }
        //
        for (int v:adj[u]){
            if (banned[v]) continue;
            broke(v);
        }
    }
}

void dfs (int u, int pre){
    ds[++len] = u;
    st[u] = len;
    numChild[u] = 1;
    for (int v:adj[u]){
        if (v==pre) continue;
        h[v] = h[u]+1;
        up[v][0] = u;
        for (int i=1; MASK(i)<=h[v]; i++){
            up[v][i] = up[ up[v][i-1] ][i-1];
        }
        dfs(v, u);
        numChild[u]+=numChild[v];
    }
    en[u] = len;
}

int get (int u, int root){
    if (st[root]<=st[u] && en[root]>=en[u]){
//        cerr<<u<<" "<<root<<"\n";
        for (int i=17; i>=0; i--){
            if (h[u]-MASK(i)>h[root]){
                u = up[u][i];
            }
        }
        return ori[u];
    }
    return n - ori[root];
}

void calc (int u, int pre){
    for (pii x:in_root[u]){
        int v = x.fi, where = x.se;
        in_tree[v][where].cnt = numChild[v];
        in_tree[v][where].del = get(v, u);
//        cerr<<"u "<<v<<" root "<<u<<" branch "<<get(v, u)<<"\n";
        int branch = in_tree[v][where].branch;
        add(sumBranch[branch][color[v]], numChild[v]);
        add(sumTree[u][color[v]], numChild[v]);
    }
    //
    dp[u] = 0;
    int treeSize = n;
    for (int v:adj[u]){
        add(dp[u], 1ll*numChild[v]*(treeSize-numChild[v])%mod);
        treeSize-=numChild[v];
    }
    //
    int oldu = numChild[u];
    for (int v:adj[u]){
        if (v==pre) continue;
        numChild[u]-=numChild[v];
        int oldv = numChild[v];
        numChild[v]+=numChild[u];
        calc(v, u);
        numChild[u] = oldu;
        numChild[v] = oldv;
    }
}

int getRet (){
    int ret = 0;
    for (int i=1; i<=k; i++) add (ret, 1ll*cost[i]*curret[i]%mod);
    return ret;
}

void process(){
    centroid::broke(1);
    dfs(1, 1);
    for (int i=1; i<=n; i++) ori[i] = numChild[i];
    calc(1, 1);
    //
    for (int i=1; i<=n; i++){
//        cerr<<i<<" "<<dp[i]<<"\n";
        int c = color[i];
        add (curret[c], dp[i]);
        for (int j = in_tree[i].size()-1; j>=0; j--){
            int root = in_tree[i][j].root;
            int cnt = in_tree[i][j].cnt;
            int del = in_tree[i][j].del, branch = in_tree[i][j].branch;
//            cerr<<"u "<<i<<" root "<<root<<" cnt "<<cnt<<" del "<<del<<" branch "<<branch<<" sumtree "<<sumTree[root][c]<<" sumbranch "<<sumBranch[branch][c]<<"\n";
            if (root==i){
                continue;
            }
            else{
                int tmp = sumTree[root][c];
                sub(tmp, sumBranch[branch][c]);
                if (c==color[root]){
                    sub(tmp, n);
                    add (curret[c], 1ll*tmp*cnt%mod);
                    int rem = n - del;
                    add (curret[c], 2ll*rem*cnt%mod);
                }
                else{
                    add (curret[c], 1ll*tmp*cnt%mod);
                }
                add (delTree[root][c], 1ll*(n-del)*cnt%mod);
//                sub
//                add (curret[c], 1ll*tmp*cnt%mod);
            }
        }
    }
//    for (int i=1; i<=k; i++) cerr<<i<<" "<<curret[i]<<"\n";
//    for (int i=1; i<=k; i++) mul(curret[i], inv2);
    cout<<getRet()<<"\n";
    for (int i=1; i<=q; i++){
        int u = query[i].fi, c = color[u];
        sub (curret[c], dp[u]);
        for (int j = in_tree[u].size()-1; j>=0; j--){
            int root = in_tree[u][j].root;
            int cnt = in_tree[u][j].cnt;
            int del = in_tree[u][j].del, branch = in_tree[u][j].branch;
//            cerr<<"u "<<u<<" root "<<root<<" cnt "<<cnt<<" del "<<del<<" branch "<<branch<<" sumtree "<<sumTree[root][c]<<" sumbranch "<<sumBranch[branch][c]<<"\n";
            if (root==u){
                sub (curret[c], 2ll*delTree[root][c]%mod);
            }
            else{
                int tmp = sumTree[root][c];
                sub(tmp, sumBranch[branch][c]);
                if (c==color[root]){
                    sub(tmp, n);
                    sub (curret[c], 2ll*tmp*cnt%mod);
                    int rem = n - del;
                    sub (curret[c], 2ll*rem*cnt%mod);
                }
                else{
                    sub (curret[c], 2ll*tmp*cnt%mod);
                }
                sub (delTree[root][c], 1ll*(n-del)*cnt%mod);
            }
            sub (sumTree[root][c], cnt);
            sub (sumBranch[branch][c], cnt);
        }
        //
        c = query[i].se;
        color[u] = c;
        add (curret[c], dp[u]);
        for (int j = in_tree[u].size()-1; j>=0; j--){
            int root = in_tree[u][j].root;
            int cnt = in_tree[u][j].cnt;
            int del = in_tree[u][j].del, branch = in_tree[u][j].branch;
            add (sumTree[root][c], cnt);
            add (sumBranch[branch][c], cnt);
//            cerr<<"u "<<u<<" root "<<root<<" cnt "<<cnt<<" del "<<del<<" branch "<<branch<<" sumtree "<<sumTree[root][c]<<" sumbranch "<<sumBranch[branch][c]<<"\n";
            if (root==u){
                add (curret[c], 2ll*delTree[root][c]%mod);
            }
            else{
                int tmp = sumTree[root][c];
                sub(tmp, sumBranch[branch][c]);
                if (c==color[root]){
                    sub(tmp, n);
                    add (curret[c], 2ll*tmp*cnt%mod);
                    int rem = n - del;
                    add (curret[c], 2ll*rem*cnt%mod);
                }
                else{
                    add (curret[c], 2ll*tmp*cnt%mod);
                }
                add (delTree[root][c], 1ll*(n-del)*cnt%mod);
            }
        }
        cout<<getRet()<<"\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    freopen ("fbuy.inp", "r", stdin);
    freopen ("fbuy.out", "w", stdout);
    cin>>n>>k>>q;
    for (int i=1; i<=n; i++) cin>>color[i];
    for (int i=1; i<=k; i++) cin>>cost[i];
    for (int i=1; i<n; i++){
        int u, v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i=1; i<=q; i++) cin>>query[i].fi>>query[i].se;
    process();
}
