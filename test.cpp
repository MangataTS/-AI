#include<bits/stdc++.h> 
using namespace std;
struct Node {
	int x,y,point;
	bool operator < (const Node & a) const{
		return this->point > a.point;
	}
}; 

int main()
{
	vector<Node> V;
	V.push_back({1,2,3});
	V.push_back({1,2,4});
	sort(V.begin(),V.end());
	printf("%d\n",V[0].point);
	puts("！！|！！|！！");
	printf("X   | O\n");
	puts("！！|！！|！！");
	
	
}
