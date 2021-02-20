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
#define int long long
using namespace std;

const int N = 2e5+5, mod = 51061;
bool umin(int &x,int y) {return x>y? x=y, 1: 0; }
bool umax(int &x,int y) {return x<y? x=y, 1: 0; }

int n,q,fa[N],ch[N][2],rev_tag[N],add_tag[N],mul_tag[N];
int sum[N],siz[N],val[N];

namespace LCT {
	#define Get(x) (ch[fa[x]][1] == x)
	#define ls ch[p][0]
	#define rs ch[p][1]
	#define isRoot(x) (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x)

	int MOD(int x) { return x%mod; }
	void Pushup(int p) {
		sum[p] = MOD(val[p]+sum[ls]+sum[rs]);
		siz[p] = siz[ls] + siz[rs] + 1;
	}

	void Pushdown(int p) {
		if(rev_tag[p]) {
			rev_tag[ls] ^= 1; rev_tag[rs] ^= 1;
			swap(ch[ls][0],ch[ls][1]);
			swap(ch[rs][0],ch[rs][1]);
			rev_tag[p] ^= 1;
		}
		sum[ls] = MOD(sum[ls] * mul_tag[p] + add_tag[p] * siz[ls]);
		sum[rs] = MOD(sum[rs] * mul_tag[p] + add_tag[p] * siz[rs]);
		val[ls] = MOD(val[ls] * mul_tag[p] + add_tag[p]);
		val[rs] = MOD(val[rs] * mul_tag[p] + add_tag[p]);
		add_tag[ls] = MOD(add_tag[ls] * mul_tag[p] + add_tag[p]);
		add_tag[rs] = MOD(add_tag[rs] * mul_tag[p] + add_tag[p]);
		mul_tag[ls] = MOD(mul_tag[ls] * mul_tag[p]);
		mul_tag[rs] = MOD(mul_tag[rs] * mul_tag[p]);
		add_tag[p] = 0;
		mul_tag[p] = 1;
	}

	void Updata(int p) {
		if(!isRoot(p)) Updata(fa[p]);
		Pushdown(p);
	}

	void Rotate(int x) {
		int y = fa[x], z = fa[y], k = Get(x);
		if(!isRoot(y)) ch[z][Get(y)] = x;
		ch[y][k] = ch[x][!k]; fa[ch[x][!k]] = y;
		ch[x][!k] = y; fa[y] = x; fa[x] = z;
		Pushup(y); Pushup(x);
	}
	void Splay(int x) {
		Updata(x);
		for(int p=0; p=fa[x], !isRoot(x); Rotate(x)) {
			if(!isRoot(p)) Rotate(Get(p)==Get(x)? p: x);
		}
	}
	int Access(int x) {
		int p;
		for(p = 0; x; p = x, x = fa[x]) {
			Splay(x); 
			ch[x][1] = p; 
			Pushup(x);
		}
		return p;  // 需要返回 top
	}
	void Makeroot(int p) {
		int tp = Access(p);   // 标记要打在 tp 上！
		rev_tag[tp] ^= 1;
		swap(ch[tp][0], ch[tp][1]);
		Splay(p);
	}
	int Find(int p) {
		Access(p); Splay(p);
		while(ls) Pushdown(p), p = ls;  // 注意是 当有左儿子 是条件
		Splay(p);
		return p;
	}
	// Makeroot , Find 之后到要 Splay(p)

	bool Link(int x,int y) {
		Makeroot(x);
		if(Find(y) == x) return 0;
		fa[x] = y;
		return 1;
	}
	bool Cut(int x,int y) {
		Makeroot(x);
		if(Find(y) == x && !ch[y][0] && fa[y]==x) {
			ch[x][1] = fa[y] = 0; Pushup(x);
			return 1;
		}
		return 0;
	}
	
}
using namespace LCT;

signed main() {
	cin >> n >> q;
	for(int i=1;i<=n;++i) val[i] = sum[i] = siz[i] = mul_tag[i] = 1;

	for(int i=1,u,v;i<n;++i) {
		cin >> u >> v;
		Link(u,v);
	}

	char tp[10];
	int u,v,c;
	while(q--) {
		scanf("%s",tp);
		if(tp[0] == '+') {
			scanf("%lld%lld%lld",&u,&v,&c);
			Makeroot(u); Access(v); Splay(v);
			sum[v] = MOD(sum[v] + siz[v]*c);
			val[v] = MOD(val[v] + c);
			add_tag[v] = MOD(add_tag[v] + c);
		}
		if(tp[0] == '-') {
			scanf("%lld%lld",&u,&v); Cut(u,v);
			scanf("%lld%lld",&u,&v); Link(u,v);
		}
		if(tp[0] == '*') {
			scanf("%lld%lld%lld",&u,&v,&c);
			Makeroot(u);
			Access(v);
			Splay(v); 
			sum[v] = MOD(sum[v] * c);
			val[v] = MOD(val[v] * c);
			add_tag[v] = MOD(add_tag[v] * c);
			mul_tag[v] = MOD(mul_tag[v] * c);
		}
		if(tp[0] == '/') {
			scanf("%lld%lld",&u,&v);
			Makeroot(u); Access(v);
			Splay(v); printf("%lld\n",sum[v]);
		}
	}
	return 0;
}