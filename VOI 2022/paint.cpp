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
const string name = "paint";

struct point{
    int x, y;
};

struct segment{
    point A, B;
    int id;
    bool upper;
    double get_y (int qx) const{
        if (A.x==B.x) return A.y;
        return 1.0*(B.y-A.y)/(B.x-A.x)*(qx-A.x)+A.y;
    }
};

int cross_product (const point&a, const point&b, const point&c){
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

bool operator < (const segment&a, const segment&b){
    if (a.A.x==b.A.x && a.A.y==b.A.y){
        return cross_product(a.A, a.B, b.B)>0;
    }
    int xx = max(a.A.x, b.A.x);
    return a.get_y(xx)<b.get_y(xx);
}

struct Event{
    segment seg;
    int x, y, kind;
};

bool cevent (const Event&a, const Event&b){
    if (a.x!=b.x) return a.x<b.x;
    if (a.kind!=b.kind) return a.kind<b.kind;
    return a.y>b.y;
}

Event event[1200000];
set <segment> bst;
int maxx, maxy, n, m, q;
int area2[200000], s2[200000];
int par[200000];
int trace[200000];
int numevent;


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
    cin>>maxx>>maxy>>n>>m>>q;
    //
    for (int i=1; i<=n; i++){
        point p[7];
        for (int j=0; j<m; j++) cin>>p[j].x>>p[j].y;
        point ria;
        ria = p[0];
        //
        for (int j=0; j<m; j++){
            if (p[j].x<ria.x || (p[j].x==ria.x && p[j].y>ria.y)) ria = p[j];
            int nx = (j+1)%m;
            area2[i]+=(p[j].y+p[nx].y)*(p[j].x-p[nx].x);
            if (p[j].x==p[nx].x) continue;
            segment seg;
            seg.A = p[j]; seg.B = p[nx];
            seg.id = i;
            seg.upper = true;
            if (p[j].x>p[nx].x){
                swap(seg.A, seg.B);
                seg.upper = false;
            }
            event[++numevent] = {seg, seg.A.x, seg.A.y, 2};
            event[++numevent] = {seg, seg.B.x, seg.B.y, 1};
        }
        area2[i] = abs(area2[i]);
        s2[i] = area2[i];
        segment tmp = {ria, ria, i, 0};
        event[++numevent] = {tmp, ria.x, ria.y, 0};
    }
    for (int i=1; i<=q; i++){
        int x, y;
        cin>>x>>y;
        point p = {x, y};
        segment tmp = {p, p, -i, 0};
        event[++numevent] = {tmp, x, y, 0};
    }
    s2[0] = maxx*maxy*2;
    //
    sort (event+1, event+numevent+1, cevent);
//    cerr<<"ok";
    //
    for (int i=1; i<=numevent; i++){
        segment seg = event[i].seg;
        int kind = event[i].kind;
//        cerr<<kind<<"\n";
//        cerr<<seg.A.x<<" "<<seg.A.y<< "  "<<seg.B.x<<" "<<seg.B.y<<"\n";
        if (kind==2){
//            int t1 = bst.size();
            bst.insert(seg);
        }
        else if (kind==0){
            set <segment> :: iterator it = bst.upper_bound(seg);
            //
            int pa = 0;
            if (it==bst.end()){
                pa = 0;
            }
            else{
                pa = it->id;
                bool upper = (it->upper);
                if (!upper) pa = par[pa];
            }
            if (seg.id<0){
                trace[-seg.id] = pa;
            }
            else{
                int cur = seg.id;
                par[cur] = pa;
//                cerr<<cur<<" "<<pa<<"\n";
                s2[pa]-=area2[cur];
            }
        }
        else{
//            auto it = bst.lower_bound(seg);
//            if (it==bst.end()){
//                cout<<"df";
//                return 0;
//            }
//            else return 0;
//            if (bst.lower_bound(seg)==bst.end()){
//                cerr<<"Not ok\n";
//            }
            bst.erase (bst.lower_bound(seg));
        }
//        cerr<<"sz  "<<bst.size()<<"\n";
    }
    //
    for (int i=1; i<=q; i++){
//        cerr<<trace[i]<<"\n";
        cout<<fixed<<setprecision(1)<<1.0*s2[trace[i]]/2<<"\n";
    }
}
