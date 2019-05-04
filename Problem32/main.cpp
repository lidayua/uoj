#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#define INF 1000000000000000000LL
#define maxn 110
#define each(e, x) for(__typeof((x).begin()) e=(x).begin();e!=(x).end();++e)
using namespace std;
typedef long long LL;
LL dis[maxn][maxn][maxn*2];
int n;
LL len[maxn][maxn][3];
bool connect[maxn][maxn];
struct Intervel
{
	LL l,r;
	Intervel() {}
	Intervel(LL l,LL r):l(l),r(r) {}
	friend Intervel operator | (const Intervel &a, const Intervel &b)
	{
		return Intervel(min(a.l,b.l),max(a.r,b.r));
	}
	friend Intervel operator & (const Intervel &a, const Intervel &b)
	{
		return Intervel(max(a.l,b.l),min(a.r,b.r));
	}
	friend bool operator < (const Intervel &a, const Intervel &b)
	{
		return a.l<b.l;
	}
};
vector<Intervel> sol[maxn];
void update(LL &a, LL b)
{
	if(a>b)
		a=b;
}
void read()
{
	int m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			for(int k=0;k<=2*n;++k)
				dis[i][j][k]=INF;
	}
	for(int i=0;i<=n;++i)
		dis[i][1][n]=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			len[i][j][0]=len[i][j][1]=len[i][j][2]=INF;
		connect[i][i]=true;
	}
	for(int i=1,a,b,w,s;i<=m;++i)
	{
		scanf("%d %d %d %d",&a,&b,&w,&s);
		len[a][b][s+1]=min(len[a][b][s+1],(LL)w);
		connect[a][b]=true;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				connect[i][j]|=connect[i][k]&connect[k][j];
	for(int t=0;t<n;++t)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				for(int s=0;s<3;++s)
					if(len[i][j][s]!=INF)
						for(int k=0;k<=n*2;++k)
							if(dis[t][i][k]!=INF&&k+s-1>=0&&k+s-1<=n*2)
								update(dis[t+1][j][k+s-1],dis[t][i][k]+len[i][j][s]);
}
vector<Intervel> relax(vector<Intervel> &a)
{
	if(a.empty())
		return a;
	sort(a.begin(),a.end());
	vector<Intervel> ans;
	Intervel now=a[0];
	for(int i=1;i<(int)a.size();++i)
	{
		if(a[i].l<=now.r)
			now.r=max(now.r,a[i].r);
		else
		{
			ans.push_back(now);
			now=a[i];
		}
	}
	ans.push_back(now);
	return ans;
}
vector<Intervel> merge(vector<Intervel> &a,vector<Intervel> &b)
{
	if(a.empty())
		return a;
	if(b.empty())
		return b;
	vector<Intervel> c;
	for(int i=0,j=0;i<(int)a.size();++i)
	{
		while(j<(int)b.size()&&b[j].r<a[i].l)
			++j;
		for(int k=j;k<(int)b.size()&&b[k].l<=a[i].r;++k)
			c.push_back(a[i]&b[k]);
	}
	return relax(c);
}
LL countx(int v)
{
	vector<Intervel> intervels;
	intervels.push_back(Intervel(-INF,INF));
	for(int i=1;i<=n;++i)
		if(connect[i][v])
			intervels = merge(intervels,sol[i]);
	LL ans=0;
	for(int i=0;i<(int)intervels.size();++i)
	{
		Intervel &l=intervels[i];
		if(l.l==-INF||l.r==INF)
			return -1;
		ans+=l.r-l.l+1;
	}
	return ans;
}
Intervel solve(LL k1,LL b1,LL k2,LL b2)
{
	//k1*x+b1>=k2*x+b2
	//(k1-k2)x>=b2-b1
	if(k1-k2>0)
	{
		LL x=(b2-b1)/(k1-k2)-3;
		while((k1-k2)*x<b2-b1)
			++x;
		return Intervel(x,INF);
	}
	else
	{
		LL x=(b2-b1)/(k1-k2)+3;
		while((k1-k2)*x<b2-b1)
			--x;
		return Intervel(-INF,x);
	}
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		sol[i].push_back(Intervel(-INF,INF));
		for(int k1=0;k1<=n*2;++k1)
			if(dis[n][i][k1]!=INF)
			{
				vector<Intervel> tmp;
				if(dis[n][i][k1]>=dis[n-1][i][k1])
					tmp.push_back(Intervel(-INF,INF));
				for(int k2=0;k2<=n*2;++k2)
					if(dis[n-1][i][k2]!=INF&&k1!=k2)
						tmp.push_back(solve(k1-n,dis[n][i][k1],k2-n,dis[n-1][i][k2]));
				tmp=relax(tmp);
				sol[i]=merge(sol[i],tmp);
			}
	}
	for(int i=1;i<=n;++i)
		printf("%lld\n",countx(i));
}
int main()
{
	read();
	work();
	return 0;
}