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
const string name = "noel";
const int lim = 2e5, limit = lim+5;

int n, q, color[limit], jump[limit], where[limit];
int L[limit], R[limit], X[limit], Y[limit];

void prep(){
    jump[n] = n+1;
    where[color[n]] = n;
    for (int i=n-1; i>=1; i--){
        jump[i] = jump[i+1];
        minimize (jump[i], where[color[i]]==0 ? n+1 : where[color[i]]);
        where[color[i]] = i;
    }
}

namespace sub1{
    int F[1000], xx[1000], yy[1000], x, y, lenx, leny;
    int rr, tt;
    bool dq (int l, int pos){
        if (l==rr+1){
            tt++;
            if (tt==x){
                lenx = pos-1;
                for (int i=1; i<=lenx; i++) xx[i] = F[i];
            }
            if (tt==y){
                leny = pos-1;
                for (int i=1; i<=leny; i++) yy[i] = F[i];
                return true;
            }
            return false;
        }
        int mxnxt = min(jump[l], rr+1);
        for (int i=mxnxt; i>=l+1; i--){
            F[pos] = i-l;
            bool tmp = dq(i, pos+1);
            if (tmp) return true;
        }
        return false;
    }
    void process(){
        for (int tv = 1; tv<=q; tv++){
            int l = L[tv];
            rr = R[tv];
            x = X[tv]; y = Y[tv];
            if (x>y) swap(x, y);
            tt = 0;
            //
            dq(l, 1);
            int ret = 0;
//            for (int i=1; i<=lenx; i++) cerr<<xx[i]<<" ";
//            cerr<<"\n";
//            for (int i=1; i<=leny; i++) cerr<<yy[i]<<" ";
//            cerr<<"\n";
            for (int i=1; i<=min(lenx, leny); i++){
                if (xx[i]!=yy[i]) break;
                ret++;
            }
            cout<<ret<<"\n";
        }
    }
}

namespace sub5{
    int jj[limit][18];
    int dp[limit], sum[limit];
    //
    int get (int l, int r, int x, int y){
        dp[r+1] = 1;
        sum[r+2] = 0;
        sum[r+1] = 1;
        int besti = r+1;
        for (int i=r; i>=l; i--){
            if (dp[i+1]>=max(x, y)) break;
            int farthest = min(jump[i], r+1);
            dp[i] = sum[i+1]-sum[farthest+1];
//            cerr<<l<<" "<<r<<" "<<i<<" "<<dp[i]<<"\n";
            besti = i;
            if (dp[i]>=max(x, y)){
                break;
            }
            sum[i] = dp[i]+sum[i+1];
        }
        int curpos = l;
        int ret = 0;
        for (int i=17; i>=0; i--){
            if (jj[curpos][i]!=0 && jj[curpos][i]<=besti){
                ret+=MASK(i);
                curpos = jj[curpos][i];
            }
        }
//        cerr<<ret<<"\n";
//        if (ret!=0) assert(0);
        //
        while (curpos<=r){
//            cerr<<curpos<<"\n";
//            cerr<<l<<" "<<r<<" "<<curpos<<"\n";
            int mxnxt = min(jump[curpos]-1, r);
            for (int i=mxnxt; i>=curpos; i--){
//                cerr<<l<<" "<<r<<" "<<curpos<<" "<<i<<" "<<dp[i+1]<<"\n";
                if (dp[i+1]<x && dp[i+1]<y){
                    x-=dp[i+1];
                    y-=dp[i+1];
                    continue;
                }
                if (dp[i+1]>=x && dp[i+1]>=y){
                    ret++;
                    curpos = i+1;
                    break;
                }
                return ret;
            }
        }
        return ret;
    }
    //
    void process(){
        for (int i=1; i<=n; i++){
            jj[i][0] = jump[i];
        }
        for (int i=1; i<=17; i++) for (int j=1; j<=n; j++){
            if (jj[j][i-1]!=n+1){
                jj[j][i] = jj[jj[j][i-1]][i-1];
            }
        }
        //
        for (int i=1; i<=q; i++){
            cout<<get(L[i], R[i], X[i], Y[i])<<"\n";
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
    cin>>n>>q;
    for (int i=1; i<=n; i++) cin>>color[i];
    for (int i=1; i<=q; i++){
        cin>>L[i]>>R[i]>>X[i]>>Y[i];
    }
    prep();
    sub5::process();
}
