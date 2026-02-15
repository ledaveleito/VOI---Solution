#include <bits/stdc++.h>
#define int long long
using namespace std;
const int limit=1e5+5;

struct edge{
    int u, v, id;
};

int par[limit], sz[limit];
edge canha[limit], canhb[limit];
int t, n, m;
int costa[limit], costb[limit];
int lena, lenb;

void make_set (){
    for (int i=1; i<=n; i++){
        par[i] = i;
        sz[i] = 1;
    }
}

int finds (int u){
    if (u==par[u]) return u;
    return par[u] = finds (par[u]);
}

bool unions (int u, int v){
    int a=finds(u), b=finds(v);
    if (a==b) return false;
    if (sz[a]>sz[b]) swap(a, b);
    par[b]=a;
    sz[a]+=sz[b];
    return true;
}

void process(){
    make_set();
    for (int i=1; i<=lena; i++) unions(canha[i].u, canha[i].v);
    vector <int> dsb;
    int dem=0;
    for (int i=1; i<=lenb; i++){
        if (unions(canhb[i].u, canhb[i].v)){
            dsb.push_back(i);
        }
    }
    //
    int ans = costb[dsb.size()] + costa[n-1-dsb.size()];
    int cur = dsb.size();
    //
    make_set();
    //
    for (int x:dsb){
        unions (canhb[x].u, canhb[x].v);
    }
    for (int i=1; i<=lenb; i++){
        if (unions(canhb[i].u, canhb[i].v) ){
            dem++;
            int tmpid = dem + dsb.size();
            if (costb[tmpid]+costa[n-1-tmpid]<ans){
                ans=costb[tmpid]+costa[n-1-tmpid];
                cur = tmpid;
            }
        }
    }
    //
    make_set();
    if (cur>0){
        for (int x:dsb){
            cout<<canhb[x].id<<" ";
            unions (canhb[x].u, canhb[x].v);
        }
        cur-=dsb.size();
        for (int i=1; i<=lenb; i++){
            if (cur>0 && unions(canhb[i].u, canhb[i].v) ){
                cout<<canhb[i].id<<" ";
                cur--;
            }
        }
    }
    for (int i=1; i<=lena; i++){
        if (unions(canha[i].u, canha[i].v)){
            cout<<canha[i].id<<" ";
        }
    }
    cout<<"\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    //freopen("aznet.inp", "r", stdin);
    //freopen("aznet.out", "w", stdout);
    //
    cin>>t;
    while (t--){
        cin>>n>>m;
        for (int i=1; i<n; i++) cin>>costa[i];
        for (int i=1; i<n; i++) cin>>costb[i];
        lena=0;
        lenb=0;
        for (int i=1; i<=m; i++){
            int u, v, c;
            cin>>u>>v>>c;
            if (c==1){
                canha[++lena] = {u, v, i};
            }
            else{
                canhb[++lenb] = {u, v, i};
            }
        }
        //
        process();
    }
}
