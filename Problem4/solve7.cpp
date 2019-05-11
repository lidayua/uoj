#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#include<ctime>
#include<fstream>
#include<algorithm>
#define maxn 1010
#define MAXT 100000000
#define SIZE(x) (int)((x).size())
using namespace std;
typedef long long LL;
typedef unsigned int uint;
int n,m,K,lmin,lmax,c1,c2,F,a[maxn][maxn],maxl,cnt;
vector<int> ans;
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
uint data()
{
	return rand()<<15|rand();
}
int randint(int l, int r)
{
	return data()%(r-l+1)+l;
}
void DFS(int xa,int ya,int xb,int yb,vector<int> &lcor,vector<int> &rcor)
{
	int t=a[xa][ya];
	a[xa][ya]=a[xb][yb]=-1;
	lcor.push_back(xa),lcor.push_back(ya);
	rcor.push_back(xb),rcor.push_back(yb);
	int l=SIZE(lcor)-1;
	if(l>=lmax-1)
	{
		if(maxl<l)
		{
			ans.clear();
			maxl=l;
			for(int i=SIZE(lcor)-2;i>=0;i-=2)
				ans.push_back(lcor[i]),ans.push_back(lcor[i+1]);
			for(int i=2;i<SIZE(rcor);++i)
				ans.push_back(rcor[i]);
		}
		if(++cnt%100000==0)
			printf("%d\n",cnt);
	}
	if(maxl<lmax-1&&cnt<=MAXT)
	{
		bool mark=false;
		for(int i=0;i<4;++i)
		{
			int px=xa+movex[i],py=ya+movey[i];
			if(px>=1&&px<=n&&py>=1&&py<=m&&a[px][py]!=-1)
				for(int j=3;j>=0;--j)
				{
					int qx=xb+movex[j],qy=yb+movey[j];
					if(qx>=1&&qx<=n&&qy>=1&&qy<=n&&a[qx][qy]!=-1&&a[qx][qy]==a[px][py]&&(px!=qx||py!=qy))
					{
						if(maxl>=lmax-1||cnt>MAXT)
							break;
						DFS(px,py,qx,qy,lcor,rcor);
						mark=true;
					}
				}
		}
		if(!mark)
		{
			if(maxl<l)
			{
				ans.clear();
				maxl=l;
				for(int i=SIZE(lcor)-2;i>=0;i-=2)
					ans.push_back(lcor[i]),ans.push_back(lcor[i+1]);
				for(int i=2;i<SIZE(rcor);++i)
					ans.push_back(rcor[i]);
			}
			if(++cnt%100000==0)
				printf("%d\n",cnt);
		}
	}
	for(int i=0;i<2;++i)
		lcor.pop_back(),rcor.pop_back();
	a[xa][ya]=a[xb][yb]=t;
}
int main()
{
	// srand(time(0));
	freopen("game7.in","r",stdin);
	ofstream fout("game7.out");
	scanf("%d %d %d %d %d %d %d %d",&n,&m,&K,&lmin,&lmax,&c1,&c2,&F);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	vector<int> lcor,rcor;
	for(int i=1;i<=1;++i)
	{
		int x=randint(1,n),y=randint(1,m);
		while(a[x][y]==0||a[x][y]==-1)
			x=randint(1,n),y=randint(1,m);
		x=n/2,y=m/2;
		DFS(x,y,x,y,lcor,rcor);
	}
	fout<<1<<endl;
	fout<<SIZE(ans)/2<<" ";
	for(auto x:ans)
		fout<<x<<" ";
	fout<<endl;
}