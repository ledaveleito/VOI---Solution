#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define int long long
using namespace std;
const int limit=1e3+5, bar=1e10;

int dx[4]={0,-1,0,+1};
int dy[4]={-1,0,+1,0};
int n,x,y,s,stt=-1;
string S[limit];
int vis[limit][limit][4];
pii toado[limit*limit*10];



void print(int lx, int ly, int ld){
    if (stt==s){
        cout<<lx<<" "<<ly;
    }
    else if (lx>=1 && ly>=1 && lx<=n && ly<=n){
        int tmp=vis[lx][ly][ld]+(s-stt-1)%(stt-vis[lx][ly][ld]+1);
        cout<<toado[tmp].fi<<" "<<toado[tmp].se;
    }
    else if (ld==0){
        stt++;
        cout<<lx<<" "<<ly-(s-stt);
    }
    else if (ld==1){
        stt++;
        cout<<lx-(s-stt)<<" "<<ly;
    }
    else if (ld==2){
        stt++;
        cout<<lx<<" "<<ly+(s-stt);
    }
    else{
        stt++;
        cout<<lx+(s-stt)<<" "<<ly;
    }
    exit(0);
}


void input(){
    cin>>n>>x>>y>>s;
    for (int i=1; i<=n; i++)
        cin>>S[i];
    for (int i=1; i<=n; i++) S[i]=" "+S[i];
}

void dfs(int tx, int ty, int huong){
    vis[tx][ty][huong]=++stt;
    toado[stt]={tx,ty};
    //cout<<tx<<" "<<ty<<" "<<huong<<"\n";
    if (stt==s) print(tx,ty,huong);
    for (int i=0; i<4; i++){
        int ndirec=(huong+i)%4;
        int newx=tx+dx[ndirec], newy=ty+dy[ndirec];
        //if (tx==3 && ty==3) cout<<newx<<" "<<newy<<" "<<ndirec<<"\n";
        if (newx<1 || newy<1 || newx>n || newy>n) print(newx,newy,ndirec);
        if (S[newy][newx]=='#') continue;
        else{
            if (vis[newx][newy][ndirec]) print(newx,newy,ndirec);
            dfs(newx,newy,ndirec);
            return;
        }
    }
}

void process(){
    if (x<=0 || x>n || y<=0){
        cout<<x<<" "<<y-s;
        return;
    }
    if (y>n && S[n][x]=='#'){
        s-=(y-n-1);
        y=n+1+s;
        cout<<x-s<<" "<<n+1;
        return;
    }
    if (y-n>=s){
        cout<<x<<" "<<y-s;
        return;
    }
    if (y>n) s-=(y-n);
    dfs(x,min(y,n),0);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    input();
    process();
}
