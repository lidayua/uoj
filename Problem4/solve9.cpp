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
#define MAXT 150
#define SIZE(x) (int)((x).size())
#define DIR_D 0
#define DIR_U 1
#define DIR_L 2
#define DIR_R 3
using namespace std;
typedef long long LL;
typedef unsigned int uint;
int n,m,K,lmin,lmax,c1,c2,F,a[maxn][maxn],maxl,cnt;
vector<int> ans;
int movex[]={1,-1,0,0};
int movey[]={0,0,-1,1};
uint data()
{
	return rand()<<15|rand();
}
int randint(int l, int r)
{
	return data()%(r-l+1)+l;
}
int getD(int x, int y)
{
    int cnt=0;
    for(int i=0;i<4;++i)
	{
		int px=x+movex[i],py=y+movey[i];
		if(px>=1&&px<=n&&py>=1&&py<=m-py&&a[px][py]!=-1)
            cnt++;
	}
    return cnt;
}
bool check(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=m-y&&a[x][y]!=-1;
}
void DFS(int x, int y,vector<int> &lcor,vector<int> &rcor)
{
	int t=a[x][y];
	a[x][y]=a[x][m-y+1]=-1;
	lcor.push_back(x),lcor.push_back(y);
	rcor.push_back(x),rcor.push_back(m-y+1);
	int l=SIZE(lcor)-1;
	if(y==m-y)
	{
		if(maxl<l)
		{
			ans.clear();
			maxl=l;
			for(int i=0;i<SIZE(lcor);++i)
				ans.push_back(lcor[i]);
			for(int i=SIZE(rcor)-2;i>=0;i-=2)
				ans.push_back(rcor[i]),ans.push_back(rcor[i+1]);
		}
		++cnt;
		if(cnt%10==0)
			printf("%d %d\n",cnt,SIZE(ans)/2);
	}
	if(cnt<MAXT)
	{
		int tmp[6],cand=0;
		if(y%2==0)
		{
			if(x==n&&y%4==2)
				tmp[++cand]=DIR_R;
			if(x==1&&y%4==0)
				tmp[++cand]=DIR_R;
			tmp[++cand]=DIR_L;
			tmp[++cand]=DIR_D;
			tmp[++cand]=DIR_U;
		}
		else
		{
			tmp[++cand]=DIR_R;
			tmp[++cand]=DIR_D;
			tmp[++cand]=DIR_U;
		}
		for(int i=1;i<=cand;++i)
		{
			int px=x+movex[tmp[i]],py=y+movey[tmp[i]];
			if(check(px,py))
				DFS(px,py,lcor,rcor);
		}
	}
	for(int i=0;i<2;++i)
		lcor.pop_back(),rcor.pop_back();
	a[x][y]=a[x][m-y+1]=t;
}
int main()
{
	// srand(time(0));
	freopen("game9.in","r",stdin);
	ofstream fout("game9.out");
	scanf("%d %d %d %d %d %d %d %d",&n,&m,&K,&lmin,&lmax,&c1,&c2,&F);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	vector<int> lcor,rcor;
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m-j;++j)
			if(a[i][j]!=a[i][m-j+1])
				a[i][j]=a[i][m-j+1]=-1,printf("%d %d\n",i,j);
	DFS(1,1,lcor,rcor);
	fout<<1<<endl;
	fout<<SIZE(ans)/2<<" ";
	for(auto x:ans)
		fout<<x<<" ";
	fout<<endl;
}