#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	int p;
	while(t--) {
		cin>>p;
		int k = (p-1)/2;
		cout<<p - k - 1<<" "<<p-1<<endl;
	}
	
	return 0;
}
