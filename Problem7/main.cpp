#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 200010
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	Point() {}
	Point(LL x,LL y): x(x),y(y) {}
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	}
	friend Point operator - (const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
};
typedef Point Vector;
long double Cross(Vector a,Vector b)
{
	return (long double)a.x*b.y-(long double)a.y*b.x;
}
struct Node
{
	LL k,d;
	int id;
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.d>b.d;
	}
};
vector<int> adj[maxn];
int n,fa[maxn];
bool ban[maxn];
LL dis[maxn],limit[maxn],vp[maxn],vq[maxn],dp[maxn];
template<class T>
void Read(T &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	int type;
	Read(n),Read(type);
	LL s;
	fill(dp+2,dp+n+1,1000000000000000000LL);
	for(int i=2,x;i<=n;++i)
	{
		Read(x),Read(s),Read(vp[i]),Read(vq[i]),Read(limit[i]);
		dis[i]=dis[x]+s,adj[i].push_back(x),adj[x].push_back(i),fa[i]=x;
	}
}
void BFS(int p,Node *son,int &n)
{
	static int queue[maxn];
	int front=0,rear=1;
	queue[rear]=p;
	while(front<rear)
	{
		p=queue[++front];
		++n,son[n].id=p,son[n].k=-vp[p],son[n].d=dis[p]-limit[p];
		for(int i=p==1?0:1;i<(int)adj[p].size();++i)
			if(!ban[adj[p][i]])
				queue[++rear]=adj[p][i];
	}
}
int FindRoot(int p)
{
	static int queue[maxn],size[maxn];
	int front=0,rear=1;
	queue[rear]=p;
	while(front<rear)
	{
		int p=queue[++front];
		size[p]=1;
		if(p==1&&!ban[adj[p][0]])
			queue[++rear]=adj[p][0];
		for(int i=1;i<(int)adj[p].size();++i)
			if(!ban[adj[p][i]])
				queue[++rear]=adj[p][i];
	}
	for(int i=rear;i>1;--i)
	{
		int p=queue[i];
		size[adj[p][0]]+=size[p];
	}
	for(int i=2;i<=rear;++i)
	{
		int p=queue[i],maxv=rear-size[p];
		for(int j=1;j<(int)adj[p].size();++j)
			if(!ban[adj[p][j]])
				maxv=max(maxv,size[adj[p][j]]);
		if(maxv*2<=rear)
			return p;
	}
	return p;
}
void solve(int p)
{
	static Point ance[maxn],stack[maxn];
	static Node son[maxn];
	int root=p;
	int n=0,m=0,top=0;
	p=FindRoot(p);
	if(p!=root)
	{
		ban[p]=true;
		solve(root);
		BFS(p,son,m);
		sort(son+1,son+m+1);
		for(int i=adj[p][0];i!=root;i=adj[i][0])
			ance[++n]=Point(dp[i],dis[i]);
		ance[++n]=Point(dp[root],dis[root]);
		for(int i=1,j=1;i<=m;++i)
		{
			if(son[i].d>ance[1].y)
				continue;
			while(j<=n&&ance[j].y>=son[i].d)
			{
				while(top>1&&Cross(ance[j]-stack[top-1],stack[top]-stack[top-1])>=0)
					--top;
				stack[++top]=ance[j++];
			}
			int l=1,r=top;
			while(l<r)
			{
				int mid=(l+r)>>1;
				stack[mid].x+son[i].k*stack[mid].y>=stack[mid+1].x+son[i].k*stack[mid+1].y?l=mid+1:r=mid;
			}
			dp[son[i].id]=min(dp[son[i].id],stack[l].x+son[i].k*stack[l].y+vp[son[i].id]*dis[son[i].id]+vq[son[i].id]);
		}
	}
	else
		BFS(p,son,m);
	for(int i=1;i<=m;++i)
	{
		int x=son[i].id;
		if(son[i].d<=dis[p])
			dp[x]=min(dp[x],dp[p]+(dis[x]-dis[p])*vp[x]+vq[x]);
	}
	for(int i=p==1?0:1;i<(int)adj[p].size();++i)
		if(!ban[adj[p][i]])
			solve(adj[p][i]);
}
void print()
{
	for(int i=2;i<=n;++i)
		printf("%lld\n",dp[i]);
}
int main()
{
	read();
	solve(1);
	print();
	return 0;
}
