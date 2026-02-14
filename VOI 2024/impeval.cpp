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
const string name = "impeval";
const int lim = 1e5, limit = lim+5, inf = 1e18;

struct canh{
    int u, v, w;
};

int n, m, q;
canh edge[limit];
vector <pii> adj[limit];
pii query[limit];


namespace sub1{
    int d1[limit], d2[limit];
    void proc(int U, int V, int W){
        for (int i=1; i<=n; i++) d1[i] = inf;
        priority_queue < pii, vector<pii>, greater<pii> > q;
        q.push({0, 1});
        d1[1] = 0;
        while (!q.empty()){
            pii tmp = q.top(); q.pop();
            if (d1[tmp.se]<tmp.fi) continue;
            for (pii x:adj[tmp.se]){
                if (minimize(d1[x.fi], tmp.fi+x.se)){
                    q.push({d1[x.fi], x.fi});
                }
            }
            if (tmp.se==U && minimize(d1[V], tmp.fi+W)){
                q.push({d1[V], V});
            }
            if (tmp.se==V && minimize(d1[U], tmp.fi+W)){
                q.push({d1[U], U});
            }
        }
        for (int i=1; i<=n; i++) d2[i] = inf;
        q.push({0, 2});
        d2[2] = 0;
        while (!q.empty()){
            pii tmp = q.top(); q.pop();
            if (d2[tmp.se]<tmp.fi) continue;
            for (pii x:adj[tmp.se]){
                if (minimize(d2[x.fi], tmp.fi+x.se)){
                    q.push({d2[x.fi], x.fi});
                }
            }
            if (tmp.se==U && minimize(d2[V], tmp.fi+W)){
                q.push({d2[V], V});
            }
            if (tmp.se==V && minimize(d2[U], tmp.fi+W)){
                q.push({d2[U], U});
            }
        }
        int ret = 0;
        for (int  i=1; i<=n; i++) if (d1[i]<=d1[U] && d2[i]<=d2[U]) ret++;
        cout<<ret<<" ";
        ret = 0;
        for (int i=1; i<=n; i++) if (d1[i]<=d1[V] && d2[i]<=d2[V]) ret++;
        cout<<ret<<"\n";
    }
    void process(){
        for (int i=1; i<=q; i++){
            int id = query[i].fi, neww = query[i].se;
            proc(edge[id].u, edge[id].v, neww);
        }
    }
}

struct ele{
    int u, w1, w2, ori;
};

bool comp (const ele&a, const ele&b){
    if (a.w1!=b.w1) return a.w1<b.w1;
    if (a.w2!=b.w2) return a.w2<b.w2;
    return  a.ori<b.ori;
}

namespace sub5{
    int BIT[limit];
    int d1[limit], d2[limit];
    ele ds[3*limit];
    int ans[limit][2];
    vector <int> nen;
    int lennen, lends;
    void update (int id, int val){
        while (id<=lennen){
            BIT[id]+=val;
            id+=(id&(-id));
        }
    }
    int get (int id){
        int ret = 0;
        while (id>0){
            ret+=BIT[id];
            id&=id-1;
        }
        return ret;
    }
    void dijkstra(){
        for (int i=1; i<=n; i++) d1[i] = inf;
        priority_queue < pii, vector<pii>, greater<pii> > q;
        q.push({0, 1});
        d1[1] = 0;
        while (!q.empty()){
            pii tmp = q.top(); q.pop();
            if (d1[tmp.se]<tmp.fi) continue;
            for (pii x:adj[tmp.se]){
                if (minimize(d1[x.fi], tmp.fi+x.se)){
                    q.push({d1[x.fi], x.fi});
                }
            }
        }
        for (int i=1; i<=n; i++) d2[i] = inf;
        q.push({0, 2});
        d2[2] = 0;
        while (!q.empty()){
            pii tmp = q.top(); q.pop();
            if (d2[tmp.se]<tmp.fi) continue;
            for (pii x:adj[tmp.se]){
                if (minimize(d2[x.fi], tmp.fi+x.se)){
                    q.push({d2[x.fi], x.fi});
                }
            }
        }
    }
    //
    int finds (int val){
        int l = 1, r = lennen, ret;
        while (l<=r){
            int mid = (l+r)/2;
            if (nen[mid]>=val){
                ret = mid;
                r = mid-1;
            }
            else l = mid+1;
        }
        return ret;
    }
    //
    void compressd2(){
        nen.pb(-1);
        sort(nen.begin(), nen.end());
        //
        nen.erase(unique(nen.begin(), nen.end()), nen.end());
//        for (int x:nen) cerr<<x<<" ";
//        cerr<<"\n";
        lennen = nen.size()-1;
    }
    //
    void process(){
        dijkstra();
        //
        for (int i=1; i<=n; i++){
            nen.pb(d2[i]);
            ds[++lends] = {i, d1[i], d2[i], 0};
        }
        for (int i=1; i<=q; i++){
            int id = query[i].fi,nw = query[i].se;
            int u = edge[id].u, v = edge[id].v;
            nen.pb(min(d2[u], d2[v]+nw));
            nen.pb(min(d2[v], d2[u]+nw));
            ds[++lends] = {i, min(d1[u], d1[v]+nw), min(d2[u], d2[v]+nw), 1};
            ds[++lends] = {i, min(d1[v], d1[u]+nw), min(d2[v], d2[u]+nw), 2};
        }
        compressd2();
        sort(ds+1, ds+lends+1, comp);
//        for (int i=1; i<=lends; i++) cerr<<ds[i].u<<" "<<ds[i].w1<<" "<<ds[i].w2<<" "<<ds[i].ori<<"\n";
//        //
        for (int i=1; i<=lends; i++){
//            cerr<<ds[i].w2<<" "<<finds(ds[i].w2)<<"\n";
            if (ds[i].ori==0){
                update(finds(ds[i].w2), 1);
            }
            else{
                ans[ds[i].u][ds[i].ori] = get(finds(ds[i].w2));
            }
        }
        for (int i=1; i<=q; i++){
            int id = query[i].fi,nw = query[i].se;
            int u = edge[id].u, v = edge[id].v;
            if (!(min(d1[u], d1[v]+nw)==d1[u] && min(d2[u], d2[v]+nw)==d2[u])) ans[i][1]++;
            if (!(min(d1[v], d1[u]+nw)==d1[v] && min(d2[v], d2[u]+nw)==d2[v])) ans[i][2]++;
            cout<<ans[i][1]<<" "<<ans[i][2]<<"\n";
        }
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
    cin>>n>>m>>q;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        edge[i] = {u, v, w};
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    //
    for (int i=1; i<=q; i++){
        cin>>query[i].fi>>query[i].se;
    }
    sub5::process();
}
