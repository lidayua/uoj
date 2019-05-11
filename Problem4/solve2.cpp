#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#include<ctime>
#include<algorithm>
#define maxn 20
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
	if(!(n&1))
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
int main()
{
	srand(time(0));
	freopen("game2.in","r",stdin);
	// freopen("game2.out","w",stdout);
	scanf("%d %d %d %d %d %d %d %d",&n,&m,&K,&lmin,&lmax,&c1,&c2,&F);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	int maxv=0;
	memcpy(tmp,a,sizeof(a));
	for(int T=1;T<=1000;++T)
	{
		int score=0;
		vector<vector<int>> sol;
		for(int _=1;_<=K;++_)
		{
			if(!CountNonzero())
				break;
			for(int t=1;t<=100;++t)
			{
				vector<pair<int,int>> can;
				for(int i=1;i<=n;++i)
					for(int j=1;j<=m;++j)
						if(a[i][j]!=0&&a[i][j]!=-1)
						{
							can.push_back(make_pair(i,j));
							break;
						}
				if(SIZE(can)==0)
					continue;
				int id=randint(0,SIZE(can)-1);
				int x=can[id].first,y=can[id].second;
				vector<int> cor;
				cor.push_back(x),cor.push_back(y);
				string s="";
				s.append(1u,a[x][y]+'0');
				a[x][y]=-1;
				for(int i=1;i<8;++i)
				{
					vector<pair<int,int>> can;
					for(int j=0;j<4;++j)
					{
						int px=x+movex[j],py=y+movey[j];
						if(px>=1&&px<=n&&py>=1&&py<=m&&a[px][py]!=-1)
							can.push_back(make_pair(px,py));
					}
					if(SIZE(can)==0)
						break;
					id=randint(0,SIZE(can)-1);
					x=can[id].first,y=can[id].second;
					s.append(1u,a[x][y]+'0');
					cor.push_back(x),cor.push_back(y);
					a[x][y]=-1;
					if(isPrime(s)||isPalin(s))
						break;
				}
				// printf("%d ",t);
				if(SIZE(s)<2||(!isPrime(s)&&!isPalin(s)))
				{
					for(int i=0;i<SIZE(cor);i+=2)
						a[cor[i]][cor[i+1]]=s[i/2]-'0';
					continue;
				}
				if(SIZE(s)==1)
					continue;
				if(isPrime(s))
					++score;
				if(isPalin(s))
					++score;
				score+=SIZE(s);
				sol.push_back(cor);
				remove();
				break;
			}
			// printf("\n");
			
			// for(int i=1;i<=n;++i,printf("\n"))
				// for(int j=1;j<=m;++j)
					// printf("%d ",a[i][j]);
			// printf("\n");
		}
		if(CountNonzero())
			score/=2;
		printf("%d %d %d\n",T,CountNonzero(),score);
		if(maxv<score)
			maxv=score,ans=sol;
		memcpy(a,tmp,sizeof(a));
	}
	printf("%d\n",maxv);
	printf("%d\n",SIZE(ans));
	for(auto x:ans)
	{
		printf("%d ",SIZE(x)/2);
		for(auto y:x)
			printf("%d ",y);
		printf("\n");
	}
}