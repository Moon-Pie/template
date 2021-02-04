#include <bits/stdc++.h>
#define P pair<int , int>
#define fi first
#define se second
using namespace std;
template <class T> void read(T &x){x=0; char c=getchar(); int f=0;while (c<'0'||c>'9') f|=(c=='-'),c=getchar();while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();if (f) x=-x;}
const int N = 2e5+5;
int n , m , root[N] , nowroot , nownode , ans;
struct node
{
	int ls , rs , f , s;
}tr[N*40];
void deal(int &x)
{
	x = (x ^ ans);
}
#define mid (l+r>>1)
#define lc tr[now].ls
#define rc tr[now].rs

int newnode()
{
	return ++nownode;
}

void build(int now , int l , int r)
{
	if(l > r) return;
	if(l == r)
	{
		tr[now].f = l;
		tr[now].s = 1;
		return ;
	}
	tr[now].ls = newnode();
	tr[now].rs = newnode();
	build(lc , l , mid);
	build(rc ,mid+1, r);
}

P que(int now , int l , int r , int pos)
{
	if(l == r) 
	{
		return P(tr[now].f , tr[now].s);
	}
	if(pos <= mid) 
	{
		return que(lc , l , mid , pos);
	}
	else 
	{
		return que(rc , mid+1 , r , pos);
	}
}

void mdf1(int his , int now , int l , int r , int pos , int val)  // change father
{
	if(l == r)
	{
		tr[now].f = val;
		tr[now].s = tr[his].s;
		return ;
	}
	if(pos <= mid) 
	{
		tr[now].ls = newnode();
		tr[now].rs = tr[his].rs;
		mdf1(tr[his].ls , lc , l , mid , pos , val);
	}
	else
	{
		tr[now].rs = newnode();
		tr[now].ls = tr[his].ls;
		mdf1(tr[his].rs , rc , mid+1 , r , pos , val);
	}
}

void mdf2(int his , int now , int l , int r , int pos , int val)  // change size
{
	if(l == r)
	{
		tr[now].s = tr[his].s + val;
		tr[now].f = tr[his].f;
		return ;
	}
	if(pos <= mid) 
	{
		tr[now].ls = newnode();
		tr[now].rs = tr[his].rs;
		mdf2(tr[his].ls , lc , l , mid , pos , val);
	}
	else 
	{
		tr[now].rs = newnode();
		tr[now].ls = tr[his].ls;
		mdf2(tr[his].rs , rc , mid+1 , r , pos , val);
	}
}

P getf(int root , int x)
{
	P fx = que(root , 1 , n , x);
	if(fx.fi == x) return fx;
	return getf(root , fx.fi);
}

int main()
{
	cin >> n >> m;

	nownode = 0;
	build(0 , 1 , n);
	nowroot = 0;

	int op , a , b , k;
	ans = 0;
	for(int i = 1; i <= m; ++i)
	{
		read(op);
		if(op == 1)
		{
			read(a); read(b);
			// deal(a); deal(b);
			root[i] = newnode();
			P A = getf(nowroot , a);
			P B = getf(nowroot , b);
			if(A.se < B.se)
			{
				mdf1(nowroot , root[i] , 1 , n , A.fi , B.fi);
				nowroot = root[i];
				root[i] = newnode();
				mdf2(nowroot , root[i] , 1 , n , B.fi , A.se);
			}
			else 
			{
				mdf1(nowroot , root[i] , 1 , n , B.fi , A.fi);
				nowroot = root[i];
				root[i] = newnode();
				mdf2(nowroot , root[i] , 1 , n , A.fi , B.se);
			}
			nowroot = root[i];
		}
		if(op == 2)
		{
			read(k);
			// deal(k);
			nowroot = root[k];
			root[i] = root[k];
		}
		if(op == 3)
		{
			read(a); read(b);
			// deal(a); deal(b);
			P A = getf(nowroot , a);
			P B = getf(nowroot , b);
			ans = (A.fi == B.fi);
			printf("%d\n",ans);
			root[i] = root[i-1];
		}

	}

	return 0;
}