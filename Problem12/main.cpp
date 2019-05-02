#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
LL Sqrt(LL n)
{
	LL x=max(1LL,(LL)sqrt(n)-5);
	while(x<n/x)
		++x;
	return x;
}
int main()
{
	int T;
	LL l,g;
	for(cin>>T;T;--T)
	{
		cin>>g>>l;
		cout<<g*2*Sqrt(l/g)<<" "<<g*(1+l/g)<<endl;
	}
	return 0;
}