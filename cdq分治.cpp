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
using namespace std;
template <class T> bool umin(T &x,T y) {return y<x? x=y,1: 0;}
template <class T> bool umax(T &x,T y) {return y>x? x=y,1: 0;}
const int N = 2e5+5;
int n,k,f[N],ans[N];
struct node {int a,b,c,w,ans; }t[N],e[N];
bool cmp1(node x,node y) {return (x.a!=y.a)? x.a < y.a: x.b!=y.b? x.b<y.b: x.c<y.c; }
bool cmp2(node x,node y) {return (x.b!=y.b)? x.b < y.b: x.c<y.c; }

struct trarr
{
	int a[N];
	void Modify(int x,int v) {
		for(;x<=k;x+=x&-x) a[x] += v;
	}
	int Query(int x) {
		int res = 0;
		for(;x;x-=x&-x) res += a[x];
		return res;
	}
}T;

void Solve(int l,int r) {
	if(l == r) return ;
	int mid = (l+r)>>1;
	Solve(l,mid);
	Solve(mid+1,r);

	sort(e+l,e+mid+1,cmp2);
	sort(e+mid+1,e+r+1,cmp2);

	int j = l;
	for(int i=mid+1;i<=r;++i) {
		while(j <= mid && e[j].b <= e[i].b) {
			T.Modify(e[j].c,e[j].w);
			++j;
		}
		e[i].ans += T.Query(e[i].c);
	}
	for(int i = l; i < j; ++i) T.Modify(e[i].c,-e[i].w);

}

signed main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k;

	for(int i=1;i<=n;++i) cin >> t[i].a >> t[i].b >> t[i].c;
	sort(t+1,t+n+1,cmp1);

	int tot = 0, w = 0;
	for(int i=1;i<=n;++i) {
		w++;
		if(t[i].a!=t[i+1].a || t[i].b!=t[i+1].b || t[i].c!=t[i+1].c)
			e[++tot] = t[i], e[tot].w = w, w = 0;
	}
	int tmp = n;
	n = tot;

	Solve(1,n);
	for(int i=1;i<=n;++i) {
		f[e[i].ans+e[i].w-1] += e[i].w;
	}
	for(int i=0;i<tmp;++i) cout << f[i] << "\n";

	return 0;
}