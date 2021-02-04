#include <bits/stdc++.h>
using namespace std;
#define P pair<int,int>
#define fi first
#define se second
template <class T> bool checkmax(T &a,T b) {return b > a ? a = b , 1 : 0;}
template <class T> bool checkmin(T &a,T b) {return b < a ? a = b , 1 : 0;}
const int mod = 1e9 + 7;
template <class T> void my_add(T &a,T b) {b %= mod; a = a + b > mod ? a + b - mod : a + b;}
template <class T> void my_sub(T &a,T b) {b %= mod; a = a - b < 0 ? a - b + mod : a - b;}
const int N=3e6+5;
const double pi = acos(-1);
int n,m,inv[N];
// char A[N],B[N];
struct com
{
	com(double xx=0, double yy=0) {x=xx,y=yy;}
	double x,y;
	com operator+(com const &o) const 
	{ return com(x+o.x, y+o.y); }
	com operator-(com const &o) const
	{ return com(x-o.x, y-o.y); }
	com operator*(com const &o) const 
	{ return com(x*o.x-y*o.y, x*o.y+o.x*y); }
}a[N],b[N],f[N];

void fft(com *f,int flag) {
	for(int i=0;i<n;++i) if(inv[i] > i) swap(f[i],f[inv[i]]);

	for(int p=2;p<=n;p<<=1) {
		int len = (p>>1);
		com bas(cos(pi*2/p), sin(pi*2/p)*flag);

		for(int i=0;i<n;i+=p) {
			com now(1,0);
			for(int j=i;j<i+len;++j) {
				com tt = f[j+len]*now;
				f[j+len] = f[j]-tt;
				f[j] = f[j]+tt;
				now = now*bas;
			}
		}
	}
}

#define mod 998244353
#define g 3
int qpow(int x,int y) {
	int res=1;
	for(int i=0;(1<<i)<=y;x=1ll*x*x%mod,++i) if(y&(1<<i)) res=1ll*res*x%mod;
	return res;
}
int INV=qpow(g,mod-2);
void ntt(int *f,int flag) {
	for(int i=0;i<n;++i) if(inv[i] > i) swap(f[inv[i]],f[i]);

	for(int p=2,len;p<=n;p<<=1) {
		len = p>>1;
		int bas = qpow(flag==1?g:INV,(mod-1)/p);
		for(int i=0;i<n;i+=p) {
			int now = 1;
			for(int j=i;j<i+len;++j) {
				int t = 1ll*f[j+len]*now%mod;
				f[j+len] = f[j]-t<0? f[j]-t+mod: f[j]-t;
				f[j] = f[j]+t>mod? f[j]+t-mod: f[j]+t;
				now = 1ll*now*bas%mod;
			}
		}
	}

	if(flag==-1) {
		int invn = qpow(n,mod-2);
		for(int i=0;i<n;++i) f[i] = 1ll*f[i]*invn%mod;
	}
}

signed main()
{
	cin >> n >> m;

	for(int i=0;i<=n;++i) scanf("%lf",&a[i].x);
	for(int i=0;i<=m;++i) scanf("%lf",&b[i].x);

	for(m=m+n,n=1;n<=m;n<<=1);

	for(int i=0;i<n;++i) inv[i]=(inv[i>>1]>>1)|((i&1)?n>>1:0);

	fft(a,1); fft(b,1);
	for(int i=0;i<n;++i) f[i] = a[i]*b[i];
	fft(f,-1);

	for(int i=0;i<=m;++i) printf("%d ",(int)(f[i].x/n+0.49));
	printf("\n");

	return 0;
}