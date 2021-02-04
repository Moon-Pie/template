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
#define IT(i,A,x) for(i = A[x]; i!=x; i=A[i])
using namespace std;
const int N = 505;
int n,m,L[N],R[N],U[N],D[N],inx=0,siz[N],col[N],row[N],fir[N];
void build() {
	for(int i=0;i<=m;++i) {
		L[i] = i-1;
		R[i] = i+1;
		U[i] = D[i] = i;
		col[i] = i;
	}
	L[0] = m; R[m] = 0;
	memset(siz,0,sizeof(siz));
	memset(fir,0,sizeof(fir));
	inx = m;
}
void insert(int r,int c) {
	row[++inx] = r;
	col[inx] = c;
	siz[c] ++;
	U[inx] = c;
	D[inx] = D[c];
	U[D[c]] = inx;
	D[c] = inx;
	if(!fir[r]) {
		fir[r] = inx;
		L[inx] = R[inx] = inx;
	}
	else {
		L[inx] = fir[r];
		R[inx] = R[fir[r]];
		L[R[fir[r]]] = inx;
		R[fir[r]] = inx;
	}
}

void remove(int c) {
	R[L[c]] = R[c];
	L[R[c]] = L[c];
	int i,j;
	IT(i,U,c) {
		IT(j,R,i) {
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			siz[col[j]]--;
		}
	}
}
void recover(int c) {
	int i,j;
	IT(i,U,c) {
		IT(j,R,i) {
			U[D[j]] = j;
			D[U[j]] = j;
			siz[col[j]]++;
		}
	}
	L[R[c]] = c;
	R[L[c]] = c;
}

int ans = 0, sta[N];
bool dance(int dep) {
	if(!R[0]) {
		ans = dep-1;
		return 1;
	}
	int c = R[0], i, j;
	IT(i,R,0) if(siz[i] < siz[c]) c=i;
	remove(c);
	IT(i,U,c) {
		IT(j,R,i) remove(col[j]);
		sta[dep] = row[i];
		if(dance(dep+1)) return 1;
		IT(j,R,i) recover(col[j]);
	}
	recover(c);
	return 0;
}

signed main()
{
	cin >> n >> m;
	build();
	for(int x,i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			scanf("%d",&x);
			if(x) insert(i,j);
		}
	}
	dance(1);
	if(ans) {
		for(int i=1;i<=ans;++i) printf("%d ",sta[i]);
		cout << "\n";
	}
	else {
		cout << "No Solution!\n";
	}

	return 0;
}