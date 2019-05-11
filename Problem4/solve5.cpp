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
int DFS(int depth,int maxd,int x,int y,vector<int> &cor,string &s,vector<int> &ans_cor,string &ans_s,int &ans)
{
	if(depth==maxd)
	{
		int score=0;
		if(isPrime(s))
			score+=maxd*maxd;
		if(isPalin(s))
			score+=maxd*maxd;
		if(ans<score)
			ans=score,ans_cor=cor,ans_s=s;
		else if(ans==score&&rand()&1)
			ans=score,ans_cor=cor,ans_s=s;
		return score;
	}
	char t=a[x][y]+'0';
	a[x][y]=-1;
	cor.push_back(x);
	cor.push_back(y);
	s.push_back(t);
	int score=0;
	for(int i=0;i<4;++i)
	{
		int px=x+movex[i],py=y+movey[i];
		if(px>=1&&px<=n&&py>=1&&py<=n&&a[px][py]!=-1)
		{
			score=max(score,DFS(depth+1,maxd,px,py,cor,s,ans_cor,ans_s,ans));
			if(score==maxd*maxd*2)
				break;
		}
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
	freopen("game5.in","r",stdin);
	ofstream fout("game5.out");
	scanf("%d %d %d %d %d %d %d %d",&n,&m,&K,&lmin,&lmax,&c1,&c2,&F);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	int maxv=0;
	memcpy(tmp,a,sizeof(a));
	for(int T=1;T<=10;++T)
	{
		int score=0;
		vector<vector<int>> sol;
		for(int _=1;_<=K;++_)
			for(int maxd=8;maxd>=2;--maxd)
			{
				vector<int> path,tmppath;
				string s,tmps;
				int maxv=0;
				bool mark=true;
				for(int i=1;i<=n&&mark;++i)
					for(int j=1;j<=m&&mark;++j)
						if(a[i][j]!=-1&&a[i][j]!=0)
						{
							DFS(0,maxd,i,j,tmppath,tmps,path,s,maxv);
							if(maxv==maxd*maxd*2)
								mark=false;
						}
				for(int i=0;i<SIZE(path);i+=2)
					a[path[i]][path[i+1]]=-1;
				
				if(s=="")
					continue;
				if(isPrime(s))
					score+=maxd*maxd;
				if(isPalin(s))
					score+=maxd*maxd;
				sol.push_back(path);
				printf("%d %d\n",_,score);
				remove();
				// print();
				break;
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