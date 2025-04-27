// https://vjudge.net/contest/352513#problem/C
// HDU- 1272
#include <cstdio>
#include <algorithm>
const int N=1e5+10;
using namespace std;
int n,f[N],vis[N],flag;
inline int sf(int x){return x==f[x]?x:f[x]=sf(f[x]);}
inline void merge(int x,int y)
{
	int xx=sf(x),yy=sf(y);
	if(xx==yy){flag=1;return ;}
	f[xx]=yy;
}
int main()
{
	int x,y;
	while(scanf("%d%d",&x,&y)==2,(~x||~y))
    {
		if(!x&&!y){puts("Yes");continue;}
		for(int i=1;i<N;i++) 
            f[i]=i,vis[i]=0;
		flag=0,merge(x,y),vis[x]=vis[y]=1;
		while(scanf("%d%d",&x,&y)==2,(x||y))
			merge(x,y),vis[x]=vis[y]=1;
		if(flag) puts("No");
        else
        {
			int cnt=0;
			for(int i=1;i<N;i++)
				if(f[i]==i&&vis[i]) cnt++;
			if(cnt==1) puts("Yes");
            else puts("No");	
		}
	}
}