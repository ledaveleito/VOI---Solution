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
const string name = "blgame";
const int lim = 1200, limit = lim+5;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
bool vis[3][3][limit][limit];
int s1[limit][limit];
int velo[limit];
int n, m, len[3], k;
int banned[limit][limit];

struct ele{
    int nrow, ncol, xtop, ytop;
};

int get (int x1, int y1, int x2, int y2){
    return banned[x2][y2] - banned[x1-1][y2] - banned[x2][y1-1] + banned[x1-1][y1-1];
}

void update (int xs, int ys,int  xl,int yl){
//    cerr<<xs<<" "<<ys<<"  "<<xl<<" "<<yl<<"\n";
    s1[xs][ys]++;
    s1[xs][yl+1]--;
    s1[xl+1][ys]--;
    s1[xl+1][yl+1]++;
}

int query (){
    int ret = 0;
    for (int row = 1; row<=n; row++){
        for (int col = 1; col<=m; col++){
            velo[col]+=s1[row][col];
        }
        int val = 0;
        for (int col=1; col<=m; col++){
            val+=velo[col];
//            cerr<<val<<" ";
            if (val>0) ret++;
        }
//        cerr<<"\n";
    }
//    if (ret==0) assert(0);
    return ret;
}

bool ok (int x, int y){
    return x>=1 && y>=1 && x<=n && y<=m;
}

bool ok (int r, int c, int xt, int yt){
    r = len[r]; c = len[c];
    return ok(xt, yt) && ok (xt+r-1, yt+c-1) && get(xt, yt, xt+r-1, yt+c-1)==0;
}

void process(){
    //
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            banned[i][j] += banned[i][j-1] + banned[i-1][j] - banned[i-1][j-1];
        }
    }
    if (!ok(0, 1, 1, 1)){
        cout<<"0";
        return;
    }
    //
    queue <ele> q;
    q.push({0, 1, 1, 1});
    vis[0][1][1][1] = true;
    while (!q.empty()){
        ele tmp = q.front();
        q.pop();
        //
        int nrow = tmp.nrow, ncol = tmp.ncol, xtop = tmp.xtop, ytop = tmp.ytop;
        //
        for (int i=0; i<4; i++){
            int newx = xtop+dx[i], newy = ytop+dy[i];
            if (ok(nrow, ncol, newx, newy) && !vis[nrow][ncol][newx][newy]){
                vis[nrow][ncol][newx][newy] = true;
                q.push({nrow, ncol, newx, newy});
            }
        }
        //
        int rem = 3-nrow-ncol;
        // lat len tren
        int nr = rem, nc = ncol, xt = xtop-len[rem], yt = ytop;
        if (ok(nr, nc, xt, yt) && !vis[nr][nc][xt][yt]){
            vis[nr][nc][xt][yt] = true;
            q.push({nr, nc, xt, yt});
        }
        // lat xuong duoi
        nr = rem; nc = ncol; xt = xtop+len[nrow]; yt = ytop;
        if (ok(nr, nc, xt, yt) && !vis[nr][nc][xt][yt]){
            vis[nr][nc][xt][yt] = true;
            q.push({nr, nc, xt, yt});
        }
        // lat sang trai
        nr = nrow; nc = rem; xt = xtop; yt = ytop-len[rem];
        if (ok(nr, nc, xt, yt) && !vis[nr][nc][xt][yt]){
            vis[nr][nc][xt][yt] = true;
            q.push({nr, nc, xt, yt});
        }
        // lat sang phai
        nr = nrow; nc = rem; xt = xtop; yt = ytop+len[ncol];
        if (ok(nr, nc, xt, yt) && !vis[nr][nc][xt][yt]){
            vis[nr][nc][xt][yt] = true;
            q.push({nr, nc, xt, yt});
        }
    }
    //
    for (int i=1; i<=n; i++) for (int j = 1; j<=m; j++){
        for (int k1 = 0; k1<=2; k1 ++) for (int k2 = 0; k2<=2; k2++){
            if (vis[k1][k2][i][j]){
                update (i, j, i+len[k1]-1, j+len[k2]-1);
            }
        }
    }
    //
    cout<<query()<<"\n";
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
    cin>>len[0]>>len[1]>>len[2]>>n>>m>>k;
    for (int i=1; i<=k; i++){
        int x, y;
        cin>>x>>y;
        banned[x][y] ++;
    }
    process();
}
