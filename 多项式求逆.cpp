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
const int N = 1e6, mod = 998244353, G = 3;
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

int f[N],tmp[N],t[N];
void to_inv(int *g) {
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
	for(int i = 0; i < N; ++i) g[i] = f[i];
}

signed main()
{
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> g[i];
	to_inv(g);
	// to_inv(g);
	for(int i = 0; i < n; ++i) cout << g[i] << " ";
	cout << "\n";

	return 0;
}