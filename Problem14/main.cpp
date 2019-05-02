#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 500010
using namespace std;
typedef long long LL;
int father[maxn],edge[maxn][2],depth[maxn];
LL ans[maxn];
int Find(int p)
{
	if(father[p]!=p)
		return Find(father[p]);
	return p;
}
void read()
{
	int n,m,top=0;
	static int stack[maxn],inputs[maxn][3];
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		father[i]=i;
	char str[10];
	LL sum=0;
	int cntedge=0;
	for(int i=1;i<=m;++i)
	{
		scanf("%s",str);
		if(str[0]=='A')
		{
			scanf("%d %d",&inputs[i][1],&inputs[i][2]);
			inputs[i][0]=0;
		}
		else if(str[0]=='D')
		{
			scanf("%d",&inputs[i][1]);
			inputs[i][0]=1;
		}
		else
			inputs[i][0]=2;
	}
	for(int i=1;i<=m;++i)
	{
		if(inputs[i][0]==0)
		{
			int a=Find(inputs[i][1]),b=Find(inputs[i][2]);
			if(a!=b&&cntedge==n-2) // first time to get a mst
				ans[i]=sum+i;
			else // answer is not changed
				ans[i]=ans[i-1];
			if(inputs[i+1][0]==2) // "Return", we don't need to consider it
				ans[i+1]=ans[i-1];
			else
			{
				stack[++top]=i; // contains all edges in descending order
				if(a!=b) // we need to add
				{
					if(depth[a]>depth[b])
						swap(a,b);
					father[a]=b,depth[b]=max(depth[b],depth[a]+1);
					edge[i][0]=a,edge[i][1]=b;
					++cntedge,sum+=i;
				}
			}
		}
		else if(inputs[i][0]==1)
		{
			if(inputs[i+1][0]==2) // Return
				ans[i+1]=ans[i-1];
			ans[i]=ans[stack[top-inputs[i][1]]];
			if(inputs[i+1][0]!=2) //we need to delete
			{
				for(int k=inputs[i][1];k>=1;--k)
				{
					int idx=stack[top--];
					if(edge[idx][0]==0)
						continue;
					int a=edge[idx][0],b=edge[idx][1];
					father[a]=a;
					--cntedge,sum-=idx;
				}
			}
		}
		printf("%lld\n",ans[i]);
	}
}
int main()
{
	freopen("input","r",stdin);
	read();
	fclose(stdin);
	fclose(stdout);
	return 0;
}