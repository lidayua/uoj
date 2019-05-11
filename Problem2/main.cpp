#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cctype>
#define maxn 100010
using namespace std;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
int type[maxn],x[maxn],n,m;
void read()
{
	Read(n),Read(m);
	char c;
	for(int i=1;i<=n;++i)
	{
		for(c=getchar();!isalpha(c);c=getchar());
		if(c=='O')
			type[i]=1;
		if(c=='X')
			type[i]=2;
		Read(x[i]);
	}
}
int work()
{
	int v1=0,v2;
	for(v2=1;v2<m;v2=v2<<1|1);
	for(int i=1;i<=n;++i)
	{
		if(type[i]==0)
			v1&=x[i],v2&=x[i];
		if(type[i]==1)
			v1|=x[i],v2|=x[i];
		if(type[i]==2)
			v1^=x[i],v2^=x[i];
	}
	bool mark=false;
	int ans=0;
	for(int i=30;i>=1;--i)
	{
		int val=v1>>(i-1)&1;
		if(((m>>(i-1)&1)||mark)&&(v2>>(i-1)&1)>val)
			val=v2>>(i-1)&1;
		else if(m>>(i-1)&1)
			mark=true;
		ans|=val<<(i-1);
	}
	return ans;
}
int main()
{
	read();
	printf("%d\n",work());
	return 0;
}