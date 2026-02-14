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
const string name = "camp";
const double inf = 1e14, pi = 3.14159265359;

mt19937_64 rng (chrono::high_resolution_clock::now().time_since_epoch().count());

int randR (int l, int r){
    return uniform_int_distribution<int> (l, r) (rng);
}

double rand (int l, int r){
    return uniform_real_distribution<double> (l, r) (rng);
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct dsu{
    vector <int> par, sz;
    int n;
    dsu (int _n){
        n = _n;
        par.resize(n+2, 0);
        sz.resize(n+2, 0);
        for (int i=0; i<n; i++){
            par[i] = i;
            sz[i] = 1;
        }
    }
    int finds (int u){
        if (u==par[u]) return u;
        return par[u] = finds (par[u]);
    }
    bool unions (int u, int v){
        int a = finds (u), b = finds (v);
        if (a==b) return false;
        if (sz[a]<sz[b]) swap(sz[a], sz[b]);
        sz[a]+=sz[b];
        par[b] = a;
        return true;
    }
};

struct point{
    double x, y;
};

double dist (const point&a, const point&b){
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
};

struct edge{
    int u, v;
    double w;
};

bool comp (const edge&a, const edge&b){
    return a.w<b.w;
}

point p[500];
int n;

double mst (vector <edge> & e, double old){
    sort (e.begin(), e.end(), comp);
    dsu ds(n);
    double ret = 0;
    vector <edge> curbest;
    for (edge tm:e){
        if (ds.unions (tm.u, tm.v)){
            ret+=tm.w;
            curbest.pb(tm);
        }
    }
    if (ret<old) e = curbest;
    return ret;
}

point random_point(){
    double R = rand (0, 100);
    double ang = rand (0, 359);
    double x = R*cos(pi*ang/180.0);
    double y = R*sin(pi*ang/180.0);
    return {x, y};
}

void process(){
    auto startTime = chrono::steady_clock::now();
    int st = n;
    for (int i=1; i<=st-2; i++){
        p[n++] = random_point();
    }
    vector <edge> cure;
    int en = n-1;
    for (int i=0; i<n; i++) for (int j=i+1; j<n; j++) cure.pb({i, j, dist(p[i], p[j])});
    double curw = mst(cure, inf);
//    cerr<<p[en].x<<" "<<p[en].y<<" "<<curw<<"\n";
    double gap = 100;
    while (1){
        auto endTime = chrono::steady_clock::now();
        int ms = chrono::duration_cast<chrono::milliseconds>(endTime-startTime).count();
        if (ms>=2800) break;
        gap*=0.997;
        for (int chosen = st; chosen<=en; chosen++){ // 100
            vector <edge> beste = cure;
            int numloop = 0;
            bool ok = true;
            do{
                cure = beste;
                ok = false;
                numloop++;
                for (int dir = 0; dir<4; dir++){
                    p[chosen].x+=gap*dx[dir];
                    p[chosen].y+=gap*dy[dir];
                    for (edge &tm:cure) if (tm.u==chosen || tm.v==chosen) tm.w = dist(p[tm.u], p[tm.v]);
                    for (int i=0; i<n; i++){
                        cure.pb({chosen, i, dist(p[chosen], p[i])});
                    }
                    if (minimize (curw, mst(cure, curw))){
                        beste = cure;
                        ok = true;
                        break;
                    }
                    else{
                        cure = beste;
                        p[chosen].x-=gap*dx[dir];
                        p[chosen].y-=gap*dy[dir];
                    }
                }
            } while (numloop<=1 && ok);
            cure = beste;
        }
    }
//    cerr<<st<<" "<<en<<"\n";
//    for (int loop = 1; loop<=100; loop++){
//        for (int qq=1; qq<=100; qq++){ // 100
//    //        cerr<<curw<<" ";
//            int chosen = rand (st, en);
//    //        cerr<<chosen<<"\n";
//            double gap = 4;
//            for (int de = 1; de<=20; de++){ // 30
////                cerr<<gap<<"\n";
//                vector <edge> beste = cure;
//                gap/=2;
//                int numloop = 0;
//                bool ok = true;
//                do{
//                    cure = beste;
//                    ok = false;
//                    numloop++;
//                    for (int dir = 0; dir<4; dir++){
////                        cerr<<gap*dx[dir]<<"\n";
//                        p[chosen].x+=gap*dx[dir];
//                        p[chosen].y+=gap*dy[dir];
//                        for (edge &tm:cure) if (tm.u==chosen || tm.v==chosen) tm.w = dist(p[tm.u], p[tm.v]);
//                        for (int i=0; i<n; i++){
//                            cure.pb({chosen, i, dist(p[chosen], p[i])});
//                        }
//                        if (minimize (curw, mst(cure, curw))){
//                            beste = cure;
//                            ok = true;
//                            break;
//                        }
//                        else{
//                            cure = beste;
//                            p[chosen].x-=gap*dx[dir];
//                            p[chosen].y-=gap*dy[dir];
//                        }
//                    }
//                } while (numloop<=5 && ok);
//                cure = beste;
//            }
//        }
//    }

//    for (int i=0; i<4; i++) for (int j=0; j<4; j++){
//        cerr<<i<<" "<<j<<" "<<dist(p[i], p[j])<<"\n";
//    }
//    curw = mst(cure, curw);
//    cerr<<fixed<<setprecision(4)<<curw<<"\n";
    cout<<st-2<<"\n";
    for (int i=st; i<=en; i++){
        cout<<fixed<<setprecision(4)<<p[i].x<<" "<<p[i].y<<"\n";
    }
//    cout<<n-1<<"\n";
    for (edge tm:cure){
        cout<<tm.u+1<<" "<<tm.v+1<<"\n";
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
    double R = 100;
    cin>>n;
    for (int i=0; i<n; i++){
        int deg;
        cin>>deg;
        double x = R*cos(pi*deg/180.0);
        double y = R*sin(pi*deg/180.0);
//        cerr<<x<<" "<<y<<"\n";
        p[i] = {x, y};
    }
    double jury;
    cin>>jury;
    process();
}
