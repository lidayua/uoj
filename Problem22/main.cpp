#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
#define maxm 5010
#define mod 998244353
using namespace std;
typedef long long LL;
int a[maxn],n,x,dp[maxm],fact[maxn],invfact[maxn];
int Power(int p,int n)
{
	int ans=1;
	for(;n;n>>=1,p=(LL)p*p%mod)
		if(n&1)
			ans=(LL)ans*p%mod;
	return ans;
}
int inv(int p)
{
	return Power(p,mod-2);
}
void read()
{
	scanf("%d %d",&n,&x);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	fact[0]=1;
	for(int i=1;i<=n;++i)
		fact[i]=(LL)fact[i-1]*i%mod;
	invfact[n]=inv(fact[n]);
	for(int i=n-1;i>=0;--i)
		invfact[i]=(LL)invfact[i+1]*(i+1)%mod;
}

void Dp()
{
	dp[x]=1;
	int ans=0;
	if(x<a[1])
		ans=x;
	for(int i=x,k;i>=1;--i)
	{
		k=upper_bound(a+1,a+n+1,i)-a-1;
		if(!dp[i])
			continue;
		for(int j=1;j<=k;++j)
		{
			int y=a[j],idy=upper_bound(a+1,a+n+1,i%y)-a-1;
			dp[i%y]=(dp[i%y]+(LL)dp[i]*fact[k-1]%mod*invfact[idy])%mod;
			if(i%y<a[1]&&ans<i%y)
				ans=i%y;
		}
	}
	int cnt=n,extra=1;
	for(int i=1;i<=n;++i)
		if(a[i]>x)
			extra=(LL)extra*(cnt--)%mod;
	printf("%d\n%d\n",ans,(LL)dp[ans]*extra%mod);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Dp();
	return 0;
}