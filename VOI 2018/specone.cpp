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
const string name = "specone";
const int lim = 1e5, limit = lim+5;

int n, k, s, m;
map <string, int> mp;
string man[limit];
int numman;
vector <int> affect[limit];
bool spe[limit];
int numcon[limit];

void process(){
    for (int i=1; i<=n; i++){
        sort(affect[i].begin(), affect[i].end());
        affect[i].erase (unique(affect[i].begin(), affect[i].end()), affect[i].end());
    }
//    if (numman>n) assert(0);
    queue <int> q;
    for (int i=1; i<=s; i++) q.push(i);
    for (int i=1; i<=s; i++) spe[i] = true;
    while (!q.empty()){
        int cur = q.front();
        q.pop();
        for (int v:affect[cur]){
            numcon[v]++;
            if (!spe[v] && numcon[v]>=k){
                spe[v] = true;
                q.push(v);
            }
        }
    }
    vector <string> vv;
    for (int i=1; i<=n; i++) if (spe[i]) vv.pb(man[i]);
    sort(vv.begin(), vv.end());
    cout<<vv.size()<<"\n";
    for (string tmp:vv) cout<<tmp<<" ";
//    if (n>100) assert(0);
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
    cin>>n>>k>>s>>m;
    for (int i=1; i<=s; i++){
        string tm;
        cin>>tm;
        mp[tm] = ++numman;
        man[numman] = tm;
    }
    for (int i=1; i<=m; i++){
        string s1, s2;
        cin>>s1>>s2;
//        if (s1==s2) assert(0);
        int id1 = mp[s1], id2 = mp[s2];
        if (id1==0){
            mp[s1] = ++numman;
            id1 = numman;
            man[numman] = s1;
        }
        if (id2==0){
            mp[s2] = ++numman;
            id2 = numman;
            man[numman] = s2;
        }
        affect[id1].pb(id2);
        affect[id2].pb(id1);
    }
    process();
}
