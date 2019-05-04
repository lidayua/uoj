#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#define maxn 10010
using namespace std;
vector<int> adj[maxn],invadj[maxn];
int n,S,T;
bool can[maxn];
void read()
{
	int m;
	scanf("%d %d",&n,&m);
	for(int i=1,x,y;i<=m;++i)
	{
		scanf("%d %d",&x,&y);
		adj[x].push_back(y),invadj[y].push_back(x);
	}
	scanf("%d %d",&S,&T);
}
void BFS(int T)
{
	queue<int> Q;
	static bool use[maxn];
	Q.push(T),use[T]=true;
	while(!Q.empty())
	{
		int p=Q.front();
		Q.pop();
		for(auto q:invadj[p])
			if(!use[q])
				use[q]=true,Q.push(q);
	}
	for(int i=1;i<=n;++i)
		if(use[i])
		{
			can[i]=true;
			for(auto x:adj[i])
				can[i]&=use[x];
		}
}
int BFS1(int S,int T)
{
	static bool use[maxn];
	static int dis[maxn];
	if(!can[S])
		return -1;
	queue<int> Q;
	Q.push(S),use[S]=true;
	while(!Q.empty())
	{
		int p=Q.front();
		Q.pop();
		if(p==T)
			return dis[p];
		for(auto q:adj[p])
			if(!use[q]&&can[q])
				use[q]=true,Q.push(q),dis[q]=dis[p]+1;
	}
	return -1;
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	BFS(T);
	printf("%d\n",BFS1(S,T));
	return 0;
}