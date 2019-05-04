#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 210
using namespace std;
int map[10][10],n,nA,nB,A[maxn],B[maxn];
void Prepare()
{
	map[0][2]=1,map[0][3]=1,map[1][3]=1,map[2][4]=1,map[3][4]=1;
	for(int i=0;i<=4;++i)
		for(int j=0;j<i;++j)
			map[i][j]=map[j][i]^1;
}
void read()
{
	scanf("%d %d %d",&n,&nA,&nB);
	for(int i=1;i<=nA;++i)
		scanf("%d",A+i);
	for(int i=1;i<=nB;++i)
		scanf("%d",B+i);
}
void print()
{
	int scoreA=0,scoreB=0;
	for(int i=1;i<=n;++i)
	{
		int a=A[(i-1)%nA+1],b=B[(i-1)%nB+1];
		scoreA+=map[a][b],scoreB+=map[b][a];
	}
	printf("%d %d\n",scoreA,scoreB);
}
int main()
{
	Prepare();
	read();
	print();
	return 0;
}