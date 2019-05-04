#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 200010
using namespace std;
int Left[maxn];
char str[maxn];
int n,cntL,ansL[maxn],ansR[maxn];
void read()
{
	scanf("%s",str+1);
	n=strlen(str+1)/2;
	for(int i=1;i<=n*2;++i)
		if(str[i]=='(')
			Left[++cntL]=i;
}
void work()
{
	if(cntL!=n)
	{
		printf("-1\n");
		return ;
	}
	int m=0;
	for(int i=1,j=1;i<=n;++i)
		if(str[i]==')')
		{
			while(Left[j]<i)
				++j;
			++m,ansL[m]=i,ansR[m]=Left[j];
			swap(str[i],str[Left[j]]);
			++j;
		}
	printf("%d\n",m);
	for(int i=1;i<=m;++i)
		printf("%d %d\n",ansL[i],ansR[i]);
}
int main()
{
	read();
	work();
	return 0;
}