#include <bits/stdc++.h>
using namespace std;

map<int,vector<int>> mp;

const int N = 1e5;
const int LOGN = 20;
const int INF = 1e9;


int tree[N+1], ans[N+1], level[N+1];
int up[N+1][LOGN];
int w,centroid;
bool mark[N+1];


//---------------------------------------------------------------------

void dfs(int u=1,int p=1,int l=0){
  level[u] = l;
  up[u][0] = p;
  for(int v:mp[u]){
    if(v!=p){
      dfs(v,u,l+1);
    }
  }
}

int lca(int a,int b){
  if(level[b] < level[a])
    swap(a,b);

  int d = level[b] - level[a];
  
  for(int i=0;i<20;i++){
    if(d&(1<<i))
      b = up[b][i];
  }

  if(a == b) return a;
  
  for(int i = 19; i >= 0; i--){
    if(up[a][i] != up[b][i])
      a = up[a][i], b = up[b][i];
  }
  
  return up[a][0];
}

int dist(int u,int v){
  return level[u] + level[v] - 2 * level[lca(u,v)];
}

void preprocess(int n){  
  dfs();
  for(int j = 1; j < LOGN;j++)
    for(int i = 1; i <= n; i++)
      up[i][j] = up[up[i][j-1]][j-1];    
}


//-----------------------------------------------------------------------

int dfs_size(int u,int p){
  if(mark[u]) return 0;
  int s = 1;
  for(int v:mp[u])
    if(v!=p)
      s += dfs_size(v,u);
  return s;
}

int dfs_centroid(int u,int p){
  if(mark[u]) return 0;
  
  int s = 1;
  bool ok = true;
  
  for(int v:mp[u]){
    if(v!=p){
      int sz = dfs_centroid(v,u);
      if(sz>w/2)
        ok = false;
      s+=sz;
    }
  }
  
  if(s<w/2) ok = false;
  if(ok) centroid = u;
  
  return s;
}

void decompose(int u = 1,int p = -1){
  
  w = dfs_size(u,-1);
  dfs_centroid(u,-1);
  
  int c = centroid;
  
  tree[c] = p;
  mark[c] = true;
  
  for(int u:mp[c])
    if(!mark[u])
      decompose(u,c);
}


//------------------------------------------------------------------------

void update(int u){
  int x = u;
  while(1){
    ans[x] = min(ans[x],dist(x,u));
    if(x == tree[x])
      break;
    x = tree[x];
  }
}

int query(int u){
  int x = u;
  int ret = INF;
  while(1){
    ret = min(ret,ans[x] + dist(u,x));
    if(x==tree[x])
      break;
    x = tree[x];
  }
  return ret;
}

//----------------------------------------------------------------------------

int main(){
  int n,m,u,v,t;
  cin >> n >> m;
  for(int i=1;i<n;i++){
    cin >> u >> v;
    mp[u].push_back(v);
    mp[v].push_back(u);
  }

  for(int i=1;i<N;i++){
    ans[i] = INF;
    tree[i] = -1;
    level[i] = 0;    
  }

  preprocess(n);
  decompose();
  update(1);

  // for(int i=1;i<=n;i++)
  //   cout<<tree[i]<<" ";

  while(m--){
    cin>>t>>u;
    if(t==1){
      ans[u] = 0;
      update(u);
    }else{
      int x = query(u);
      cout<<x<<"\n";
    }
  }
  return 0;
}