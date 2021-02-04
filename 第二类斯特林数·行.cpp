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
int n,N;
const int MAXN = 6e5;
const int mod = 167772161, g = 3;
int qpow(int x,int y) {
	int res = 1;
	for(int i=0;(1<<i)<=y;++i,x=1ll*x*x%mod) if(y&(1<<i)) res=1ll*res*x%mod;
	return res; 
}
int INV = qpow(g,mod-2),rev[MAXN];
void NTT(int *f,int flag) {
	for(int i = 0; i < N; ++i) rev[i] = rev[i>>1]>>1|(i&1?N>>1:0);
	for(int i = 0; i < N; ++i) if(rev[i] > i) swap(f[i],f[rev[i]]);
	for(int len, p = 2; p <= N; p<<=1) {
		len = p>>1;
		int bas = qpow(flag==1? g: INV, (mod-1)/p);
		for(int i = 0; i < N; i += p) {
			int now = 1;
			for(int j = i; j < i+len; ++j) {
				int t = 1ll*f[j+len]*now%mod;
				f[j+len] = f[j]-t<0? f[j]-t+mod: f[j]-t;
				f[j] = f[j]+t>=mod? f[j]+t-mod: f[j]+t;
				now = 1ll*now*bas%mod;
			}
		}
	}
	if(flag == -1) {
		int invn = qpow(N,mod-2);
		for(int i=0;i<N;++i) f[i] = 1ll*f[i]*invn%mod;
	}
}
int a[MAXN],b[MAXN],f[MAXN];
int pi[MAXN];
signed main()
{
	cin >> n; n++;
	pi[0]=1; for(int i=1;i<=n;++i) pi[i]=1ll*pi[i-1]*i%mod;
	for(int i=0;i<n;++i) a[i] = 1ll*qpow(i,n-1)*qpow(pi[i],mod-2)%mod;
	for(int i=0;i<n;++i) b[i] = (mod+qpow(pi[i],mod-2)*(i&1?-1:1))%mod;

	for(N=1;N<=n+n;N<<=1);
	NTT(a,1); NTT(b,1);
	for(int i=0;i<N;++i) f[i] = 1ll*a[i]*b[i]%mod;
	NTT(f,-1);
	for(int i=0;i<n;++i) cout << f[i] <<" ";
	cout << "\n";
	return 0;
}