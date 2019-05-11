#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cctype>
#define maxn 5010
using namespace std;
typedef long long LL;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
int nRow,nCol,seq[maxn*maxn],rank[maxn*maxn];
int pre[maxn],suf[maxn];
void read()
{
	LL x,a,b,c,d;
	int nQ;
	cin>>x>>a>>b>>c>>d>>nRow>>nCol>>nQ;
	for(int i=1;i<=nRow*nCol;++i)
	{
		seq[i]=i,x=(a*x*x+b*x+c)%d;
		swap(seq[i],seq[x%i+1]);
	}
	for(int i=1,x,y;i<=nQ;++i)
	{
		Read(x),Read(y);
		swap(seq[x],seq[y]);
	}
	for(int i=1;i<=nRow*nCol;++i)
		rank[seq[i]]=i;
}
void print()
{
	fill(suf+1,suf+nRow+2,1<<30);
	static int ans[maxn*2];
	int tot=0;
	for(int i=1;i<=nRow*nCol;++i)
	{
		int id=rank[i],x=(id-1)/nCol+1,y=(id-1)%nCol+1;
		if(pre[x-1]<=y&&suf[x+1]>=y)
		{
			ans[++tot]=i;
			for(int j=x;j<=nRow&&pre[j]<y;++j)
				pre[j]=y;
			for(int j=x;j>=1&&suf[j]>y;--j)
				suf[j]=y;
		}
	}
	for(int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i<tot?' ':'\n');
}
int main()
{
	read();
	print();
	return 0;
}
