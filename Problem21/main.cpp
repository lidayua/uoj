#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1000010
using namespace std;
typedef long long LL;
LL cnt[maxn],sum_a;
const int M=1000000;
void read()
{
	int n;
	scanf("%d",&n);
	for(int i=1,a;i<=n;++i)
	{
		scanf("%d",&a);
		sum_a+=a;
		++cnt[a];
	}
	for(int i=1;i<=M;++i)
		cnt[i]+=cnt[i-1];
}
void work()
{
	LL maxv=0;
	for(int i=1;i<=M;++i)
	{
		LL sum=0;
		for(int j=1;j*i<=M;++j)
			sum+=(cnt[min(M,(j+1)*i-1)]-cnt[j*i-1])*(i-1)*j;
		maxv=max(maxv,sum);
	}
	cout<<sum_a-maxv<<endl;
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}