#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 300010
using namespace std;
typedef long long LL;
struct Task
{
	int t,s,id,used,p;
	Task() {}
	friend bool operator < (const Task &a,const Task &b)
	{
		return a.p<b.p;
	}
}task[maxn],sort_task[maxn];
bool cmp(const Task &a,const Task &b)
{
	return a.t<b.t;
}
LL T,ans[maxn];
int n,x;
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d %d",&task[i].t,&task[i].s,&task[i].p);
		task[i].id=i;
		if(task[i].p==-1)
			x=i;
	}
	cin>>T;
}
void solve()
{
	memcpy(sort_task, task, sizeof(task));
	sort(sort_task+1,sort_task+n+1,cmp);
	priority_queue<Task> Q;
	LL now=0;
	for(int i=1,j=1;i<=n;i=j)
	{
		LL last=now;
		now=sort_task[i].t;
		while(!Q.empty()&&Q.top().s+last<=now)
		{
			Task t=Q.top();
			if(last>=task[x].t&&last<=T)
				task[t.id].used+=min((LL)Q.top().s,T-last);
			last+=t.s;
			Q.pop();
		}
		if(!Q.empty())
		{
			Task a=Q.top();
			a.s-=now-last;
			if(last>=task[x].t&&last<=T)
				task[a.id].used+=min(T,now)-last;
			Q.pop(),Q.push(a);
		}
		for(;sort_task[j].t==sort_task[i].t;++j)
			Q.push(sort_task[j]);
	}
	while(!Q.empty())
	{
		Task a=Q.top();
		LL last=now;
		now+=Q.top().s;
		if(last>=task[x].t&&last<=T)
			task[a.id].used+=min(T,now)-last;
		Q.pop();
	}
	sort(task+1,task+n+1);
	now=0;
	for(int i=1;i<=n;++i)
	{
		now+=task[i].used;
		if(now==task[1].s&&i!=1&&(task[i].p+1<task[i+1].p||i==n))
		{
			task[1].p=task[i].p+1;
			break;
		}
	}
	task[1].p=max(task[1].p,1);
	printf("%d\n",task[1].p);
	memcpy(sort_task, task, sizeof(task));
	sort(sort_task+1,sort_task+n+1,cmp);
	now=0;
	for(int i=1,j=1;i<=n;i=j)
	{
		LL last=now;
		now=sort_task[i].t;
		while(!Q.empty()&&Q.top().s+last<=now)
		{
			Task t=Q.top();
			last+=t.s;
			ans[t.id]=last;
			Q.pop();
		}
		if(!Q.empty())
		{
			Task a=Q.top();
			a.s-=now-last;
			Q.pop(),Q.push(a);
		}
		for(;sort_task[j].t==sort_task[i].t;++j)
			Q.push(sort_task[j]);
	}
	while(!Q.empty())
	{
		Task a=Q.top();
		now+=Q.top().s;
		ans[a.id]=now;
		Q.pop();
	}
	for(int i=1;i<=n;++i)
		printf("%lld%c",ans[i],i<n?' ':'\n');
}
int main()
{
	read();
	solve();
	return 0;
}
