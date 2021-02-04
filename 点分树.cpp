#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,w[N],pnt[N*2],nxt[N*2],head[N],E=0;
int siz[N],S,root,vis[N],far[N],dep[N],dis[N][20];
void adde(int u,int v) {pnt[++E]=v;nxt[E]=head[u];head[u]=E;}
void find_g(int u,int fa) {
	int ok=1;
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i]) {
		int v=pnt[i]; if(v==fa || vis[v]) continue;
		find_g(v,u);
		siz[u]+=siz[v];
		if(siz[v] > S/2) ok=0;
	}
	if(S-siz[u] > S/2) ok=0;
	if(ok) root=u;  
}

struct tr_arr
{
	int si;
	vector<int> a[2];
	void init(int s) {
		a[0].resize(s+2,0); 
		a[1].resize(s+2,0); 
		si=s+2;
	}
	void addn(int x,int v,int op) {
		x++;
		if(x>0) for(;x<si;x+=x&-x) a[op][x]+=v;
	}
	int askn(int x,int op) {
		int res=0;
		x++;
		if(x>0) for(x=min(x,si-1);x;x-=x&-x) res+=a[op][x];
		return res;
	}
}tr[N];

void get_chain(int u,int fa,int len,int ori,int fro) {
	tr[ori].addn(len,w[u],0);
	tr[fro].addn(len,w[u],1);
	dis[u][dep[ori]] = len;
	for(int i=head[u];i;i=nxt[i]) {
		int v=pnt[i]; if(v==fa || vis[v]) continue;
		get_chain(v,u,len+1,ori,fro);
	}
}

void pdiv(int u) {
	vis[u]=1;
	find_g(u,0);
	tr[u].addn(0,w[u],0);
	for(int i=head[u];i;i=nxt[i]) {
		int v=pnt[i]; if(vis[v]) continue;
		S = siz[v]; find_g(v,u);
		tr[root].init(S);
		get_chain(v,u,1,u,root);
		far[root]=u;
		dep[root]=dep[u]+1;
	}
	for(int i=head[u];i;i=nxt[i]) {
		int v=pnt[i]; if(vis[v]) continue;
		S = siz[v]; find_g(v,u);		
		pdiv(root);
	}
}

signed main()
{
	cin >> n >> m;
	for(int i=1;i<=n;++i) scanf("%d",&w[i]);
	for(int i=1,u,v;i<n;++i) {
		scanf("%d%d",&u,&v);
		adde(u,v); adde(v,u);
	}

	S=n; find_g(1,0);
	tr[root].init(S);
	pdiv(root);

	int op,x,y,lst=0;
	while(m --> 0) {
		scanf("%d%d%d",&op,&x,&y);
		x=x^lst; y=y^lst;
		if(op == 0) {
			int res=0;
			for(int f=x;f;f=far[f]) {
				res += tr[f].askn(y-dis[x][dep[f]],0);
				if(far[f]) res -= tr[f].askn(y-dis[x][dep[f]-1],1);
			}
			lst=res;
			printf("%d\n",res);
		}
		else {
			int dlt = y-w[x];
			w[x] = y;
			for(int f=x;f;f=far[f]) {
				tr[f].addn(dis[x][dep[f]],dlt,0);
				if(far[f]) tr[f].addn(dis[x][dep[f]-1],dlt,1);
			}
		}
	}

	return 0;
}