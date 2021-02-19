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
#define ll long long
using namespace std;
bool umin(int &x,int y) {return y<x? x=y,1: 0;}
bool umax(int &x,int y) {return y>x? x=y,1: 0;}
const int N = 2e5+5;
int n,m,cnt=0,bac[N<<5],ch[N<<5][2],nownode=0,rt[N];
ll val[N<<5];

#define mid ((l+r)>>1)
#define ls ch[p][0]
#define rs ch[p][1]
int newnode() {return cnt? bac[cnt--]: ++nownode; }
void del(int p) {
	ls = rs = val[p] = 0;
	bac[++cnt] = p;
}
void Modify(int &p,int l,int r,int pos,int v) {
	if(!p) p = newnode();
	val[p] += v;
	if(l == r) return ;
	if(pos <= mid) Modify(ls,l,mid,pos,v);
	else Modify(rs,mid+1,r,pos,v);
}
ll Query(int p,int l,int r,int s,int e) {
	if(l > e || r < s) return 0;
	if(s <=l && r <=e) return val[p];
	return Query(ls,l,mid,s,e)+Query(rs,mid+1,r,s,e);
}
int Kth(int p,int l,int r,int k) {
	if(l == r) return l;
	if(val[ls] >= k) return Kth(ls,l,mid,k);
	else return Kth(rs,mid+1,r,k-val[ls]);
}
int Merge(int p,int y) {
	if(p*y == 0) return p+y;
	val[p] += val[y];
	ls = Merge(ls,ch[y][0]);
	rs = Merge(rs,ch[y][1]);
	del(y);
	return p;
}
void Split(int x,int &y,ll k) {  // 把 x 中的前k个元素放到 y 中
	if(!x) return ;
	y = newnode();
	ll v = val[ch[x][0]];
	if(k < v) Split(ch[x][0],ch[y][0],k);
	else swap(ch[x][0],ch[y][0]);
	if(k > v) Split(ch[x][1],ch[y][1],k-v);
	val[y] = k;
	val[x] = val[x]-k;
}
signed main()
{
	cin >> n >> m;
	memset(rt,0,sizeof(rt));
	for(int i=1,a;i<=n;++i) {
		scanf("%d",&a);
		Modify(rt[1],1,n,i,a);
	}
	int tp,p,x,y,t,q,k;
	int tot=1;
	while(m--) {
		scanf("%d",&tp);
		if(tp == 0) {
			scanf("%d%d%d",&p,&x,&y);
			int tmp = 0;
			ll k1 = Query(rt[p],1,n,1,x-1); Split(rt[p],tmp,k1);
			ll k2 = Query(rt[p],1,n,x,y); Split(rt[p],rt[++tot],k2);
			rt[p] = Merge(rt[p],tmp);
		}
		if(tp == 1) {
			scanf("%d%d",&p,&t);
			rt[p] = Merge(rt[p],rt[t]);
		}
		if(tp == 2) {
			scanf("%d%d%d",&p,&x,&q);
			Modify(rt[p],1,n,q,x);
		}
		if(tp == 3) {
			scanf("%d%d%d",&p,&x,&y);
			printf("%lld\n",Query(rt[p],1,n,x,y));
		}
		if(tp == 4) {
			scanf("%d%d",&p,&k);
			printf("%d\n",val[rt[p]]<k? -1: Kth(rt[p],1,n,k));
		}
	}
	return 0;
} 