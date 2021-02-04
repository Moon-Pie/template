#include <stdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
int n , m , root[N] , nowroot=0;
struct node
{
	int ls,rs,val;
};
int newnode()
{
	return ++nownode;
}
#define mid (l+r>>1)
#define lc tr[now].ls
#define rc tr[now].rs

void mdf(int now,int l,int r,int pos,int val)
{
	if(l == r)
	{
		tr[now].val+=val;
		return ;
	}
	if(pos <= mid) mdf(lc , l , mid , pos , val);
	else mdf(rc , mid+1 , r , pos , val);
}

void mrg(int x,int y)
int main()
{
	cin >> n >> m;
	for(int x, i = 1; i <= n; ++i)
	{
		scanf("%d",&x);
		mdf(root[1] , 1 , n , i , x);
	}

	int op , p , x , y , t , q , k;
	for(int o = 1; o <= m; ++o)
	{
		scanf("%d",&op);
		if(op == 0)
		{
			scanf("%d%d%d",&p,&x,&y);

		}
		if(op == 1)
		{
			scanf("%d%d",&p,&t);
			mrg(p,t);
		}
		if(op == 2)
		{
			scanf("%d%d%d",&p,&x,&q);

		}
		if(op == 3)
		{
			scanf("%d%d%d",&p,&x,&y);

		}
		if(op == 4)
		{
			scanf("%d%d",&p,&k);

		}
	}
	return 0;
}