#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 30
using namespace std;
int n,x[maxn],y[maxn],cnt[maxn],d;
void read()
{
	scanf("%d %d",&d,&n);
	for(int i=1;i<=n;++i)
		scanf("%d %d %d",&x[i],&y[i],&cnt[i]);
}
void work()
{
	int maxv=0,sum=0;
	for(int i=0;i<=128;++i)
		for(int j=0;j<=128;++j)
		{
			int value=0;
			for(int k=1;k<=n;++k)
				if(abs(x[k]-i)<=d&&abs(y[k]-j)<=d)
					value+=cnt[k];
			if(maxv==value)
				++sum;
			else if(maxv<value)
				maxv=value,sum=1;
		}
	printf("%d %d\n",sum,maxv);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	work();
	return 0;
}