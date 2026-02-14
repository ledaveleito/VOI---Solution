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
const string name = "three";
const int lim = 2e5, limit = lim+5, inf = 1e18;

void adds1    (pii &ret, const pii&a, const pii&b){
    if (a.fi==b.fi){
        ret.fi = ret.se = a.fi;
    }
    else if (a.fi<b.fi){
        ret.fi = b.fi;
        ret.se = max (a.fi, b.se);
    }
    else{
        ret.fi = a.fi;
        ret.se = max (b.fi, a.se);
    }
}

struct tree2{
    // fi : id max1, se : id max2
    int ori[limit];
    pii ST[4*limit];
    //
    int maxii (int a, int b){
        if (ori[a]>ori[b]) return a;
        return b;
    }
    void adds (pii &ret, const pii&a, const pii&b){
        if (ori[a.fi]<ori[b.fi]){
            ret.fi = b.fi;
            ret.se = maxii (a.fi, b.se);
        }
        else{
            ret.fi = a.fi;
            ret.se = maxii (b.fi, a.se);
        }
    }
    //
    void update (int id, int l, int r, int pos, int val){
        if (l>pos || r<pos) return;
        if (l==r){
            return;
        }
        int mid = (l+r)/2;
        update (id*2, l, mid, pos, val);
        update (id*2+1, mid+1, r, pos, val);
        adds(ST[id], ST[id*2], ST[id*2+1]);
    }
    //
    void build_tree (int id, int l, int r){
        if (l==r){
            ST[id] = {l, 0};
            return;
        }
        int mid = (l+r)/2;
        build_tree(id*2, l, mid);
        build_tree(id*2+1, mid+1, r);
        adds(ST[id], ST[id*2], ST[id*2+1]);
    }
    void upd (int id, int val, int len){
        ori[id] = val;
        update (1, 1, len, id, val);
    }
    //
    void ini (int A[], int len){
        for (int i=1; i<=len; i++) ori[i] = A[i];
        return build_tree (1, 1, len);
    }
};

struct tree1{
    int ori[limit];
    int ST[8*limit];
    //
    void update (int id, int l, int r, int pos, int val){
        if (l>pos || r<pos) return;
        if (l==r){
            ST[id] = val;
            return;
        }
        int mid = (l+r)/2;
        update (id*2, l, mid, pos, val);
        update (id*2+1, mid+1, r, pos, val);
        ST[id] = max(ST[id*2], ST[id*2+1]);
    }
    //
    void build_tree (int id, int l, int r){
        if (l==r){
            ST[id] = ori[l];
            return;
        }
        int mid = (l+r)/2;
        build_tree(id*2, l, mid);
        build_tree(id*2+1, mid+1, r);
        ST[id] = max(ST[id*2], ST[id*2+1]);
    }
    //
    void upd (int id, int val, int len){
        ori[id] = val;
        update (1, 1, len, id, val);
    }
    //
    void ini (int A[], int len){
        for (int i=1; i<=len; i++) ori[i] = A[i];
        return build_tree (1, 1, len);
    }
};

int n, sl, q;
int lenHang, lenCot;
int sumHang[limit], sumCot[limit];
int preHang[limit], preCot[limit];
int sufHang[limit], sufCot[limit];
pii pre2Hang[limit], pre2Cot[limit];
pii suf2Hang[limit], suf2Cot[limit];
//
pii bestHang[limit], bestCot[limit];
pii secondCot[limit], secondHang[limit];
tree2 xoaCot, xoaHang;
tree1 ddn, nnd;
int dsHang[limit], dsCot[limit];
int motHang[2*limit], motCot[2*limit];
int haiHang[limit], haiCot[limit];
vector <int> insideHang[limit];
vector <int> insideCot[limit];
vector <int> atHang[2*limit];
vector <int> atCot[2*limit];
int orival;
int hang[limit], cot[limit], val[limit];

int finds (int ar[], int len, int val){
    int l = 1, r = len, ret = -1;
    while (l<=r){
        int mid = (l+r)/2;
        if (ar[mid]>=val){
            ret = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return ret;
}

void compress(){
    vector <int> ds;
    ds.clear();
    ds.pb(-1);
    for (int i=1; i<=sl; i++) ds.pb(hang[i]);
    sort(ds.begin(), ds.end());
    ds.erase (unique(ds.begin(), ds.end()), ds.end());
    lenHang = ds.size()-1;
    for (int i=1; i<=lenHang; i++) dsHang[i] = ds[i];
    for (int i=1; i<=sl; i++) hang[i] = finds(dsHang, lenHang, hang[i]);
    //
    ds.clear();
    ds.pb(-1);
    for (int i=1; i<=sl; i++) ds.pb(cot[i]);
    sort(ds.begin(), ds.end());
    ds.erase (unique(ds.begin(), ds.end()), ds.end());
    lenCot = ds.size()-1;
    for (int i=1; i<=lenCot; i++) dsCot[i] = ds[i];
    for (int i=1; i<=sl; i++) cot[i] = finds(dsCot, lenCot, cot[i]);
}

void prep(){
    compress();
    for (int i=1; i<=max(lenHang, lenCot); i++){
        sumHang[i] = 0;
        sumCot[i] = 0;
        insideHang[i].clear();
        insideCot[i].clear();
    }
    for (int i=1; i<=sl; i++){
        sumHang[hang[i]]+=val[i];
        sumCot[cot[i]]+=val[i];
        insideHang[hang[i]].pb(i);
        insideCot[cot[i]].pb(i);
    }
    for (int i=1; i<=2*max(lenHang, lenCot); i++){
        atHang[i].clear();
        atCot[i].clear();
    }
    pre2Hang[0] = suf2Hang[lenHang+1] = {0, 0};
    pre2Cot[0] = suf2Cot[lenCot+1] = {0, 0};
    sufHang[lenHang+1] = 0;
    sufCot[lenCot+1] = 0;
    for (int i=1; i<=lenHang; i++){
        preHang[i] = max (preHang[i-1], sumHang[i]);
        pii tmp = {sumHang[i], 0};
        adds1(pre2Hang[i], pre2Hang[i-1], tmp);
    }
    for (int i=1; i<=lenCot; i++){
        preCot[i] = max (preCot[i-1], sumCot[i]);
        pii tmp = {sumCot[i], 0};
        adds1(pre2Cot[i], pre2Cot[i-1], tmp);
    }
    for (int i=lenHang; i>=1; i--){
        sufHang[i] = max (sufHang[i+1], sumHang[i]);
        pii tmp = {sumHang[i], 0};
        adds1(suf2Hang[i], suf2Hang[i+1], tmp);
    }
    for (int i=lenCot; i>=1; i--){
        sufCot[i] = max (sufCot[i+1], sumCot[i]);
        pii tmp = {sumCot[i], 0};
        adds1(suf2Cot[i], suf2Cot[i+1], tmp);
    }
    //
    xoaHang.ini(sumCot, lenCot);
    for (int i=1; i<=lenHang; i++){
        for (int id:insideHang[i]){
            xoaHang.upd(cot[id], xoaHang.ori[cot[id]]-val[id], lenCot);
        }
        bestHang[i] = {xoaHang.ST[1].fi, xoaHang.ori[xoaHang.ST[1].fi]};
        secondHang[i] = {xoaHang.ST[1].se, xoaHang.ori[xoaHang.ST[1].se]};
        for (int id:insideHang[i]){
            xoaHang.upd(cot[id], xoaHang.ori[cot[id]]+val[id], lenCot);
        }
    }
    //
    xoaCot.ini(sumHang, lenHang);
    for (int i=1; i<=lenCot; i++){
        for (int id:insideCot[i]){
            xoaCot.upd(hang[id], xoaCot.ori[hang[id]]-val[id], lenHang);
        }
        bestCot[i] = {xoaCot.ST[1].fi, xoaCot.ori[xoaCot.ST[1].fi]};
        secondCot[i] = {xoaCot.ST[1].se, xoaCot.ori[xoaCot.ST[1].se]};
        for (int id:insideCot[i]){
            xoaCot.upd(hang[id], xoaCot.ori[hang[id]]+val[id], lenHang);
        }
    }
    //
    orival = 0;
//    cerr<<lenHang<<" "<<lenCot<<"\n";
    for (int i=1; i<=lenHang; i++){
        maximize (orival, sumHang[i]+preHang[i-1]+sufHang[i+1]);
//        cerr<<sumHang[i]+preHang[i-1]+sufHang[i+1]<<"\n";
        maximize (orival, sumHang[i]+bestHang[i].se+secondHang[i].se);
    }
//    cerr<<orival<<"\n";
    for (int i=1; i<=lenCot; i++){
        maximize (orival, sumCot[i]+preCot[i-1]+sufCot[i+1]);
        maximize (orival, sumCot[i]+bestCot[i].se+secondCot[i].se);
    }
    //
    cout<<orival<<"\n";
    //
    // TH 1: 2 XIEN NGANG, 1 XIEN DOC
    for (int i=1; i<=lenCot; i++){
        motCot[i] = bestCot[i].se+sumCot[i];
        atHang[bestCot[i].fi].pb(i);
        motCot[lenCot+i] = secondCot[i].se+sumCot[i];
        atHang[secondCot[i].fi].pb(i+lenCot);
    }
    nnd.ini(motCot, lenCot*2);
    //
    for (int i=1; i<=lenHang; i++){
        for (int id:insideHang[i]){
            nnd.upd(cot[id], nnd.ori[cot[id]]-val[id], lenCot*2);
            nnd.upd(cot[id]+lenCot, nnd.ori[cot[id]+lenCot]-val[id], lenCot*2);
        }
        for (int id:atHang[i]){
            nnd.upd(id, nnd.ori[id]-inf, lenCot*2);
        }
        haiHang[i] = nnd.ST[1]+sumHang[i];
        for (int id:insideHang[i]){
            nnd.upd(cot[id], nnd.ori[cot[id]]+val[id], lenCot*2);
            nnd.upd(cot[id]+lenCot, nnd.ori[cot[id]+lenCot]+val[id], lenCot*2);
        }
        for (int id:atHang[i]){
            nnd.upd(id, nnd.ori[id]+inf, lenCot*2);
        }
    }
    // TH 2: 2 XIEN DOC, 1 XIEN NGANG
    for (int i=1; i<=lenHang; i++){
        motHang[i] = bestHang[i].se+sumHang[i];
        atCot[bestHang[i].fi].pb(i);
        motHang[lenHang+i] = secondHang[i].se+sumHang[i];
        atCot[secondHang[i].fi].pb(i+lenHang);
    }
    ddn.ini(motHang, lenHang*2);
    //
    for (int i=1; i<=lenCot; i++){
        for (int id:insideCot[i]){
            ddn.upd(hang[id], ddn.ori[hang[id]]-val[id], lenHang*2);
            ddn.upd(hang[id]+lenHang, ddn.ori[hang[id]+lenHang]-val[id], lenHang*2);
        }
        for (int id:atCot[i]){
            ddn.upd(id, ddn.ori[id]-inf, lenHang*2);
        }
        haiCot[i] = ddn.ST[1]+sumCot[i];
        for (int id:insideCot[i]){
            ddn.upd(hang[id], ddn.ori[hang[id]]+val[id], lenHang*2);
            ddn.upd(hang[id]+lenHang, ddn.ori[hang[id]+lenHang]+val[id], lenHang*2);
        }
        for (int id:atCot[i]){
            ddn.upd(id, ddn.ori[id]+inf, lenHang*2);
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
    int t;
    cin>>t;
    while (t--){
        cin>>n>>sl>>q;
        for (int i=1; i<=sl; i++){
            cin>>hang[i]>>cot[i]>>val[i];
        }
        //
        prep();
        for (int i=1; i<=q; i++){
            int inc, id;
            cin>>id>>inc;
            int ret = orival;
            int newHang = sumHang[hang[id]]+inc;
            int newCot = sumCot[cot[id]]+inc;
            maximize (ret, newHang+preHang[hang[id]-1]+sufHang[hang[id]+1]);
            maximize (ret, newHang+pre2Hang[hang[id]-1].fi+pre2Hang[hang[id]-1].se);
            maximize (ret, newHang+suf2Hang[hang[id]+1].fi+suf2Hang[hang[id]+1].se);
            maximize (ret, haiHang[hang[id]]+inc);
//            cerr<<haiHang[hang[id]]<<" "<<haiCot[cot[id]]<<"\n";
            maximize (ret, newHang + bestHang[hang[id]].se+secondHang[hang[id]].se);
//            cerr<<newHang<<"\n";
//            cerr<<bestHang[hang[id]].se<<" "<<secondHang[hang[id]].se<<"\n";
//            cerr<<ret<<"\n";
            //
            maximize (ret, newCot+preCot[cot[id]-1]+sufCot[cot[id]+1]);
            maximize (ret, newCot+pre2Cot[cot[id]-1].fi+pre2Cot[cot[id]-1].se);
            maximize (ret, newCot+suf2Cot[cot[id]+1].fi+suf2Cot[cot[id]+1].se);
            maximize (ret, haiCot[cot[id]]+inc);
            maximize (ret, newCot + bestCot[cot[id]].se+secondCot[cot[id]].se);
            cout<<ret<<"\n";
        }
    }
}
