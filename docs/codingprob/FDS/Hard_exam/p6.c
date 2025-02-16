//https://wintermelonc.github.io/WintermelonC_Docs/zju/basic_courses/data_structure/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 100010
int n,m,A,B,s[20];
int tot,p[N],np[N];
void euler()
{
    np[1]=1;
    np[2]=0;
    for(int i=2;i<N;i++)
    {
        if(!np[i])
            p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<N;j++)
        {
            np[i*p[j]]=1;
            if(i%p[j]==0)
                break;
        }
    }
}
void sieve(int x)
{
    for(int i=A;i<=B;i++)
    {
        if(i%x==0)
        {
            for(int j=i;j<=B;j+=i)
                if(!np[j])
                    np[j]=1;
        }
    }
}
int main()
{
    int i,j;
    //euler();
    scanf("%d%d%d",&A,&B,&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&s[i]);
        sieve(s[i]);
    }
    int cnt=0;
    for(i=A;i<=B;i++)
        if(np[i]==0)
        {
            for(j=2;j<=i/2;j++)
            {
                if(i%j==0)
                {
                    ++cnt;
                    break;
                }
            }
        }
    printf("%d\n",cnt);
    return 0;
}