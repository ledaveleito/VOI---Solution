#include <bits/stdc++.h>
#define int long long
#define ll long long
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
const string name = "GIFT";
const int lim = 1e5, limit = lim+5, inf = 1e9;

int n;

struct fenwick{
    long long BIT[limit];
    void update (int id, int val){
        while (id<=n){
            BIT[id]+=val;
            id+=(id&(-id));
        }
    }
    long long get (int id){
        int ret = 0;
        while (id>0){
            ret+=BIT[id];
            id&=id-1;
        }
        return ret;
    }
};

fenwick fen1, fen2, cnt1, cnt2;
int q;
int W[limit], S[limit], M[limit], K[limit], T[limit];
pii ds[limit], ds2[limit], dst[limit];
int kind[limit];
int ret[limit];
int L[limit], R[limit];

// moi tui co dung k mon khac nhau
// suy ra la k*t mon
//
// phai la khong duoc chon qua t

int maxk (int diff, int capa){
    int des = 0, alr = 0;
    for (int i=20; i>=0; i--){
        if (des+MASK(i)<=n){
            int tm = des+MASK(i);
            int tmget = fen1.BIT[tm]*diff+fen2.BIT[tm];
//            cerr<<tm<<" "<<fen2.BIT[tm]<<"\n";
            if (capa>=tmget){
                capa-=tmget;
                des = tm;
//                if (diff==5) cerr<<cnt2.BIT[tm]<<"\n";
                alr += diff*cnt1.BIT[tm] + cnt2.BIT[tm];
            }
        }
    }
//    if (diff==6) cerr<<des<<" "<<alr<<" "<<capa<<"\n";
    des++;
    if (des<=n){
        int val = ds[des].fi;
        int sl = ds[des].se;
        int maxadd = min(capa/val, min(sl, diff));
        alr+=maxadd;
    }
//    if (diff==1 && capa==19) cerr<<alr<<"\n";
    return alr/diff;
//    cerr<<diff<<" "<<alr<<"\n";
}

void process(){
    // chua bao hoa:
    // fen1: counting theo sum each co bao nhieu cai chua bao hoa
    // fen2: trang thai da bao hoa
    for (int i=1; i<=n; i++){
        ds[i] = {W[i], S[i]};
    }
    sort (ds+1, ds+n+1);
//    for (int i=1; i<=n; i++) cerr<<ds[i].fi<<" "<<ds[i].se<<"\n";
    for (int i=1; i<=n; i++){
        ds2[i] = {ds[i].se, i};
    }
    // W, S phe roi
    sort (ds2+1, ds2+n+1);
    //
    for (int i=1; i<=q; i++){
        ret[i] = 0;
        if (kind[i]==1){
            L[i] = T[i];
            R[i] = T[i];
        }
        else{
            L[i] = 1;
            R[i] = inf;
        }
    }
    for (int loops = 1; loops<=32; loops++){
        int numt = 0;
        for (int i=1; i<=q; i++){
            if (L[i]<=R[i]){
                int mid = (L[i]+R[i])/2;
                dst[++numt] = {mid, i};
            }
        }
        if (numt==0) break;
        sort (dst+1, dst+numt+1);
        for (int i=0; i<=n; i++){
            fen1.BIT[i] = 0;
            fen2.BIT[i] = 0;
            cnt1.BIT[i] = 0;
            cnt2.BIT[i] = 0;
        }
        for (int i=1; i<=n; i++){
            fen1.update (i, ds[i].fi);
            cnt1.update (i, 1);
        }
//        if (loops==29){
//            for (int i=1; i<=numt; i++) cerr<<dst[i].fi<<" "<<dst[i].se<<"\n";
//        }
        int cur = 1;
        for (int i=1; i<=numt; i++){
            int tmpt = dst[i].fi;
//            cerr<<dst[i].fi<<" "<<dst[i].se<<"\n";
            while (cur<=n && ds2[cur].fi<=tmpt){
//                if (loops==29) cerr<<cur<<"\n";
                int id = ds2[cur].se;
                int sl = ds2[cur].fi;
                int val = ds[id].fi;
                fen1.update (id, -val);
                cnt1.update (id, -1);
                fen2.update (id, val*sl);
                cnt2.update (id, sl);
                cur++;
            }
            int iq = dst[i].se;
//            if (iq==2) cerr<<tmpt<<" "<<M[iq]<<"\n";
            if (maxk(tmpt, M[iq])>=K[iq]){
                ret[iq] = tmpt;
                L[iq] = tmpt+1;
            }
            else{
                R[iq] = tmpt-1;
            }
        }
    }
    for (int i=1; i<=q; i++){
        if (kind[i]==1){
            if (ret[i]==0) cout<<"0\n";
            else cout<<"1\n";
        }
        else cout<<ret[i]<<"\n";
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
    for (int i=1; i<=n; i++) cin>>W[i];
    for (int i=1; i<=n; i++) cin>>S[i];
    for (int i=1; i<=q; i++){
        cin>>kind[i]>>M[i]>>K[i];
        if (kind[i]==1) cin>>T[i];
    }
    process();
}
