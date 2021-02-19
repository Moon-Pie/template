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
int n,m,uk,block,a[N],x[N],pos[N],Ans[N];
struct Query {
	int l,r,id; 
	bool operator<(const Query &o) const {
		return pos[l]==pos[o.l]? r<o.r: pos[l]<pos[o.l]; 
	}
}q[N];
int L[N],R[N],cl[N],Rt[N];
int calc(int l,int r) {
	int res = 0;
	for(int i=l;i<=r;++i) Rt[a[i]] = 0;
	for(int i=l;i<=r;++i) {
		if(Rt[a[i]]) res = max(res, i-Rt[a[i]]);
		else Rt[a[i]] = i;
	}
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	block = sqrt(n);
	for(int i=1;i<=n;++i) {
		cin >> x[i];
		a[i] = x[i];
		pos[i] = 1+(i-1)/block;
	}
	sort(x+1,x+n+1);
	uk = unique(x+1,x+n+1)-x-1;
	for(int i=1;i<=n;++i) a[i] = lower_bound(x+1,x+uk+1,a[i])-x;
	cin >> m;
	for(int i=1;i<=m;++i) {
		q[i].id = i;
		cin >> q[i].l >> q[i].r;
	}
	sort(q+1,q+m+1);

	for(int i=1,j=1;j<=pos[n];++j) {
		int br = min(n,j*block),l=br+1,r=l-1,ans=0;
		int cnt = 0;
		for(; pos[q[i].l]==j ;++i) {
			if(pos[q[i].r] == j) {
				Ans[q[i].id] = calc(q[i].l,q[i].r);
				continue;
			}
			while(r < q[i].r) {
				++r;
				R[a[r]] = r;
				if(!L[a[r]]) L[a[r]] = r, cl[++cnt] = a[r];
				ans = max(ans,r-L[a[r]]);
			}
			int tmp = ans;
			while(l > q[i].l) {
				--l;
				if(R[a[l]]) ans = max(ans, R[a[l]]-l);
				else R[a[l]] = l;
			}
			Ans[q[i].id] = ans;
			while(l <= br) {
				if(R[a[l]] == l) R[a[l]] = 0;
				++l;
			}
			ans = tmp;
		}
		for(int k=1;k<=cnt;++k) L[cl[k]] = R[cl[k]] = 0;
	}

	for(int i=1;i<=m;++i) cout << Ans[i] << "\n";

	return 0;
}