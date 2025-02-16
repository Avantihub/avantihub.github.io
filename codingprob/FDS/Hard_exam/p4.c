//https://wintermelonc.github.io/WintermelonC_Docs/zju/basic_courses/data_structure/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 10010
char s[12][12],ori[N];
int n,m,a[N],star[N]={0};
// given 0 1 2 3 4 5 6 7 8 9 10
//gap   0 1 2 3 4 5 6 7 8 9,star[i]=1 -> marked
//  l=2,len=3,  star[2,5]
int main()
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",s[i]);
    }
    scanf("%s",ori);
    m=strlen(ori);
    int l,r,len,fl;
    for(i=0;i<n;i++)//for each slang
    {
        len=strlen(s[i]);
        for(l=0;l<m;l++)//for each position
        {
            fl=1;
            for(j=0;j<len;j++)//for each length
            {
                if(ori[l+j]!=s[i][j])
                {
                    fl=0;
                    break;
                }
            }
            if(fl)
            {
                star[l]++;
                star[l+len]++;
            }
        }
    }
    int cnt;
    for(i=0;i<m;i++)
    {
        cnt=star[i];
        while(cnt--)
        {
            printf("*");
        }
        printf("%c",ori[i]);
    }
    cnt=star[m];
    while(cnt--)
    {
        printf("*");
    }
    printf("\n");
    return 0;
}