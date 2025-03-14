#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 100010
int n,h,b[N];
//If l not unique, output the smallest one
int main()
{
    int T,i,j,k;

    scanf("%d%d",&n,&h);
    for(i=0;i<n;i++)
        scanf("%d",&b[i]);
    int l=0,r=0;
    int p=N,mx=0;
    for(;l<n;l++)
    {
        while(r<n&&b[r]-b[l]<=h)
            r++;
        //r is the first one that b[r]-b[l]>h
        if(r-l>mx)
        {
            mx=r-l;
            p=b[l];
        }
        if(mx==r-l&&b[l]<p)
            p=b[l];
    }
    l=r=n-1;
    for(;r>=0;r--)
    {
        while(l>=0&&b[r]-b[l]<=h)
            l--;
        //l is the first one that b[r]-b[l]>h
        if(r-l>mx)
        {
            mx=r-l;
            p=b[r]-h;
        }
        if(mx==r-l&&b[r]-h<p)
            p=b[r]-h;
    }
    printf("%d %d\n",p,mx);
    return 0;
}