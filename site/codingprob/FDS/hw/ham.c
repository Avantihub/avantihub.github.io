#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 210
int n,m,k,g[N][N]={0},ord[N],n1,a[N*2],vis[N];
int chk()
{
    if(n1!=n+1||a[0]!=a[n1-1])
        return 0;
    memset(vis,0,sizeof(vis));
    int i,j;
    for(i=0;i<n1-1;i++)
    {
        vis[a[i]]=1;
        if(!g[a[i]][a[i+1]])
            return 0;
    }
    vis[a[n1-1]]=1;
    for(i=1;i<=n;i++)
    {
        if(!vis[i])
            return 0;
    }
    return 1;
}
int main()
{
    int i,j,x,y;

    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&x,&y);
    //    printf("Edge number %d: %d %d\n",i+1,x,y);
        g[x][y]=1;
        g[y][x]=1;
    }
    //printf("Edge input done\n");
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d",&n1);
        for(i=0;i<n1;i++)
        {
            scanf("%d",&a[i]);
        }
    /*   printf("Path input *************\n");
        for(i=0;i<n1;i++)
        {
            printf("%d ",a[i]);
        }
        printf("\n");*/
        if(chk())
            printf("YES\n");
        else
            printf("NO\n");
    }
}