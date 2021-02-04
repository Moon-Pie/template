#include <bits/stdc++.h>

#define ll long long
using namespace std;

#define line cerr<<"--------------------\n"
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" ";cerr<<endl;

const int mod = 167772161, G = 3, MAXN = 2e6;
int qpow(int x,int y) {
	int res = 1;
	for(int i=0;(1<<i)<=y;++i,x=1ll*x*x%mod) if(y&(1<<i)) res = 1ll*res*x%mod;
	return res;
}
int I = qpow(G,mod-2), rev[MAXN];
void NTT(int f[],int n,int flag) {
	for(int i=0;i<n;++i) if(rev[i] > i) swap(f[i],f[rev[i]]);
	for(int p=2,len;p<=n;p<<=1) {
		len = p>>1;
		int bas = qpow(flag==1?G:I,(mod-1)/p);
		for(int i=0;i<n;i+=p) {
			int now = 1;
			for(int j=i;j<i+len;++j) {
				int t = 1ll*f[j+len]*now%mod;
				f[j+len] = f[j]-t<0? f[j]-t+mod: f[j]-t;
				f[j] = f[j]+t>=mod? f[j]+t-mod: f[j]+t;
				now = 1ll*now*bas%mod;
			}
		}
	}
	if(flag == -1) {
		int invn = qpow(n,mod-2);
		for(int i=0;i<n;++i) f[i] = 1ll*f[i]*invn%mod;
	}
}

void pol_mul(int *f,int *g,int n,int m) {
	for(m+=n,n=1;n<m;n<<=1);
	for(int i=0;i<n;++i) rev[i] = (rev[i>>1]>>1)|((i&1)?(n>>1):0);
	NTT(f,n,1); 
	NTT(g,n,1);
	for(int i=0;i<n;++i) f[i] = 1ll*f[i]*g[i]%mod;
	NTT(f,n,-1);
}

namespace Stirling1 {
	int a[MAXN],b[MAXN],f[MAXN],pi[MAXN],iv[MAXN],g[MAXN];

	void presol(int n) {
		pi[0]=1; for(int i=1;i<=n;++i) pi[i] =1ll*pi[i-1]*i%mod;
		iv[n]=qpow(pi[n],mod-2);
		for(int i=n-1;i>=0;--i) iv[i] = 1ll*iv[i+1]*(i+1)%mod;
	}

	void solve(int m) {
		if(m == 1) {f[1] = 1; return ; }
		if(m&1) {
			solve(m-1);
			for(int i=m;i>=1;--i) f[i]=(f[i-1]+1ll*f[i]*(m-1)%mod)%mod;
			f[0]=1ll*f[0]*(m-1)%mod;
		}
		else {
			int n = m/2;
			solve(n);
			int now=1;
			for(int i=0;i<=n;++i) {
				a[i] = 1ll*f[i]*pi[i]%mod;
				b[i] = 1ll*now*iv[i]%mod,now=1ll*now*n%mod;
			}
			reverse(a,a+n+1);
			pol_mul(a,b,n+1,n+1);
			for(int i=0;i<=n;++i) g[i] = 1ll*iv[i]*a[n-i]%mod;
			pol_mul(f,g,n+1,n+1);
			int N=1;
			for(;N<(n+1)*2;N<<=1);
			for(int i=n+1;i<N;++i) a[i] = b[i] = g[i] = 0;
			for(int i=m+1;i<N;++i) f[i] = 0;
		}
	}
}

int n,m,f[100],g[100];
signed main()
{
	int n;
	cin >> n;
	Stirling1::presol(n*3);
	Stirling1::solve(n);
	for(int i=0;i<=n;++i) cout << Stirling1::f[i] << " ";
	cout << "\n";
	return 0;
}
