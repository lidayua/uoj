#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<set>
#define maxn 10010
using namespace std;
pair<int,string> name[maxn];
int n;
int main()
{
	char str[50];
	string file;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		cin>>file;
		name[i]=make_pair(file.length(),file);
	}
	sort(name+1,name+n+1);
	for(int i=1;i<=n;++i)
		cout<<name[i].second<<endl;
	return 0;
}
