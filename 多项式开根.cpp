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
		
#define line cerr<<"--------------------\n"
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" ";cerr<<endl;

const int N = 1e6, mod = 998244353, G = 3, v2 = 499122177;
int n,g[N],rev[N];
int qpow(int x,int y) {
	int res = 1;
	for(int i=0;(1<<i)<=y;++i,x=1ll*x*x%mod) if(y&(1<<i)) res = 1ll*res*x%mod;
	return res;
}

int INV = qpow(G,mod-2);
void NTT(int *f,int n,int flag) {
	for(int i=0;i<n;++i) rev[i] = rev[i>>1]>>1|(i&1? n>>1: 0);
	for(int i=0;i<n;++i) if(rev[i] > i) swap(f[i],f[rev[i]]);
	for(int p=2,len;p<=n;p<<=1) {
		len = p >> 1;
		int bas = qpow(flag==1? G: INV, (mod-1)/p);
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

namespace TOI {
	int f[N],tmp[N],t[N];
	void to_inv(int *g,int n) {
		memset(f,0,sizeof(f));
		memset(tmp,0,sizeof(tmp));
		memset(t,0,sizeof(t));
		int N;
		for(N = 1; N <= n; N<<=1);

		f[0] = qpow(g[0], mod-2);
		for(int len = 2; len <= N; len<<=1) {
			for(int i = 0; i < (len>>1); ++i) tmp[i] = 2ll*f[i]%mod;
			NTT(f,len<<1,1);  for(int i=0;i<len<<1;++i) f[i] = 1ll*f[i]*f[i]%mod;
			for(int i = 0; i < len; ++i) t[i] = g[i]; NTT(t,len<<1,1);
			for(int i = 0; i < (len<<1); ++i) f[i] = 1ll*f[i]*t[i]%mod;
			NTT(f,len<<1,-1); for(int i=len;i<(len<<1);++i) f[i] = 0;
			for(int i = 0; i<len; ++i) f[i] = (tmp[i] - f[i] + mod)%mod;
		}
		for(int i = 0; i < N; ++i) g[i] = i<n?f[i]:0;
	}
}

namespace TOS {

	int f[N],tmp[N],t[N],d[N];
	void to_sqrt(int *g) {
		memset(f,0,sizeof(f));
		memset(tmp,0,sizeof(tmp));
		memset(t,0,sizeof(t));
		int N;
		for(N = 1; N <= n; N<<=1);
		f[0] = 1;
		for(int len = 2; len <= N; len<<=1) {
			memset(tmp,0,sizeof(tmp)); memset(t,0,sizeof(t));
			for(int i = 0; i < (len>>1); ++i) tmp[i] = 2ll*f[i]%mod;
			TOI::to_inv(tmp,len);
			NTT(tmp,len<<1,1);
			for(int i = 0; i < len; ++i) t[i] = g[i]; NTT(t,len<<1,1); 
			NTT(f,len<<1,1); for(int i = 0; i<(len<<1);++i) f[i] = (1ll*f[i]*f[i]%mod+t[i])%mod;
			for(int i = 0; i<(len<<1);++i) f[i] = 1ll*f[i]*tmp[i]%mod;
			NTT(f,len<<1,-1); for(int i = len; i<(len<<1); ++i) f[i] = 0;
		}
		for(int i = 0; i < N; ++i) g[i] = f[i];
	}

}

signed main()
{
	cout << qpow(2,mod-2) << "\n";
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> g[i];
	TOS::to_sqrt(g);
	for(int i = 0; i < n; ++i) cout << g[i] << " ";
	cout << "\n";
	return 0;
}