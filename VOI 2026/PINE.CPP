#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int LIM = 200000 + 5;
const string name = "pine";

/* ================= Fenwick ================= */

struct FenwickLL {
    ll bit[LIM];
    FenwickLL() { memset(bit, 0, sizeof(bit)); }

    inline void update(int i, ll v){
        for (++i; i < LIM; i += i & -i)
            bit[i] += v;
    }
    inline ll get(int i){
        ll s = 0;
        for (++i; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }
    inline ll get(int l, int r){
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }
};

struct FenwickInt {
    int bit[LIM];
    FenwickInt() { memset(bit, 0, sizeof(bit)); }

    inline void update(int i, int v){
        for (++i; i < LIM; i += i & -i)
            bit[i] += v;
    }
    inline int get(int i){
        int s = 0;
        for (++i; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }
    inline int get(int l, int r){
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }
};

FenwickLL sumBIT;
FenwickInt cntBIT;

/* ================= Tree & HLD ================= */

int n, q;
int A[LIM];
vector<int> adj[LIM];

int sz[LIM], par[LIM], depth[LIM];
int head[LIM], inchain[LIM];
int dshld[LIM], poshld[LIM];
int numchain = 0, numhld = 0;

/* ================= Segment Tree ================= */

int maxi[4 * LIM];

inline void pull(int id){
    maxi[id] = (maxi[id<<1] > maxi[id<<1|1] ?
                maxi[id<<1] : maxi[id<<1|1]);
}

/* ================= DFS ================= */

void dfs(int u, int p){
    sz[u] = 1;
    par[u] = p;
    for (int v : adj[u]){
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void heavize(int u, int p){
    inchain[u] = numchain;
    dshld[++numhld] = u;
    poshld[u] = numhld;

    int heavy = 0;
    for (int v : adj[u]){
        if (v == p) continue;
        if (!heavy || sz[v] > sz[heavy])
            heavy = v;
    }

    if (heavy)
        heavize(heavy, u);

    for (int v : adj[u]){
        if (v == p || v == heavy) continue;
        head[++numchain] = v;
        heavize(v, u);
    }
}

/* ================= Segment Tree ================= */

void build(int id, int l, int r){
    if (l == r){
        maxi[id] = A[dshld[l]];
        sumBIT.update(maxi[id], maxi[id]);
        cntBIT.update(maxi[id], 1);
        return;
    }
    int mid = (l + r) >> 1;
    build(id<<1, l, mid);
    build(id<<1|1, mid+1, r);
    pull(id);
}

void updateSeg(int id, int l, int r, int ql, int qr, int mod){
    if (l > qr || r < ql || maxi[id] < mod) return;

    if (l == r){
        int old = maxi[id];
        sumBIT.update(old, -old);
        cntBIT.update(old, -1);

        maxi[id] = old % mod;

        sumBIT.update(maxi[id], maxi[id]);
        cntBIT.update(maxi[id], 1);
        return;
    }

    int mid = (l + r) >> 1;
    updateSeg(id<<1, l, mid, ql, qr, mod);
    updateSeg(id<<1|1, mid+1, r, ql, qr, mod);
    pull(id);
}

/* ================= Query helpers ================= */

inline void updatePath(int u, int v, int w){
    if (u > v) swap(u, v);
    updateSeg(1, 1, n, u, v, w);
}

ll getans(int mod){
    ll ret = 0;
    for (int st = 0; st < LIM; st += mod){
        int en = st + mod - 1;
        if (en >= LIM) en = LIM - 1;
        ll s = sumBIT.get(st, en);
        ll c = cntBIT.get(st, en);
        ret += s - c * st;
    }
    return ret;
}

ll query(int turn, int u, int v, int w){
    while (inchain[u] != inchain[v]){
        if (inchain[u] > inchain[v]){
            updatePath(poshld[head[inchain[u]]], poshld[u], w);
            u = par[head[inchain[u]]];
        } else {
            updatePath(poshld[head[inchain[v]]], poshld[v], w);
            v = par[head[inchain[v]]];
        }
    }
    updatePath(poshld[u], poshld[v], w);
    return getans(turn);
}

/* ================= Main ================= */

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (fopen((name + ".inp").c_str(), "r")){
        freopen((name + ".inp").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];

    for (int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    depth[1] = 0;
    dfs(1, 0);
    head[++numchain] = 1;
    heavize(1, 0);
    build(1, 1, n);

    for (int i = 1; i <= q; i++){
        int u, v, w;
        cin >> u >> v >> w;
        cout << query(i, u, v, w) << '\n';
    }
    return 0;
}
