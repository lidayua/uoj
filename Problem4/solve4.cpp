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
#define maxn 110
#define SIZE(x) (int)((x).size())
using namespace std;
typedef long long LL;
typedef unsigned int uint;
inline LL mul(LL p,LL n,LL mo)
{
	LL ans=0;
	while(n)
	{
		if(n&1)
		{
			ans+=p;
			if(ans>=mo)
				ans-=mo;
		}
		n>>=1,p<<=1;
		if(p>=mo)
			p-=mo;
	}
	return ans;
}
inline LL power(LL p,LL n,LL mo)
{
	LL ans=1;
	for(;n;n>>=1,p=mul(p,p,mo))
		if(n&1)
			ans=mul(ans,p,mo);
	return ans;
}
inline bool Miller_Rabin(int p,LL n)
{
	int s=0;
	LL d=n-1;
	while(!(d&1))
		++s,d>>=1;
	LL w=power(p,d,n);
	if(w==1)
		return true;
	for(int i=0;i<=s-1;++i)
	{
		if(w==n-1)
			return true;
		w=mul(w,w,n);
	}
	return false;
}
inline bool isPrime(LL n)
{
	static int prime[]={2,3,5,7,11,13,17,19,23};
	if(n==1)
		return false;
	if(find(prime,prime+9,n)!=prime+9)
		return true;
	for(int i=0;i<9;++i)
		if(n%prime[i]==0)
			return false;
	for(int i=0;i<9;++i)
		if(!Miller_Rabin(prime[i],n))
			return false;
	return true;
}
bool isPrime(string str)
{
	LL n=0;
	for(int i=0;i<str.size();++i)
		n=n*10+str[i]-'0';
	return isPrime(n);
}
bool isPalin(string str)
{
	int i=0,j=SIZE(str)-1;
	while(i<j)
		if(str[i++]!=str[j--])
			return false;
	return true;
}
int n,m,K,lmin,lmax,c1,c2,F,a[maxn][maxn],tmp[maxn][maxn];
vector<vector<int>> ans;
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
void remove()
{
	bool flag=true;
	while(flag)
	{
		flag=false;
		for(int i=1;i<n;++i)
			for(int j=1;j<=m;++j)
				if(a[i][j]!=-1&&a[i+1][j]==-1)
					a[i+1][j]=a[i][j],a[i][j]=-1,flag=true;
	}
}
int CountNonzero()
{
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]!=-1)
				++cnt;
	return cnt;
}
bool DFS(int depth,int x,int y,vector<int> &cor,string &s)
{
	if(depth==18)
	{
		if(isPrime(s))
			return true;
		return false;
	}
	char t=a[x][y]+'0';
	a[x][y]=-1;
	cor.push_back(x);
	cor.push_back(y);
	s.push_back(t);
	for(int i=0;i<4;++i)
	{
		int px=x+movex[i],py=y+movey[i];
		if(px>=1&&px<=n&&py>=1&&py<=n&&a[px][py]!=-1)
			if(DFS(depth+1,px,py,cor,s))
				return true;
	}
	cor.pop_back(),cor.pop_back();
	s.pop_back();
	a[x][y]=t-'0';
	return false;
}
void print()
{
	for(int i=1;i<=n;++i,printf("\n"))
		for(int j=1;j<=m;++j)
			printf("%2d ",a[i][j]);
}
int main()
{
	srand(time(0));
	freopen("game4.in","r",stdin);
	ofstream fout("game4.out");
	scanf("%d %d %d %d %d %d %d %d",&n,&m,&K,&lmin,&lmax,&c1,&c2,&F);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	int maxv=0;
	memcpy(tmp,a,sizeof(a));
	for(int T=1;T<=1;++T)
	{
		int score=0;
		vector<vector<int>> sol;
		for(int _=1;_<=K;++_)
		{
			vector<int> path;
			string s;
			bool mark=true;
			for(int i=1;i<=n&&mark;++i)
				for(int j=1;j<=m&&mark;++j)
					if(a[i][j]!=-1&&a[i][j]!=0)
					{
						DFS(0,i,j,path,s);
						if(!isPrime(s))
						{
							for(int k=0;k<SIZE(path);k+=2)
								a[path[k]][path[k+1]]=s[k]-'0';
							path.clear();
							s.clear();
						}
						else
							mark=false;
					}
			if(isPrime(s))
				score+=18*18;
			else
				printf("fuck\n");
			if(isPalin(s))
				++score;
			sol.push_back(path);
			printf("%d %d\n",_,score);
			remove();
		}
		printf("%d %d\n",T,score);
		if(maxv<score)
			maxv=score,ans=sol;
		memcpy(a,tmp,sizeof(a));
	}
	printf("%d\n",maxv);
	fout<<SIZE(ans)<<endl;
	for(auto x:ans)
	{
		fout<<SIZE(x)/2<<" ";
		for(auto y:x)
			fout<<y<<" ";
		fout<<endl;
	}
}