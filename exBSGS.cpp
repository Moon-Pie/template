#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18;
int a,p,b;
void exgcd(int a,int b,int &x,int &y) {
	if(!b) {
		x=1;y=0;
	}
	else {
		exgcd(b,a%b,x,y);
		x -= a/b*y;
		swap(x,y);
	}
}
int inv(int x,int p) 
{
	int xx,yy;
	exgcd(x,p,xx,yy);
	return (xx%p+p)%p;
}
int BSGS(int a,int b,int p)
{
	int T=0;
	while(T*T<=p) ++T;
	map<int,int> mp;
	int f=1;
	for(int i=0;i<T;++i) {
		if(f==b) return i;
		mp[1ll*b*inv(f,p)%p]=i;
		f=1ll*f*a%p;
	}
	int bas=f;
	for(int i=1;i<=T;++i) {
		if(mp[f]) return i*T+mp[f];
		f=1ll*f*bas%p;
	}
	return -inf;
}
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
int exBSGS(int a,int p,int b)
{
	if(b==1 || p==1) return 0;
	int g = gcd(a,p),res=0,m=1;
	while(g > 1) {
		if(b%g!=0) return -inf;
		res++; b/=g; p/=g; m=m*(a/g)%p;
		if(m==b) return res;
		g = gcd(a,p);
	}
	int bs=BSGS(a,b*inv(m,p)%p,p);
	if(bs < 0) return -inf;
	return bs+res;
}
signed main()
{
	while(scanf("%lld%lld%lld",&a,&p,&b)) {
		if(!a && !p && !b) break;
		int res=exBSGS(a,p,b);
		if(res>=0) printf("%lld\n",res);
		else printf("No Solution\n");
	}
	return 0;
}