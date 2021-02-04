#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005,inf=1e9;
int n,m,s,t,itr[N],lev[N];
struct edge {int to,cap,rev; };
vector<edge> g[N];
bool vis[N];

void add(int u,int v,int w)
{
	g[u].push_back((edge){v,w,(int)g[v].size()});
	g[v].push_back((edge){u,0,(int)g[u].size()-1});
}

void bfs()
{
	memset(lev,-1,sizeof(lev));
	queue<int> Q;
	Q.push(s);
	lev[s]=0;
	while(!Q.empty())
	{
		int u = Q.front(); Q.pop();
		for(int i=0;i<g[u].size();++i)
		{
			int v = g[u][i].to;
			if(lev[v] < 0 && g[u][i].cap)
			{
				lev[v] = lev[u]+1;
				Q.push(v);
			}
		}
	}
}

int dfs(int u,int f)
{
	if(u == t) return f;
	for(int &i=itr[u];i<g[u].size();++i)
	{
		int v = g[u][i].to, r = g[u][i].rev;
		if(lev[v]>lev[u] && g[u][i].cap)
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

int Max_flow()
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

main()
{
	cin >> n >> m >> s >> t;
	for(int u,v,w,i=1;i<=m;++i)
	{
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);
	}
	cout << Max_flow() << endl;
	return 0;
}