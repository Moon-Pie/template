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
#define db double
using namespace std;
const db eps = 1e-8, inf = 1e9;
const int N = 1e5+5;
int syp(db x) {return (x>eps)-(x<-eps); }
struct voc
{
	voc(db xx=0,db yy=0) {x=xx,y=yy;}
	db x,y;
	voc operator+(const voc &o)
	const {return voc(x+o.x,y+o.y); }
	voc operator-(const voc &o)
	const {return voc(x-o.x,y-o.y); }
	voc operator*(const db &o)
	const {return voc(x*o,y*o); }
	bool operator==(const voc &o)
	const {return syp(x-o.x)==0 && syp(y-o.y)==0;}
}pot[N];

db dot(voc v1,voc v2) {return v1.x*v2.x+v1.y+v2.y; }
db crs(voc v1,voc v2) {return v1.x*v2.y-v2.x*v1.y; }
db dis(voc A,voc B) {return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)); }
db disf(voc A,voc B) {return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y); }
db ml(voc v) {return sqrt(v.x*v.x+v.y*v.y); }
void uni(voc &v) {v = voc(v.x/ml(v),v.y/ml(v)); }

db dis_P_L(voc A,voc B,voc P) {
	voc v1 = B-A, v2 = voc(v1.y,-v1.x);
	db t = crs((A-P),v1)/crs(v2,v1);
	voc Q = P+v2*t;
	return disf(P,Q);
}

voc L(inf,inf);
bool cmp(voc a,voc b) {
	if(a==L) return 1;
	else if(b==L) return 0;
	else if(syp(crs(a-L,b-L)) == 0) return disf(a,L)<disf(b,L);
	else return syp(crs(a-L,b-L)) > 0;
}
bool cmp1(voc a,voc b) {
	return (a.x!=b.x)?( a.x<b.x): (a.y<b.y);
}

int n,st[N],tp;
int nxt(int x) {return x+1>tp? x+1-tp: x+1; }
void outp(voc v) {printf("(%lf,%lf)\n",v.x,v.y); }

signed main()
{
	cin >> n;
	for(int i=1;i<=n;++i) {
		scanf("%lf%lf",&pot[i].x,&pot[i].y);
		if(pot[i].x < L.x) L = pot[i];
	}
	if(n == 2) {
		printf("%0.0lf\n",disf(pot[1],pot[2]));
		return 0;
	}

	sort(pot+1,pot+n+1,cmp1);
	n = unique(pot+1,pot+n+1)-pot-1;
	sort(pot+1,pot+n+1,cmp);

	tp = 0;
	for(int i=1;i<=n;++i) {
		while(tp>1 && syp(crs(pot[st[tp]]-pot[st[tp-1]], pot[i]-pot[st[tp]])) == -1) --tp;
		st[++tp] = i;
	}

	db mxd = 0, ans = 0;
	int j;
	for(int i=3;i<=tp;++i) if(dis_P_L(pot[st[1]],pot[st[2]],pot[st[i]]) > mxd) {
		mxd = dis_P_L(pot[st[1]],pot[st[2]],pot[st[i]]);
		j = i;
	}
	ans = max(ans,disf(pot[st[j]],pot[st[1]]));
	ans = max(ans,disf(pot[st[j]],pot[st[2]]));
	for(int i=2;i<tp;++i) {
		while(dis_P_L(pot[st[i]],pot[st[i+1]],pot[st[j]]) < dis_P_L(pot[st[i]],pot[st[i+1]],pot[st[nxt(j)]])) j=nxt(j);
		ans = max(ans,disf(pot[st[j]],pot[st[i]]));
		ans = max(ans,disf(pot[st[j]],pot[st[i+1]]));
	}
	while(dis_P_L(pot[st[1]],pot[st[tp]],pot[j]) < dis_P_L(pot[st[1]],pot[st[tp]],pot[st[nxt(j)]])) j = nxt(j);

	ans = max(ans,disf(pot[st[j]],pot[st[tp]]));
	ans = max(ans,disf(pot[st[j]],pot[st[1]]));
	printf("%0.0lf\n",ans);

	return 0;
}