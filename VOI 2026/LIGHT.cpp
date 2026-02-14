#include <bits/stdc++.h>
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
const string name = "light";

int dist[7][667][667];
int sum[667][4];
int n,q,x, y;
int A[667];

struct ele{
    int c0, c1, c2;
};

void prep(){
    for (int i=1; i<=n; i++){
        for (int j=0; j<=2; j++) sum[i][j] = sum[i-1][j];
        sum[i][A[i]]++;
    }
    queue <ele> q;
    memset (dist, -1, sizeof(dist));
    for (int i=1; i<=min(6, n); i++){
        q.push({i, 0, 0});
        dist[i][0][0] = 0;
    }
    while (!q.empty()){
        ele tmp = q.front();
        q.pop();
        int c0 = tmp.c0, c1 = tmp.c1, c2 = tmp.c2;
//        cerr<<c0<<" "<<c1<<" "<<c2<<" "<<dist[c0][c1][c2]<<"\n";
        int cur = dist[c0][c1][c2];
        if (c0<6){
            for (int a0 = 0; a0<=x && a0<=c0; a0++){
                for (int a1 = 0; a0+a1<=x && a1<=c1; a1++){
                    int a2 = x-a0-a1;
                    if (a2>c2) continue;
                    for (int s0 = 0; s0<=y && a0+s0<=c0; s0++){
                        for (int  s1 = 0; s0+s1<=y && a1+s1<=c1; s1++){
                            int s2 = y-s0-s1;
                            if (a2+s2>c2) continue;
                            int n0 = min(6, c0 - a0 - s0 + a1 + s2);
                            int n1 = c1 - a1 - s1 + a2 + s0;
                            int n2 = c2 - a2 - s2 + a0 + s1;
//                            cerr<<n0<<" "<<n1<<" "<<n2<<" \n";
                            if (dist[n0][n1][n2]==-1){
                                dist[n0][n1][n2] = cur+1;
                                q.push({n0, n1, n2});
                            }
                        }
                    }
                }
            }
        }
        else{
            for (int a0 = 0; a0<=x && a0<=c0; a0++){
                for (int a1 = 0; a0+a1<=x && a1<=c1; a1++){
                    int a2 = x-a0-a1;
                    if (a2>c2) continue;
                    for (int s0 = 0; s0<=y && a0+s0<=c0; s0++){
                        for (int  s1 = 0; s0+s1<=y && a1+s1<=c1; s1++){
                            int s2 = y-s0-s1;
                            if (a2+s2>c2) continue;
                            int nn0 = min(6, c0 - a0 - s0 + a1 + s2);
                            int n1 = c1 - a1 - s1 + a2 + s0;
                            int n2 = c2 - a2 - s2 + a0 + s1;
                            for (int n0 = nn0; n0<=6; n0++){
                                if (n0-nn0+6+c1+c2<=n){
                                    if (dist[n0][n1][n2]==-1){
                                        dist[n0][n1][n2] = cur+1;
                                        q.push({n0, n1, n2});
                                    }
                                }
                            }
                        }
                    }
                }
            }
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
    cin>>n>>q>>x>>y;
    for (int i=1; i<=n; i++) cin>>A[i];
    prep();
    for (int i=1; i<=q; i++){
        int l ,r;
        cin>>l>>r;
        cout<<dist[min(6, sum[r][0]-sum[l-1][0])][sum[r][1]-sum[l-1][1]][sum[r][2]-sum[l-1][2]]<<"\n";
    }
}
