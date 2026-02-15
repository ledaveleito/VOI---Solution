#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int limit=2e6+5;

struct point{
    int x, y;
};

struct datas{
    int a, b, c, id;
};

datas ds[limit];
pii edge[limit];
point p[limit];
bool vis[limit];
vector <int> red, blue;
int n;
int len;


bool comp (const datas&a, const datas&b){
    if (a.a!=b.a) return a.a<b.a;
    if (a.b!=b.b) return a.b<b.b;
    if (a.c!=b.c) return a.c<b.c;
    return a.id<b.id;
}

void add (int id){
    if (vis[edge[id].fi]==false){
        if (edge[id].fi*2<=n) red.push_back(edge[id].fi); else blue.push_back(edge[id].fi);
        vis[edge[id].fi]=true;
    }
    if (vis[edge[id].se]==false){
        if (edge[id].se*2<=n) red.push_back(edge[id].se); else blue.push_back(edge[id].se);
        vis[edge[id].se]=true;
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //
    cin>>n;
    n*=2;
    for (int i=1; i<=n; i++) cin>>p[i].x>>p[i].y;
    //
    for (int i=1; i*2<=n; i++){
        for (int j=n/2; j<=n; j++){
            len++;
            edge[len] = {i, j};
            int xa = p[i].x, ya = p[i].y;
            int xb = p[j].x, yb = p[j].y;
            int a = ya-yb;
            int b = xb-xa;
            int c = -xa*(ya-yb)-ya*(xb-xa);
            int gcd;
            if (a!=0) gcd = __gcd(__gcd(abs(a), abs(b)), abs(c));
            else if (b!=0) gcd = __gcd(__gcd(abs(a), abs(b)), abs(c));
            else gcd = __gcd(__gcd(abs(c), abs(b)), abs(a));
            a/=gcd; b/=gcd;
            c/=gcd;
            if (a<0){
                a=-a; b=-b; c=-c;
            }
            ds[len]={a, b, c, len};
            //cerr<<a<<" "<<b<<" "<<c<<i<<" "<<j<<"\n";
        }
    }
    sort(ds+1, ds+len+1, comp);
    add (ds[1].id);
    for (int i=2; i<=len; i++){
        if (ds[i].a==ds[i-1].a && ds[i].b==ds[i-1].b && ds[i].c==ds[i-1].c){
            add(ds[i].id);
            //cerr<<red.size()<<" "<<blue.size()<<"\n";
            if (red.size()>1 && blue.size()){
                cout<<red[0]<<" "<<red[1]<<" "<<blue[0];
                return 0;
            }
            else if (red.size() && blue.size()>1){
                cout<<blue[0]<<" "<<blue[1]<<" "<<red[0];
                return 0;
            }
        }
        else{
            for (int x:red) vis[x]=false;
            for (int x:blue) vis[x]=false;
            red.clear();
            blue.clear();
            add(ds[i].id);
        }
    }
    cout<<"-1";
}
