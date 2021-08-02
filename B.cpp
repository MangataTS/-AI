#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	string ch1,ch2;
	while(t--) {
		int n;
		cin>>n;
		cin>>ch1>>ch2;
		int ans = 0;
		for(int i = 0;i < n; ++i) {
			if(ch2[i] == '0') {
				continue;
			}
			else if(ch2[i] == '1') {
				if(ch1[i] == '0') {
					ans++;
				}
				else if(ch1[i] == '1') {
					if(i - 1 >= 0 && ch1[i - 1] == '1') {
						ans++;
						ch1[i - 1] = '0';
					}
					else if(i + 1 < n && ch1[i + 1] == '1') {
						ans++;
						ch1[i + 1] = '0';
					}
				}
			}
		}
		cout<<ans<<endl;
		
	}
	
	return 0;
}
