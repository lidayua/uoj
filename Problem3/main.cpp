#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<ctime>
#define maxn 200010
using namespace std;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct Edge
{
	int u,v,a,b;
	friend bool operator < (const Edge &a,const Edge &b)
	{
		return a.a<b.a;
	}
}E[maxn];
struct lct_node
{
	lct_node *fa,*son[2],*maxv;
	bool rev;
	int val;
}lct[maxn];
bool Root(lct_node *p)
{
	if(p->fa==0)
		return true;
	return p!=p->fa->son[0]&&p!=p->fa->son[1];
}
void update_rev(lct_node *p)
{
	p->rev^=1;
	swap(p->son[0],p->son[1]);
}
void push_down(lct_node *p)
{
	if(p->rev)
	{
		if(p->son[0])
			update_rev(p->son[0]);
		if(p->son[1])
			update_rev(p->son[1]);
		p->rev=false;
	}
}
void update(lct_node *p)
{
	p->maxv=p;
	if(p->son[0]&&p->maxv->val<p->son[0]->maxv->val)
		p->maxv=p->son[0]->maxv;
	if(p->son[1]&&p->maxv->val<p->son[1]->maxv->val)
		p->maxv=p->son[1]->maxv;
}
void Rotate(lct_node *p,lct_node *x)
{
	bool mark=p==x->son[1];
	lct_node *y=p->son[mark^1],*z=x->fa;
	if(y!=0)
		y->fa=x;
	if(!Root(x))
		z->son[x==z->son[1]]=p;
	p->son[mark^1]=x,p->fa=z,x->son[mark]=y,x->fa=p,update(x);
}
void Splay(lct_node *p)
{
	static lct_node *ancestor[maxn];
	int top=0;
	ancestor[++top]=p;
	for(lct_node *i=p;!Root(i);i=i->fa)
		ancestor[++top]=i->fa;
	for(;top;--top)
		push_down(ancestor[top]);
	while(!Root(p))
	{
		lct_node *x=p->fa,*y=x->fa;
		if(Root(x))
			Rotate(p,x);
		else if((p==x->son[0])^(x==y->son[0]))
			Rotate(p,x),Rotate(p,y);
		else
			Rotate(x,y),Rotate(p,x);
	}
	update(p);
}
void Access(lct_node *p)
{
	for(lct_node *v=0;p;v=p,p=p->fa)
		Splay(p),p->son[1]=v,update(p);
}
lct_node* FindRoot(lct_node *p)
{
	Access(p),Splay(p);
	while(p->son[0])
		p=p->son[0],push_down(p);
	Splay(p);
	return p;
}
void BeRoot(lct_node *a)
{
	Access(a),Splay(a),update_rev(a);
}
void Link(lct_node *a,lct_node *b)
{
	BeRoot(a),a->fa=b;
}
void Cut(lct_node *a,lct_node *b)
{
	BeRoot(a),Access(b),Splay(b);
	a->fa=0,b->son[0]=0,update(b);
}
lct_node* Query(lct_node *a,lct_node *b)
{
	BeRoot(a),Access(b),Splay(b);
	return b->maxv;
}
int n,m;
void read()
{
	Read(n),Read(m);
	for(int i=1;i<=m;++i)
		Read(E[i].u),Read(E[i].v),Read(E[i].a),Read(E[i].b);
	sort(E+1,E+m+1);
}
int work()
{
	int ans=-1,tot=n;
	for(int i=1;i<=n;++i)
		lct[i].maxv=lct+i;
	for(int i=1,j;i<=m;i=j)
	{
		for(j=i;E[j].a==E[i].a;++j)
		{
			if(E[j].u==E[j].v)
				continue;
			if(FindRoot(lct+E[j].u)!=FindRoot(lct+E[j].v))
			{
				tot=n+j;
				lct[tot].maxv=lct+tot;
				lct[tot].val=E[j].b;
				Link(lct+E[j].u,lct+tot),Link(lct+tot,lct+E[j].v);
			}
			else
			{
				lct_node *x=Query(lct+E[j].u,lct+E[j].v);
				if(x->val>E[j].b)
				{
					int id=x-lct-n;
					Cut(lct+E[id].u,x),Cut(lct+E[id].v,x);
					tot=n+j;
					lct[tot].maxv=lct+tot;
					lct[tot].val=E[j].b;
					Link(lct+E[j].u,lct+tot),Link(lct+tot,lct+E[j].v);
				}
		 	}
		}
		if(FindRoot(lct+1)==FindRoot(lct+n))
		{
			lct_node *x=Query(lct+1,lct+n);
			if(ans==-1||ans>E[i].a+x->val)
				ans=E[i].a+x->val;
		}
	}
	return ans;
}
int main()
{
	read();
	printf("%d\n",work());
	return 0;
}
