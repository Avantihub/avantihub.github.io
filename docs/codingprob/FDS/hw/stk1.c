#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1010
int m,n,k;
int a[N];
int stk[N],tp,cur;
int main()
{
    int T,i,j;

    scanf("%d%d%d",&m,&n,&T);
    while(T--)
    {
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);
        tp=0;
        memset(stk,0,sizeof(stk));
        stk[++tp]=1;
        cur=1;
        int fl=1;
        for(i=0;i<n;i++)
        {
            while(a[i]>stk[tp]&&tp<m)
                stk[++tp]=++cur;
            if(a[i]==stk[tp])
                tp--;
            else if(tp>m)
            {
                fl=0;
                break;
            }
            else
            {
                fl=0;
                break;
            }
        }
        if(fl)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
