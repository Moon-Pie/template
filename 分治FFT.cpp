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
		
#define line cerr<<"--------------------\n"
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" ";cerr<<endl;

using namespace std;
const int Maxn = (1<<20);
const int mod=998244353, G=3, I=332748118;

int qpow(int x,int y) {
	int res=1;
	for(int i=0;(1<<i)<=y;++i,x=1ll*x*x%mod) if(y&(1<<i)) res=1ll*res*x%mod;
	return res;
}
int n,g[Maxn],f[Maxn];
int rev[Maxn];

void NTT(int *f,int flag,int N) {
	for(int i=0;i<N;++i) rev[i] = (rev[i>>1]>>1)|(i&1?N>>1:0);
	for(int i=0;i<N;++i) if(rev[i] > i) swap(f[rev[i]],f[i]);
	for(int p=2;p<=N;p<<=1) {
		int len = p>>1;
		int bas = qpow(flag==1? G: I, (mod-1)/p);
		for(int i=0;i<N;i+=p) {
			int now = 1;
			for(int j=i;j<i+len;++j) {
				int t = 1ll*f[j+len]*now%mod;
				f[j+len] = f[j]-t<0? f[j]-t+mod: f[j]-t;
				f[j] = f[j]+t>mod? f[j]+t-mod: f[j]+t;
				now = 1ll*now*bas%mod;
			}
		}
	}
	if(flag == -1) {
		int invn = qpow(N,mod-2);
		for(int i=0;i<N;++i) f[i] = 1ll*f[i]*invn%mod;
	}
}

int tg[Maxn],tf[Maxn];
void div_NTT(int l,int r) {
	if(l == r) {
		if(l == 0) f[l] = 1;
		return ;
	}
	int mid = (l+r)>>1;
	int len = r-l+1;

	div_NTT(l,mid);

	int N; for(N=1;N<=len+len;N<<=1);
	for(int i=0;i<N;++i) tf[i] = l+i>mid? 0: f[l+i];
	for(int i=0;i<N;++i) tg[i] = i>r? 0: g[i];
	NTT(tf,1,N);
	NTT(tg,1,N);
	for(int i=0;i<N;++i) tg[i] = 1ll*tf[i]*tg[i]%mod;
	NTT(tg,-1,N);
	for(int i=mid+1;i<=r;++i) f[i] = (f[i]+tg[i-l])%mod;
		
	div_NTT(mid+1,r);
}

signed main()
{
	cin >> n;
	for(int i=1;i<n;++i) cin >> g[i];
	div_NTT(0,n-1);

	for(int i=0;i<n;++i) cout << f[i] <<" ";
	cout <<"\n";

	return 0;
}