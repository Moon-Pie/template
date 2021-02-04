#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,pnt[N*2],nxt[N*2],head[N],E=0;
int far[N][20],dep[N],siz[N],son[N],L[N],R[N],a[N],tst=0;
vector<int> dl[N],ad[N];
void add(int u,int v) {pnt[++E]=v;nxt[E]=head[u];head[u]=E;}
void prp(int u,int fa)
{
	L[u]=++tst;
	a[tst]=u;
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=pnt[i];
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		far[v][0]=u;
		prp(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
	R[u]=tst;
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	int dlt=dep[u]-dep[v];
	for(int i=19;i>=0;--i) if(dlt&(1<<i)) u=far[u][i];
	if(u==v) return u;
	for(int i=19;i>=0;--i) if(far[u][i]!=far[v][i]) u=far[u][i],v=far[v][i];
	return far[u][0];
}

set<int> s[N];
int cnt[N],tim[N],Mx,ans[N];
// s[i] 出现i次的颜色们
// cnt[i] 出现i次颜色数
// tim[i] 颜色i出现次数
// Mx 出现次数最多的颜色
void upd(int u)
{
	for(int i=0;i<ad[u].size();++i)
	{
		int x=ad[u][i];
		int t=tim[x];
		tim[x]++;
		cnt[t+1]++;
		cnt[t]--;
		s[t].erase(x);
		s[t+1].insert(x);
		if(tim[x]>tim[Mx]||(tim[x]==tim[Mx]&&x<Mx)) Mx=x;
	}
	for(int i=0;i<dl[u].size();++i)
	{
		int x=dl[u][i];
		int t=tim[x];
		tim[x]--;
		cnt[t-1]++;
		cnt[t]--;
		s[t].erase(x);
		s[t-1].insert(x);
		if(Mx==x) Mx=cnt[t]? *s[t].begin(): *s[t-1].begin();
	}
}
void dfs(int u,int fa,int keep)
{
	static int vis[N],Tim;

	for(int i=head[u];i;i=nxt[i])
	{
		int v=pnt[i]; if(v==fa||v==son[u]) continue;
		dfs(v,u,0);
	}
	if(son[u]) dfs(son[u],u,1);

	for(int i=head[u];i;i=nxt[i])
	{
		int v=pnt[i]; if(v==fa||v==son[u]) continue;
		for(int i=R[v];i>=L[v];--i)
		{
			upd(a[i]);
		}
	}
	upd(u);
	ans[u]=tim[Mx]? Mx: 0;

	if(!keep)
	{
		Tim++;
		for(int i=L[u];i<=R[u];++i) 
		{
			int v=a[i];
			for(int j=0;j<dl[v].size();++j)
			{
				int x=dl[v][j];
				if(vis[x]!=Tim) 
				{
					vis[x]=Tim;
					cnt[tim[x]]--;
					cnt[0]++;
					s[tim[x]].erase(x);
					s[0].insert(x);
					tim[x]=0;
				}
			}
			for(int j=0;j<ad[v].size();++j)
			{
				int x=ad[v][j];
				if(vis[x]!=Tim) 
				{
					vis[x]=Tim;
					cnt[tim[x]]--;
					cnt[0]++;
					s[tim[x]].erase(x);
					s[0].insert(x);
					tim[x]=0;
				}
			}
		}		
	}
}
int main()
{
	cin >> n >> m;
	for(int i=2,u,v;i<=n;++i)
	{
		scanf("%d%d",&u,&v);
		add(u,v); add(v,u);
	}
	prp(1,0);
	for(int i=1;i<20;++i) for(int u=1;u<=n;++u) far[u][i]=far[far[u][i-1]][i-1];

	for(int i=1,u,v,w;i<=m;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		int lca=LCA(u,v);
		ad[u].push_back(w);
		ad[v].push_back(w);
		dl[lca].push_back(w);
		dl[far[lca][0]].push_back(w);
	}

	Mx=0; cnt[0]=n; for(int i=1;i<=n;++i) {s[0].insert(i);tim[i]=0;}
	dfs(1,0,1);
	for(int i=1;i<=n;++i) printf("%d\n",ans[i]);

	return 0;
}