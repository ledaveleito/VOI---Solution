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
const string name = "INTERNET";
const int lim = 1e5, limit = lim+5, inf = 1e18;

struct point{
    int x, y, id;
};

point edge[8*limit], ori[limit], p[limit];
int n, s, k, m;
int par[limit], sz[limit];
pii BIT[limit], base;
vector <int> ds;

bool comp (const point&a, const point&b){
    if (a.x-a.y!=b.x-b.y) return a.x-a.y>b.x-b.y;
    return a.y>b.y;
}

bool comp2 (const point&a, const point&b){
    return a.id<b.id;
}

void update (int id, pii val){
    id = n-id+1;
    while (id<=n){
        minimize (BIT[id], val);
        id+=(id&(-id));
    }
}

pii get (int id){
    id = n-id+1;
    pii ret = base;
    while (id>0){
        minimize (ret, BIT[id]);
        id&=id-1;
    }
    return ret;
}

void ini(){
    ds.clear();
    ds.pb(-inf);
    for (int i=1; i<=n; i++){
        ds.pb(p[i].y);
    }
    sort (ds.begin(), ds.end());
    ds.erase (unique (ds.begin(), ds.end()), ds.end());
    base = {inf, inf};
    for (int i=1; i<=n; i++) BIT[i] = base;
}

int dist (int u, int v){
    return abs(ori[u].x-ori[v].x)+abs(ori[u].y-ori[v].y);
}

void find_edges(){
    sort (p+1, p+n+1, comp);
    ini();
    for (int i=1; i<=n; i++){
        int x = p[i].x, y = p[i].y;
        int pos = lower_bound(ds.begin(), ds.end(), p[i].y)-ds.begin();
        int id = p[i].id;
        pii tmp = get (pos);
        if (tmp.fi!=inf){
            edge[++m] = {id, tmp.se, dist(tmp.se, id)};
        }
        update (pos, make_pair(x+y, id)) ;
    }
}

int finds (int u){
    if (u==par[u]) return u;
    return par[u] = finds (par[u]);
}

bool unions (int u, int v){
    int a = finds (u), b = finds (v);
    if (a==b) return false;
    if (sz[a]<sz[b]) swap(a, b);
    sz[a]+=sz[b];
    par[b] = a;
    return true;
}

void process(){
    for (int i=1; i<=n; i++){
        p[i].x = ori[i].x;
        p[i].y = ori[i].y;
        p[i].id = i;
    }
    for (int turn=1; turn<=2; turn++){ // flip hinh
        for (int ro=1; ro<=4; ro++){ // xoay 90
            find_edges();
            for (int i=1; i<=n; i++){
                int x = p[i].x, y = p[i].y;
                p[i].x = x-y;
                p[i].y = x+y;
            }
        }
        for (int i=1; i<=n; i++) p[i].y*=-1;
    }
    sort (edge+1, edge+m+1, comp2);
    for (int i=1; i<=n; i++){
        par[i] = i;
        sz[i] = 1;
    }
    int ret = 0;
    for (int i=1; i<=m; i++){
        int u = edge[i].x, v = edge[i].y, w = edge[i].id;
        if (w<=s){
            unions (u, v);
        }
        else{
            if (k>0 && unions(u, v)){
                k--;
                ret+=w;
            }
        }
    }
    cout<<ret;
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
    cin>>n>>s>>k;
    for (int i=1; i<=n; i++){
        cin>>ori[i].x>>ori[i].y;
    }
    process();
}
