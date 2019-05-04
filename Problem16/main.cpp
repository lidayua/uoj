#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define mod 10007
#define maxn 200010
using namespace std;
vector<int> adj[maxn];
int w[maxn],n;
void read()
{
	scanf("%d",&n);
	for(int i=2,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		adj[a].push_back(b),adj[b].push_back(a);
	}
	for(int i=1;i<=n;++i)
		scanf("%d",w+i);
}
void work()
{
	static int a[maxn];
	int ans1=0,ans2=0;
	for(int i=1;i<=n;++i)
	{
		int tot=0;
		each(p,adj[i])
			a[++tot]=w[*p];
		if(tot<2)
			continue;
		sort(a+1,a+tot+1);
		ans1=max(ans1,a[tot]*a[tot-1]);
		int s1=0,s2=0;
		for(int j=1;j<=tot;++j)
			s1=(s1+a[j])%mod,s2=(s2+a[j]*a[j])%mod;
		ans2=(ans2+s1*s1-s2+mod)%mod;
	}
	printf("%d %d\n",ans1,ans2);
}
int main()
{
	read();
	work();
	return 0;
}
