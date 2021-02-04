#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
char s[N];
int n,m,tp[N],sa[N],rnk[N],tax[N],Height[N];
void Sort()
{
	for(int i=0;i<=m;++i) tax[i] = 0;
	for(int i=1;i<=n;++i) tax[rnk[i]]++;
	for(int i=1;i<=m;++i) tax[i] += tax[i-1];
	for(int i=n;i>=1;--i) sa[ tax[rnk[tp[i]]]-- ] = tp[i];
}
void SuffixSort()
{
	m = 128;
	for(int i=1;i<=n;++i) rnk[i]=s[i]-'0'+1, tp[i]=i;
	Sort();
	for(int w=1,p=0; p < n; m=p, w<<=1) {
		p = 0;
		for(int i=1;i<=w;++i) tp[++p] = n-w+i;
		for(int i=1;i<=n;++i) if(sa[i] > w) tp[++p] = sa[i]-w;
		Sort();
		memcpy(tp,rnk,sizeof(rnk));
		rnk[sa[1]] = p = 1;
		for(int i=2;i<=n;++i) {
			rnk[sa[i]] = (tp[sa[i-1]]==tp[sa[i]] && tp[sa[i-1]+w]==tp[sa[i]+w])? p: ++p;
		}
	}

	int j, k=0;
	for(int i=1;i<=n;++i) {
		if(k) --k;
		j = sa[rnk[i]-1];
		while(s[j+k] == s[i+k]) ++k;
		Height[rnk[i]] = k;
	}
	// for(int i=1;i<=n;++i) {
	// 	cout << rnk[i] <<"  ";
	// 	for(int j=sa[i];j<=n;++j) cout <<s[j];
	// 	cout <<"\n";
	// }
}
signed main()
{
	scanf("%s",s+1);
	n = strlen(s+1);
	SuffixSort();
	for(int i=1;i<=n;++i) printf("%d%c",sa[i],i==n? '\n': ' ');
	return 0;
}