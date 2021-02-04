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
const int N = 100000;
const db eps = 1e-7;
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
}pot[N];
int syp(db x) {return (x>eps)-(x<-eps); }
db dot(voc v1,voc v2) {return v1.x*v2.x+v1.y*v2.y; }
db crs(voc v1,voc v2) {return v1.x*v2.y-v1.y*v2.x; }

struct Line {
	Line(voc ss=voc(0,0),voc vv=voc(0,0)) {s=ss,v=vv;}
	voc s,v; 
	bool operator<(const Line &o) {
		if(syp(atan2(v.y,v.x) - atan2(o.v.y, o.v.x)) == 0) return syp(crs(o.s-s,v)) > 0;
		else return atan2(v.y,v.x) < atan2(o.v.y, o.v.x);
	}
}li[N];

bool ono(voc a,voc b) {
	return (a.x*b.x>=0) && (a.y*b.y>=0);
}
voc pot_L_L(Line l1,Line l2) {
	return l1.s+l1.v*(crs((l2.s-l1.s),l2.v)/crs(l1.v,l2.v));
}

void outp(voc A) {
	printf("(%lf,%lf)",A.x,A.y);
}

int n,nl=0,t=0;
signed main()
{
	cin >> n;
	for(int i=1,m;i<=n;++i) {
		cin >> m;
		voc a,b,s;
		for(int j=1;j<=m;++j) {
			scanf("%lf%lf",&a.x,&a.y);
			if(j>1) {
				li[++nl].v = a-b;
				li[nl].s = b;
			}
			else {
				s=a;
			}
			b=a;
		}
		li[++nl].v = s-a;
		li[nl].s = a;
	}

	sort(li+1,li+nl+1);
	int sz;
	deque<int> Q;
	for(int i=1;i<=nl;++i) if(i==1 || (atan2(li[i].v.y,li[i].v.x) != atan2(li[i-1].v.y,li[i-1].v.x))) {
		sz = Q.size();
		while(sz > 1) {
			Line l1 = li[Q[sz-2]];
			Line l2 = li[Q[sz-1]];
			voc P = pot_L_L(l2,l1);
			if( syp(crs(P-li[i].s,li[i].v)) > 0) {
				Q.pop_back();
				sz = Q.size();
			}
			else {break;}
		}

		sz = Q.size();
		while(sz > 1) {
			Line l1 = li[Q[0]];
			Line l2 = li[Q[1]];
			voc P = pot_L_L(l1,l2);
			if( syp(crs(P-li[i].s,li[i].v)) > 0) {
				Q.pop_front();
				sz = Q.size();
			}
			else {break;}
		}
		Q.push_back(i);
	}

	sz = Q.size();
	while(sz > 1) {
		Line l1 = li[Q[sz-2]];
		Line l2 = li[Q[sz-1]];
		voc P = pot_L_L(l2,l1);
		if( syp(crs(P-li[Q[0]].s,li[Q[0]].v)) > 0) {
			Q.pop_back();
			sz = Q.size();
		}
		else {break;}
	}

	sz = Q.size();
	while(sz > 1) {
		Line l1 = li[Q[0]];
		Line l2 = li[Q[1]];
		voc P = pot_L_L(l1,l2);
		if( syp(crs(P-li[Q[sz-1]].s,li[Q[sz-1]].v)) > 0) {
			Q.pop_front();
			sz = Q.size();
		}
		else {break;}
	}


	sz = Q.size();
	pot[1] = pot_L_L(li[Q[sz-1]],li[Q[0]]);
	for(int i=1;i<sz;++i) pot[i+1] = pot_L_L(li[Q[i]],li[Q[i-1]]);
	
	db ans = 0;
	for(int i=2;i<sz;++i) {
		ans += crs(pot[i]-pot[1],pot[i+1]-pot[1]);
	}
	ans /= 2;
	printf("%0.3lf\n",syp(ans)==-1? -ans: ans);

	return 0;
}