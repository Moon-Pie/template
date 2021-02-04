#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,dp[N],pnt[N*2],nxt[N*2],head[N],val[N*2],E=0,key[N],ine[N][20],far[N][20],dep[N],sum[N],dfn[N],cnt=0,a[N],st[N],top;
void adde(int u,int v,int w) {pnt[++E]=v;nxt[E]=head[u];head[u]=E;val[E]=w;}
struct edge {int to,c; };
vector<edge> g[N];
void presol(int u,int fa) {
	dfn[u] = ++cnt;
	for(int i=head[u];i;i=nxt[i]) {
		int v=pnt[i]; if(v==fa) continue;
		far[v][0]=u;
		ine[v][0]=val[i];
		dep[v] = dep[u]+1;
		sum[v] = sum[u]+val[i];
		presol(v,u);
	}
}
int mie;
int LCA(int u,int v) {
	mie=1e9;
	if(dep[u] < dep[v]) swap(u,v);
	int dlt = dep[u]-dep[v];
	for(int i=19;i>=0;--i) if(dlt&(1<<i)) mie=min(mie,ine[u][i]),u=far[u][i];
	if(u==v) return u;
	for(int i=19;i>=0;--i) if(far[u][i]^far[v][i]) {
		mie=min(mie,ine[u][i]);
		mie=min(mie,ine[v][i]);
		u=far[u][i],v=far[v][i];
	}
	return far[u][0];
}
void dfs(int u) {
	dp[u]=0;
	for(int i=0;i<g[u].size();++i) {
		int v=g[u][i].to,d=g[u][i].c;
		dfs(v);
		if(key[v]) dp[u]+=d;
		else dp[u]+=min(d,dp[v]);
	}
	g[u].clear();
}
bool cmp(int x,int y) {return dfn[x]<dfn[y];}
signed main()
{
	cin>>n;
	for(int u,v,w,i=1;i<n;++i) {
		scanf("%lld%lld%lld",&u,&v,&w);
		adde(u,v,w); adde(v,u,w);
	}
	presol(1,0);
	for(int i=1;i<20;++i) for(int u=1;u<=n;++u) far[u][i]=far[far[u][i-1]][i-1];
	for(int i=1;i<20;++i) for(int u=1;u<=n;++u) ine[u][i]=min(ine[u][i-1],ine[far[u][i-1]][i-1]);

	int q,m;
	cin >> q;
	while(q --> 0)
	{
		scanf("%lld",&m);
		for(int i=1;i<=m;++i) scanf("%lld",&a[i]),key[a[i]]=1;
		sort(a+1,a+m+1,cmp);
		st[top=1] = 1;
		for(int i=1;i<=m;++i) {
			int u = a[i], v=st[top], lca=LCA(u,v);
			if(lca == v) st[++top]=u;
			else {
				int lste;
				while(dfn[st[top]] > dfn[lca]) {
					if(dfn[st[top-1]] >= dfn[lca]) {
						LCA(st[top-1],st[top]);
						g[st[top-1]].push_back((edge){st[top],mie});
					}
					lste=st[top];
					top--;
				}
				if(st[top] != lca) {
					LCA(lste,lca);
					g[lca].push_back((edge){lste,mie});
					st[++top]=lca;
				}
				st[++top]=u;
			}
		}
		while(top>1) {
			LCA(st[top-1],st[top]);
			g[st[top-1]].push_back((edge){st[top],mie});
			top--;
		}
		dfs(1);
		printf("%lld\n",dp[1]);
		for(int i=1;i<=m;++i) key[a[i]]=0;
	}
	return 0;
}