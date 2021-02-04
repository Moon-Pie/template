#include <bits/stdc++.h>
using namespace std;;
template <class T> void read(T &x){x=0; char c=getchar(); int f=0;while (c<'0'||c>'9') f|=(c=='-'),c=getchar();while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();if (f) x=-x;}
const int N = 1e6+5;
int n , m , a[N] , cntnode=0 , root[N];
struct node
{
	int ls , rs , v;
}tr[N*20];

int newnode()
{
	return ++cntnode;
}

#define mid (l+r>>1)
#define lc tr[p].ls
#define rc tr[p].rs

void build(int p, int l, int r)
{
	if(l > r) return ;
	if(l==r)
	{
		tr[p].v = a[l];
		return ;
	}
	tr[p].ls = newnode();
	tr[p].rs = newnode();
	build(lc,l,mid);
	build(rc,mid+1,r);
}

void mdf(int his , int now , int l , int r , int pos , int val)
{
	if(l == r) 
	{
		tr[now].v = val;
		return;
	}
	if(pos <= mid)
	{
		tr[now].rs = tr[his].rs;
		tr[now].ls = newnode();
		mdf(tr[his].ls , tr[now].ls , l , mid , pos , val);
 	}
	else 
	{
		tr[now].ls = tr[his].ls;
		tr[now].rs = newnode();
		mdf(tr[his].rs , tr[now].rs ,mid+1, r , pos , val);
	}
}

int que(int p , int l , int r , int pos)
{
	if(l == r)
	{
		return tr[p].v;
	}
	if(pos <= mid) return que(lc , l , mid , pos);
	else return que(rc , mid+1 , r , pos);
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		read(a[i]);
	}

	root[0] = 0;
	build(root[0],1,n);

	int v,op,loc,val;
	int now = 1;
	while (m --> 0)
	{
		scanf("%d%d",&v,&op);
		if(op == 1)
		{
			scanf("%d%d",&loc,&val);
			root[now] = newnode();
			mdf(root[v] , root[now] , 1 , n , loc , val);
			now++;
		}
		if(op == 2)
		{
			scanf("%d",&loc);
			printf("%d\n",que(root[v] , 1 , n , loc));
			root[now] = root[v];
			now++;
		}
	}
	return 0;
}