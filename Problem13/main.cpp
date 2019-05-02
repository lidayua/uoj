#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 20010
#define maxm 500010
using namespace std;
int encode(char c)
{
	if(c>='a'&&c<='z')
		return c-'a';
	return 26;
}
struct TrieNode
{
	int son[27],ancestor,father;
	bool flag;
	char c;
}Tree[maxm];
int n,m,cnt,root;
char stra[maxm],strb[maxm];
int Insert(char *a)
{
	int p=root;
	for(int i=0;a[i];++i)
	{
		int x=encode(a[i]);
		if(Tree[p].flag&&x==26)
			p=Tree[p].ancestor;
		if(x==26&&p==0)
			continue;
		if(!Tree[p].son[x])
		{
			Tree[p].son[x]=++cnt;
			Tree[cnt].c=a[i];
			Tree[cnt].father=p;
		}
		p=Tree[p].son[x];
	}
	if(Tree[p].flag)
		p=Tree[p].ancestor;
	return p;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%s %s",stra,strb);
		int a=Insert(stra),b=Insert(strb);
		if(Tree[b].ancestor==0)
			Tree[b].ancestor=b;
		Tree[a].ancestor=Tree[b].ancestor;
		Tree[a].flag=Tree[b].flag=true;
	}
	static char stack[maxm];
	for(int i=1;i<=m;++i)
	{
		scanf("%s",stra);
		int a=Insert(stra),top=0;
		for(int j=a;j;j=Tree[j].father)
			stack[++top]=Tree[j].c;
		putchar('/');
		while(top)
			printf("%c",stack[top--]);
		printf("\n");
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