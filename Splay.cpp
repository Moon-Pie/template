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
#define db double
using namespace std;
template <class T> bool umin(T &x,T y) {return y<x? x=y,1: 0;}
template <class T> bool umax(T &x,T y) {return y>x? x=y,1: 0;}
const int N = 1e5+5, inf = 1e9;
int n,q,a[N];

namespace Splay_Tree {
	int root,nownode;
	db val[N],mx[N],mi[N],sum1[N],sum2[N];
	int f[N],ch[N][2],siz[N],tag[N];

	#define ls ch[p][0]
	#define rs ch[p][1]
	#define Get(x) (ch[f[x]][1] == x)
	#define mid ((l+r)>>1)

	void Pushup(int p) {
		sum1[p] = val[p]; sum2[p] = val[p]*val[p];
		siz[p] = 1; mx[p] = val[p]; mi[p] = val[p];
		if(ls) umax(mx[p],mx[ls]), umin(mi[p],mi[ls]), siz[p] += siz[ls], sum1[p]+=sum1[ls],sum2[p]+=sum2[ls];
		if(rs) umax(mx[p],mx[rs]), umin(mi[p],mi[rs]), siz[p] += siz[rs], sum1[p]+=sum1[rs],sum2[p]+=sum2[rs];
	}

	void Pushdown(int p) {
		if(p && tag[p]) {
			swap(ls,rs); tag[p] = 0;
			tag[ls] ^= 1; tag[rs] ^= 1;
		}
	}

	void Rotate(int x) {
		int y = f[x], z = f[y], k = Get(x);
		Pushdown(x); Pushdown(y); 
		if(z) ch[z][Get(y)] = x;
		f[ch[x][!k]] = y; ch[y][k] = ch[x][!k];
		ch[x][!k] = y; f[y] = x; f[x] = z;
		Pushup(y); Pushup(x);
	}

	void Splay(int p,int goal) {
		for(int fa; fa=f[p], fa!=goal; Rotate(p)) {
			if(f[fa] != goal) Rotate(Get(fa)==Get(p)? fa: p);
		}
		if(!goal) root = p;
	}

	int Build(int fa,int l,int r) {
		if(l > r) return 0;
		int p = ++nownode;
		f[p] = fa; siz[p] = 1;
		ls = rs = 0;
		mx[p] = mi[p] = val[p] = a[mid];
		ls = Build(p,l,mid-1);
		rs = Build(p,mid+1,r);
		Pushup(p);
		return p;
	}

	int Find(int k) {  // 找第k大
		int p = root;
		for(;;) {
			Pushdown(p);
			if(k <= siz[ls]) p = ls;
			else {
				k -= siz[ls]+1;
				if(!k) return p;
				p = rs;
			}
		}
	}

	void Reverse(int x,int y) {
		int l = x-1, r = y+1;
		l = Find(l); r = Find(r);
		Splay(l,0); Splay(r,l);
		int p = ch[ch[l][1]][0];
		tag[p] ^= 1;
	}

}
using namespace Splay_Tree;

void dfs(int p) {
	Pushdown(p);
	if(ls) dfs(ls);
	if(val[p]!=inf && val[p]!=inf) cout << val[p] << " ";
	if(rs) dfs(rs);
}

signed main()
{
  cin >> n >> q;

  a[1] = -inf; a[n+2] = inf;
  for(int i=2;i<=n+1;++i) scanf("%d",&a[i]);

  nownode = 0;
	root = Build(0,1,n+2);

  char tp[5];
  int l,r;
  while(q--) {
      scanf("%s",tp);
      scanf("%d%d",&l,&r);
      if(tp[0] == 'r') {
      	Reverse(l+1,r+1);
      }
      else {
        if(l == r) {cout << "0.000000\n"; continue; }

        db tot = r-l+1;
        l++; r++;
        l = Find(l-1); r = Find(r+1);
        Splay(l,0); Splay(r,l);
        int p = ch[ch[l][1]][0];

        db s=sum1[p];
        db MX=mx[p],MI=mi[p];

        db dlt1 = 1.0*(tot*MX - s)/(1-tot);
        db dlt2 = 1.0*(tot*MI - s)/(1-tot);

        db avr1 = MX+dlt1, avr2 = MI+dlt2;
        db f1 = 0, f2 = 0;

        f1 = sum2[p]-2.0*avr1*sum1[p]+tot*avr1*avr1;
        f1 -= (MX-avr1)*(MX-avr1);

        f2 = sum2[p]-2.0*avr2*sum1[p]+tot*avr2*avr2;
        f2 -= (MI-avr2)*(MI-avr2);

        if(f1 < f2) printf("%0.6lf\n",f1/tot);
        else printf("%0.6lf\n",f2/tot);
      }
  }
  return 0;
}