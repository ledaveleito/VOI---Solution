#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int limit=1505, inf=1e9+5;

int t, n, m;
int A[limit], B[limit], dp[limit];
vector <int> inside[2*limit];
vector <int> num;

void compress(){
    set <int> se;
    for (int i=1; i<=n; i++) se.insert(A[i]);
    for (int i=1; i<=m; i++) se.insert(B[i]);
    //
    num.clear();
    for (int x:se) num.push_back(x);
    map <int, int> mp;
    for (int i=0; i<num.size(); i++) mp[num[i]]=i;
    for (int i=1; i<=n; i++) A[i]=mp[A[i]];
    for (int i=1; i<=m; i++) B[i]=mp[B[i]];
    //
    for (int i=0; i<num.size(); i++) inside[i].clear();
    for (int i=1; i<=m; i++) inside[B[i]].push_back(i);
}

int finds (int kind, int cantren){
    int l=0, r=inside[kind].size()-1, ret=inf;
    while (l<=r){
        int mid=(l+r)/2;
        if (inside[kind][mid]<cantren){
            ret=inside[kind][mid];
            l=mid+1;
        }
        else r=mid-1;
    }
    return ret;
}

void process(){
    compress();
    //
    for (int i=1; i<=n; i++){
        if (inside[A[i]].size()==0) dp[i]=inf;
        else dp[i] = inside[A[i]].back();
    }
    //
    int ret=0;
    while (1){
        bool ok=false;
        for (int i=1; i<=n; i++) if (dp[i]!=inf){
            ok=true;
            break;
        }
        //for (int i=1; i<=n; i++) cerr<<dp[i]<<" ";
        //cerr<<"\n";
        if (!ok) break;
        ret++;
        map <int, int> mp;
        //
        for (int i=n; i>=1; i--){
            if (dp[i]==inf) continue;
            int old=dp[i];
            int aimval = num[A[i]]*2;
            auto it = mp.lower_bound(aimval);
            //cerr<<mp.size()<<"\n";
            if (it==mp.end()) dp[i]=inf;
            else{
                int nxt = (*it).se;
                //cerr<<i<<(*it).fi<<" "<<nxt<<"\n";
                dp[i] = finds(A[i], nxt);
            }
            int curval = num[A[i]];
            it = mp.upper_bound (curval);
            //if (it==mp.end()) cerr<<"1\n"; else cerr<<"0\n";
            //cerr<<curval<<" "<<(*it).fi<<"\n";
            if (it==mp.end() || old>(*it).se){
                //cerr<<i<<" "<<curval<<" "<<mp[curval]<<" "<<old<<"\n";
                int phu=mp[curval]=max(mp[curval], old);
                auto ti = mp.lower_bound(curval);
                auto it2=ti;
                while (it2!=mp.begin()){
                    it2--;
                    if ((*it2).se >phu) break;
                }
                if (it2==ti) continue;
                if ((*it2).se>phu) it2++;
                while (it2!=ti){
                    //cerr<<"ok\n";
                    auto it3=it2;
                    it3++;
                    mp.erase(it2);
                    it2=it3;
                }
            }
        }
    }
    cout<<ret<<"\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("lcs2x.inp", "r", stdin);
    //freopen("lcs2x.out", "w", stdout);
    //
    int t;
    cin>>t;
    while (t--){
        cin>>n>>m;
        for (int i=1; i<=n; i++) cin>>A[i];
        for (int i=1; i<=m; i++) cin>>B[i];
        process();
    }
}
