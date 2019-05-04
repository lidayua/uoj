#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn 110
#define maxm 1000010
#define mod 1000000009
using namespace std;
typedef long long LL;
int n,m,a[maxn];
int f[maxn][maxn],sum[2][maxm];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<=n;++i)
	{
		char c;
		for(c=getchar();c!='-'&&!isdigit(c);c=getchar());
		int type=1,s=0;
		if(c=='-')
			type=0,c=getchar();
		while(isdigit(c))
			s=((LL)s*10+c-'0')%mod,c=getchar();
		if(type==0)
			s=(mod-s)%mod;
		a[i]=s;
	}
}
void solve()
{
	for(int i=1;i<=n+2;++i)
	{
		int s=0;
		for(int j=n;j>=0;--j)
			s=((LL)s*i+a[j])%mod;
		f[1][i]=s;
	}
	for(int i=2;i<=n+2;++i)
		for(int j=1;j<=n-i+3;++j)
			f[i][j]=(f[i-1][j+1]-f[i-1][j]+mod)%mod;
	int cur=0;
	for(int i=1;i<=m;++i)
		sum[cur][i]=f[n+1][1];
	for(int i=n;i>=1;--i)
	{
		cur^=1;
		sum[cur][1]=f[i][1];
		for(int j=2;j<=m;++j)
		{
			sum[cur][j]=sum[cur][j-1]+sum[cur^1][j-1];
			if(sum[cur][j]>=mod)
				sum[cur][j]-=mod;
		}
	}
	int cnt=0;
	static int ans[maxn];
	for(int i=1;i<=m;++i)
		if(sum[cur][i]==0)
			ans[++cnt]=i;
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)
		printf("%d\n",ans[i]);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	solve();
	return 0;
}