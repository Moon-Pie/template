#include <bits/stdc++.h>
using namespace std;
template <class T> void read(T &x){x=0; char c=getchar(); int f=0;while (c<'0'||c>'9') f|=(c=='-'),c=getchar();while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();if (f) x=-x;}
const int N = 2e5+5;
int n , m , a[N] , X[N] , nownode=0 , root[N];
struct node
{
	int ls , rs , v;
}tr[N*18];

int newnode()
{
	return ++nownode;
}

#define mid (l+r>>1)
#define lc tr[now].ls
#define rc tr[now].rs

void build(int p , int l , int r)
{
	if(l > r) return ;
	if(l == r)
	{
		tr[p].v = 0;
		return ;
	}
	tr[p].ls = newnode();
	tr[p].rs = newnode();
	build(tr[p].ls , l , mid);
	build(tr[p].rs ,mid+1, r);
	tr[p].v = tr[tr[p].ls].v + tr[tr[p].rs].v;
}

void mdf(int his , int now , int l , int r , int pos , int val)
{
	if(l == r)
	{
		tr[now].v = tr[his].v + val;
		return ;
	}
	if(pos <= mid)
	{
		tr[now].rs = tr[his].rs;
		tr[now].ls = newnode();
		mdf(tr[his].ls , lc , l , mid , pos , val);
	}
	else 
	{
		tr[now].ls = tr[his].ls;
		tr[now].rs = newnode();
		mdf(tr[his].rs , rc ,mid+1, r , pos , val);
	}
	tr[now].v = tr[lc].v + tr[rc].v;
}

int que(int his , int now , int l , int r , int k)
{
	if(l == r)
	{
		return X[l];
	}

	if(tr[lc].v - tr[tr[his].ls].v < k)
	{
		return que(tr[his].rs , rc ,mid+1, r , k - (tr[lc].v - tr[tr[his].ls].v));
	}
	else
	{
		return que(tr[his].ls , lc , l , mid , k);
	}
}

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; ++i)
	{
		read(a[i]);
		X[i] = a[i];
	}

	sort(X+1,X+n+1);
	int ht = unique(X+1,X+n+1)-X-1;

	for(int i = 1; i <= n; ++i)
	{
		a[i] = lower_bound(X+1,X+ht+1,a[i]) - X;
 	}

 	root[0] = 0;
 	build(0,1,ht);

 	for(int i = 1; i <= n; ++i)
 	{
 		root[i] = newnode();
 		mdf(root[i-1] , root[i] , 1 , ht , a[i] , 1);
 	}

 	int l , r , k;
 	while(m --> 0)
 	{
 		read(l); read(r); read(k);
 		printf("%d\n" , que(root[l-1] , root[r] , 1 , ht , k) );
 	}

	return 0;
}