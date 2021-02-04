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
const int N = 1e5+5, inf=1e9;
const db eps = 1e-7;
int syp(db x) {
	if(abs(x) <= eps) return 0;
	else if(x > 0) return 1;
	else return -1;
}
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
db crs(voc v1,voc v2) {return v1.x*v2.y-v2.x*v1.y; }
db dot(voc v1,voc v2) {return v1.x*v2.x+v1.y*v2.y; }
db dis(voc A,voc B) {return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}

void outp(voc P) {
	printf("(%0.6lf,%0.6lf)\n",P.x,P.y);
}

voc lft(inf,inf);
int n;
bool cmp(voc a,voc b) {
	if(a==lft) return 1;
	else if(b==lft) return 0;
	else if(syp(crs(a-lft,b-lft)) == 0) return dis(a,lft)<dis(b,lft);
	else return syp(crs(a-lft,b-lft)) > 0;
}

int st[N],tp=0;
signed main()
{
	cin >> n;
	for(int i=1;i<=n;++i) {
		scanf("%lf%lf",&pot[i].x,&pot[i].y);
		if(pot[i].x < lft.x) lft = pot[i];
	}
	sort(pot+1,pot+n+1,cmp);
	for(int i=1;i<=n;++i) {
		while(tp>1 && syp(crs(pot[st[tp]]-pot[st[tp-1]],pot[i]-pot[st[tp]])) == -1 ) --tp;
		st[++tp] = i;
	}
	db ans = 0;
	for(int i=1;i<tp;++i) ans += dis(pot[st[i]],pot[st[i+1]]);
	ans += dis(pot[st[tp]],pot[st[1]]);
	printf("%0.2lf\n",ans);
	return 0;
}