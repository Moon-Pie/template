#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y) {
	int res=1;
	for(int i=0;(1ll<<i)<=y;++i,x=1ll*x*x%mod) if(y&(1ll<<i)) res=1ll*res*x%mod;
	return res;
} 
int polya(int n,int m) // n个石子，m种颜色
{
	vector<int> divs;
	vector<int> prim;
	int t=n;
	for(int i=1;1ll*i*i<=n;++i) {
		if(n%i==0) {
			divs.push_back(i);
			if(i*i!=n) divs.push_back(n/i);
		}
		if(i>1 && t%i==0) {
			prim.push_back(i);
			while(t%i == 0) t/=i;
		}
	}
	if(t > 1) prim.push_back(t);

	ll res=0,sum=0;
	for(int i=0;i<(int)divs.size();++i) {
		ll phi = divs[i]; // 轨迹上有多少个点
		for(int j=0;j<(int)prim.size();++j) {
			if(divs[i]%prim[j] == 0) {
				phi = phi/prim[j]*(prim[j]-1);
			}
		}
		res = (res + 1ll*qpow(m,n/divs[i])*phi%mod)%mod;
	}
	return 1ll*res*qpow(n,mod-2)%mod;
}

signed main()
{

	int n,m;
	int T;
	cin>>T;
	while(T--){
		cin >> n;
		cout << polya(n,n)<< "\n";
	}
	return 0;
}