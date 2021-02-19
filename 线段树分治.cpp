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
const int N = 2e5+5;
int n,m,k;
struct node {
	vector<P> tag; 
}tr[N*4];

#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
void Modify(int p,int l,int r,int s,int e,P edge) {
	if(l > e || r < s || l > r) return ;
	if(s <=l && r <=e) {
		tr[p].tag.push_back(edge);
		return ;
	}
	Modify(ls,l,mid,s,e,edge);
	Modify(rs,mid+1,r,s,e,edge);
}

int fro[N*40], top=0;
struct DS
{
	int far[N*2],siz[N*2];
	void Init(int n) { for(int i=1; i<=n; ++i) far[i] = i, siz[i] = 1; }
	int getf(int x) { return far[x]==x? x: getf(far[x]); }
	void Link(int x,int y) {
		if(siz[x] > siz[y]) swap(x,y);
		fro[++top] = x;
		far[x] = y; siz[y] += siz[x];
	}
	bool Merge(int x,int y) {
		int x0 = getf(x*2), x1 = getf(x*2-1);
		int y0 = getf(y*2), y1 = getf(y*2-1);
		if(x0 == y0 || x1 == y1) return 0;
		Link(x0,y1); Link(x1,y0);
		return 1;
	}
}D;

int ans[N];
void Solve(int p,int l,int r,int tp) {
	if(l > r) return ;

	int L = top+1;
	for(int i=0;i<(int)tr[p].tag.size();++i) {
		int x = tr[p].tag[i].fi;
		int y = tr[p].tag[i].se;
		tp &= D.Merge(x,y);
	}
	int R = top;

	if(l == r) ans[l+1] = tp;
	else {
		Solve(ls,l,mid,tp);
		Solve(rs,mid+1,r,tp);
	}

	for(int i=R; i>=L; --i) {
		int S = D.siz[fro[i]];
		for(int u = fro[i]; D.far[u]!=u; u = D.far[u]) {
			D.siz[D.far[u]] -= S;
		}
		D.far[fro[i]] = fro[i];
	}

}

signed main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	for(int i=1,x,y,l,r;i<=m;++i) {
		cin >> x >> y >> l >> r;
		Modify(1,0,k-1,l,r-1,P(x,y));	
	}

	D.Init(2*n);
	Solve(1,0,k-1,1);

	for(int i=1;i<=k;++i) puts(ans[i]?"Yes":"No");
	return 0;
}