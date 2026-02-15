#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int limit=1e3+5, inf=1e9+5;

struct edge{
    int v , c, f;
};

struct dinic{
    int n, work[limit], d[limit];
    vector <edge> e;
    vector <int> adj[limit];
    int s, t, maxflow;
    dinic (int _n, int _s, int _t){
        n=_n; s=_s; t=_t;
    }
    //
    void add_edge (int u, int v, int c){
        e.pb({v, c, 0});
        adj[u].pb(e.size()-1);
        e.pb({u, 0, 0});
        adj[v].pb(e.size()-1);
    }
    //
    bool bfs (){
        for (int i=1; i<=n; i++) d[i]=-1;
        d[s]=0;
        queue <int> q;
        q.push(s);
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (int id:adj[u]){
                int v = e[id].v;
                int c = e[id].c;
                int f = e[id].f;
                if (c>f && d[v]==-1){
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
        return d[t]!=-1;
    }
    //
    int dfs (int u, int flow){
        if (u==t) return flow;
        for (int &z=work[u]; z<adj[u].size(); z++){
            int id = adj[u][z];
            int v = e[id].v, c = e[id].c, f = e[id].f;
            if (c>f && d[v]==d[u]+1){
                int tmp = dfs (v, min(flow, c-f));
                if (tmp){
                    e[id].f+=tmp;
                    e[id^1].f-=tmp;
                    return tmp;
                }
            }
        }
        return 0;
    }
    //
    int max_flow(){
        maxflow=0;
        while (bfs()){
            for (int i=1; i<=n; i++) work[i]=0;
            while (int tmp=dfs(s, inf)){
                maxflow+=tmp;
            }
        }
        return maxflow;
    }
    //
};

int n, m, num[limit], low[limit];
int cnt, scc;
vector <int> g[limit];
vector <int> adj[limit];
int A[limit];
bool deleted[limit];
int thuoc[limit];
vector <int> avail[limit];
bool ok[limit][limit];
stack <int> st;

void dfs (int u){
    num[u]=low[u]=++cnt;
    st.push(u);
    for (int v:adj[u]){
        if (deleted[v]) continue;
        if (num[v]==0){
            dfs(v);
            low[u] = min (low[u], low[v]);
        }
        else{
            low[u] = min (low[u], num[v]);
        }
    }
    if (low[u]==num[u]){
        scc++;
        do{
            deleted[st.top()]=true;
            thuoc[st.top()]=scc;
            st.pop();
        } while (!deleted[u]);
    }
}

void dfs2 (int u){
    for (int v:g[u]){
        for (int x:avail[v]){
            if (avail[v].size()==0) dfs2(v);
            ok[u][x]=true;
            avail[u].pb(x);
        }
    }
    avail[u].pb(u);
}

void tarjan (){
    for (int i=1; i<=n; i++){
        if (num[i]==0) dfs(i);
    }
    //
    for (int i=1; i<=n; i++){
        for (int v:adj[i]){
            int a = thuoc[i], b = thuoc[v];
            if (a!=b) g[a].pb(b);
        }
    }
    //
    for (int i=1; i<=scc; i++){
        if (avail[i].size()==0) dfs2(i);
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    cin>>n;
    for (int i=1; i<=n; i++) cin>>A[i];
    cin>>m;
    for (int i=1; i<=m; i++){
        int u, v;
        cin>>u>>v;
        adj[u].pb(v);
    }
    //
    tarjan();
    int ret=0;
    //
    dinic f(n+2, n+1, n+2);
    for (int i=1; i<=n; i++){
        if (A[i]>0){
            f.add_edge(n+1, i, A[i]);
            ret+=A[i];
            for (int j=1; j<=n; j++){
                if (A[j]<0 && (thuoc[j]==thuoc[i] || ok[thuoc[i]][thuoc[j]])){
                    f.add_edge(i, j, inf);
                }
            }
        }
        else{
            f.add_edge(i, n+2, -A[i]);
        }
    }
    cout<<ret-f.max_flow();
}
