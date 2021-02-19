#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define P pair<int,int>
#define fi first
#define se second
using namespace std;
template <class T> bool umin(T &x,T y) {return y<x? x=y,1: 0;}
template <class T> bool umax(T &x,T y) {return y>x? x=y,1: 0;}
const int N = 40005, M = 100005;
int block,a[N],x[N],cnt=0,n,m,un,L[N],R[N],far[N][17],dep[N];
int b[N*2],c[N*2],pos[N*2];
vector<int> g[N];
void dfs(int u,int fa) {
	cnt++;
	L[u] = cnt;
	b[cnt] = u;
	c[cnt] = a[u];
	for(int i=0;i<(int)g[u].size();++i) {
		int v = g[u][i]; if(v == fa) continue;
		dep[v] = dep[u]+1;
		dfs(v,u);
		far[v][0] = u;
	}
	cnt++;
	R[u] = cnt;
	b[cnt] = u;
	c[cnt] = a[u];
}
int LCA(int u,int v) {
	if(dep[u] < dep[v]) swap(u,v);
	int dlt = dep[u]-dep[v];
	for(int i=16;i>=0;--i) if(dlt&(1<<i)) u = far[u][i];
	if(u == v) return u;
	for(int i=16;i>=0;--i) if(far[u][i]^far[v][i]) u=far[u][i],v=far[v][i];
	return far[u][0];	
}

struct Query{
	int l,r,id,lc;
	bool operator<(const Query &o) const {
		return pos[l]==pos[o.l]? r<o.r: pos[l]<pos[o.l];
	}
}q[M*2];
int totq=0,to[M*2];
P subq[N];
int ans=0,cnt_nd[N],cnt_col[N],Ans[M];

void Add(int);
void Sub(int);

signed main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i=1;i<=n;++i) {
		cin >> a[i];
		x[i] = a[i]; 
	}
	sort(x+1,x+n+1);
	un = unique(x+1,x+n+1)-x-1;
	for(int i=1;i<=n;++i) {
		a[i] = lower_bound(x+1,x+un+1,a[i]) - x;
	}

	for(int i=1,u,v;i<n;++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(1,0);
	for(int i=1;i<17;++i) for(int u=1;u<=n;++u) 
		far[u][i] = far[far[u][i-1]][i-1];

	for(int i=1,u,v;i<=m;++i) {
		cin >> u >> v;
		if(L[u] > L[v]) swap(u,v);
		int lca = LCA(u,v);
		q[i] = (Query){R[u],L[v],i,L[lca]};
	}

	block = sqrt(2*n);
	for(int i=1;i<=2*n;++i) pos[i] = (i-1)/block+1;
	sort(q+1,q+m+1);

	for(int i=1,l=1,r=0;i<=m;++i) {
		while(r < q[i].r) Add(++r);
		while(r > q[i].r) Sub(r--);
		while(l < q[i].l) Sub(l++);
		while(l > q[i].l) Add(--l);
		Ans[q[i].id] = ans+(cnt_col[c[q[i].lc]]==0);
	}
	for(int i=1;i<=m;++i) cout << Ans[i] << "\n";

	return 0;
}
void Add(int x) {
	cnt_nd[b[x]] ^= 1;
	if(!cnt_nd[b[x]]) ans -= (--cnt_col[c[x]]==0);
	else ans += !cnt_col[c[x]]++;
}
void Sub(int x) {
	cnt_nd[b[x]] ^= 1;
	if(!cnt_nd[b[x]]) ans -= (--cnt_col[c[x]]==0);
	else ans += !cnt_col[c[x]]++;
}