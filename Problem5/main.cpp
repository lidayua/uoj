#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cctype>
#define maxn 1000010
#define P 131
#define mod 1000000007
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
char str[maxn];
ULL sum[maxn],Power[maxn];
int work()
{
	static int num[maxn];
	memset(num,0,sizeof(num));
	Power[0]=1;
	int n=strlen(str+1);
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]*P+str[i];
	for(int i=2;i<=n;++i)
		if(str[i]==str[1])
		{
			int l=1,r=min(n-i+1,i-1)+1;
			while(l<r)
			{
				int mid=(l+r)>>1;
				sum[mid]==sum[i+mid-1]-sum[i-1]*Power[mid]?l=mid+1:r=mid;
			}
			++num[i],--num[i+l-1];
		}
	for(int i=2;i<=n;++i)
		num[i]+=num[i-1];
	int ans=1;
	for(int i=1;i<=n;++i)
		ans=(LL)ans*(num[i]+1)%mod;
	return ans;
}
int main()
{
	Power[0]=1;
	for(int i=1;i<=1000000;++i)
		Power[i]=Power[i-1]*P;
	int T;
	for(cin>>T;T;--T)
	{
		scanf("%s",str+1);
		printf("%d\n",work());
	}
	return 0;
}
