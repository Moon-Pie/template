#include <bits/stdc++.h>
using namespace std;
const int N=5e3+5,M=5e4+4,inf=1e9;
int n,m,s,t,iu[M],iv[M],iw[M],ic[M];
struct edge{ int to,cap,cost,rev; };
vector<edge> g[N];

void add(int u,int v,int w,int c)
{
	g[u].push_back((edge){v,w,c,(int)g[v].size()});
	g[v].push_back((edge){u,0,-c,(int)g[u].size()-1});
}

void init()
{
	for(int i=1;i<=n;++i) g[i].clear();
	for(int i=1;i<=m;++i) add(iu[i],iv[i],iw[i],ic[i]);
}

int lev[N],itr[N];
void bfs()
{
	queue<int> Q;
	memset(lev,-1,sizeof(lev));
	lev[s] = 0;  Q.push(s);
	while(!Q.empty())
	{
		int u=Q.front(); Q.pop();
		for(int i=0;i<(int)g[u].size();++i)
		{
			int v=g[u][i].to;
			if(g[u][i].cap && lev[v]<0)
			{
				lev[v] = lev[u]+1;
				Q.push(v);
			}
		}
	}
}

int dfs(int u,int f)
{
	if(u==t) return f;
	for(int &i=itr[u];i<(int)g[u].size();++i)
	{
		int v=g[u][i].to, r=g[u][i].rev;
		if(lev[v] > lev[u] && g[u][i].cap)
		{
			int d = dfs(v,min(f,g[u][i].cap));
			if(d)
			{
				g[u][i].cap -= d;
				g[v][r].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow()
{
	int flow=0;
	for(;;)
	{
		bfs();
		if(lev[t] < 0) return flow;
		memset(itr,0,sizeof(itr));

		int f = dfs(s,inf);
		while(f)
		{
			flow += f;
			f = dfs(s,inf);
		}
	}
}

int dis[N],vis[N],prv[N],pre[N],cnt[N];
int min_cost_flow(int f)
{
	int flow = 0;

	while(f)
	{
		queue<int> Q;
		memset(dis,0x3f,sizeof(dis));
		memset(vis,0,sizeof(vis));

		dis[s] = 0;
		Q.push(s); vis[s]=1;
		while(!Q.empty())
		{	
			int u = Q.front(); Q.pop(); vis[u] = 0;
			for(int i=0;i<(int)g[u].size();++i)
			{
				int v = g[u][i].to;

				if(g[u][i].cap>0 && dis[v] > dis[u]+g[u][i].cost)
				{
					dis[v] = dis[u]+g[u][i].cost;
					prv[v]=u; pre[v]=i;
					if(!vis[v])
					{
						vis[v]=1;
						Q.push(v);
					}
				}
			}
		}
		int d=inf;
		for(int u=t; u!=s; u=prv[u]) d=min(d,g[prv[u]][pre[u]].cap);
		f -= d;
		flow += d*dis[t];
		for(int u=t; u!=s; u=prv[u])
		{
			int r = g[prv[u]][pre[u]].rev;
			g[prv[u]][pre[u]].cap -= d;
			g[u][r].cap += d;
		}
	}
	return flow;
}

int main()
{
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;++i) scanf("%d%d%d%d",&iu[i],&iv[i],&iw[i],&ic[i]);
	init(); int F = max_flow(); init();
	cout << F << " " << min_cost_flow(F) << endl;
	return 0;
}