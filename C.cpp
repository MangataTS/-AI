#include<bits/stdc++.h>
using namespace std;

int n,m;

const int N = 2e5+10; 

map<int,int> V[N];

int p[N];

inline int f(int k) {
	int ans = 0;
	for(auto it : V[k]) {
		if(it.first > k) ans++;
	}
	return ans;
}

//inline bool delt(int loc,int k) {
//	bool fg = true;
//	for(int i = 0,len = V[loc].size();i < len; ++i) {
////		printf("V[loc][i] = %d\n",V[loc][i]);
//		if(V[loc][i] == k)
//			V[loc][i] = 0;
//		if(V[loc][i] > loc)	fg = false;
//	}
//	return fg;
//}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m; ++i) {
		int u,v;
		scanf("%d %d",&u,&v);
		V[u][v] = 1;
		V[v][u] = 1;
	}
	int q;
	int ans = 0;
	for(int i = 1;i <= n; ++i) {
		p[i] = f(i);
		if(p[i] == 0) ans++;
	}
	scanf("%d",&q);
	while(q--) {
		int u,v,w;
		scanf("%d",&w);
		if(w == 1) {
			scanf("%d%d",&u,&v);
			if(u > v) {
				if(p[v] == 0) ans--;
				p[v]++;
			}
			else {
				if(p[u] == 0) ans--;
				p[u]++;
			}
			V[u][v] = V[u][v]= 1;
		}
		else if(w == 2) {
			scanf("%d%d",&u,&v);
			if(u > v) {
				if(p[v] == 1) {
					ans++;
				}
				p[v]--;
			}
			else {
				if(p[u] == 1) 
					ans++;
				p[u]--;
			}
			V[u][v] = V[v][u] = 0;
		}
		else if(w == 3) {
			printf("%d\n",ans);
		}
	}
	
	return 0;
}
