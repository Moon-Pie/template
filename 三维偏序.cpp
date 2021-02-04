#include <cstdio>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,a[N],pos[N],tot=0,tr[N],ans[N];
struct node
{
	int s,T,P,V;
	bool operator < (const node &o) const{
		return P < o.P;
	}
}e[N*2];
void add(int x,int v) {for(;x<=n;x+=x&-x) tr[x]+=v;}
int que(int x)
{
	int res=0;
	for(;x;x-=x&-x) res+=tr[x];
	return res;
}

/*
需要 Ti < Tj  Pi < Pj && Vi > Vj
或者 Ti < Tj  Pi > Pj && Vi < Vj
*/
void solve(int l,int r)
{
	if(l == r) return;

	int mid = l+r>>1 , j;
	
	solve(l,mid); 
	solve(mid+1,r);
	
	sort(e+l,e+mid+1);
	sort(e+mid+1,e+r+1);

	j = l;
	for(int i = mid+1; i <= r; ++i)
	{
		while(e[j].P < e[i].P && j <= mid) 
		{
			add(e[j].V , e[j].s);
			++j;
		}
		ans[e[i].T] += e[i].s * (que(n) - que(e[i].V));
	}

	for(int i = l; i < j; ++i) add(e[i].V , -e[i].s);

	j = mid;
	for(int i = r; i >= mid+1; --i)
	{
		while(e[j].P > e[i].P && j >= l)
		{
			add(e[j].V , e[j].s);
			--j;
		}
		ans[e[i].T] += e[i].s * que(e[i].V-1);
	}
	for(int i = mid; i > j; --i) add(e[i].V , -e[i].s);

}

main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i) 
	{
		scanf("%lld",&a[i]);
		pos[a[i]]=i;
		e[++tot]={1,0,i,a[i]};
	}
	for(int x,i=1;i<=m;++i)
	{
		scanf("%lld",&x);
		e[++tot]={-1,i,pos[x],x};
	}

	solve(1,tot);

	for(int i = 1; i <= m; ++i) ans[i] += ans[i-1];

	for(int i = 0; i < m; ++i) printf("%lld\n",ans[i]);

	return 0;
}