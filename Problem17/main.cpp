#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 10010
#define maxm 1010
using namespace std;
int n,m,have[maxn],x[maxn],y[maxn],L[maxn],R[maxn];
void read()
{
	int k;
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d",x+i,y+i);
		L[i]=0,R[i]=m+1;
	}
	for(int i=1,x;i<=k;++i)
	{
		scanf("%d",&x);
		scanf("%d %d",&L[x],&R[x]);
		have[x]=1;
	}
}
void Dp()
{
	static int dp[maxn][maxm];
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		fill(dp[i]+1,dp[i]+m+1,1<<30);
		for(int j=x[i]+1;j<=R[i]-1;++j)
			dp[i][j]=min(dp[i-1][j-x[i]]+1,dp[i][j-x[i]]+1);
		fill(dp[i]+1,dp[i]+L[i]+1,1<<30);
		if(R[i]>m)
			for(int j=1;j<=m;++j)
				dp[i][m]=min(dp[i][m],dp[i-1][j]+max(1,(m-j-1+x[i])/x[i]));
		for(int j=L[i]+1;j<=R[i]-1&&j+y[i]<=m;++j)
			dp[i][j]=min(dp[i][j],dp[i-1][j+y[i]]);
		int val=1<<30;
		for(int j=1;j<=m;++j)
			dp[i][j]=min(dp[i][j],1<<30),val=min(val,dp[i][j]);
		if(val==1<<30)
		{
			printf("0\n");
			printf("%d\n",cnt);
			return ;
		}
		cnt+=have[i];
	}
	printf("1\n");
	printf("%d\n",*min_element(dp[n]+1,dp[n]+m+1));
}
int main()
{
	read();
	Dp();
	return 0;
}