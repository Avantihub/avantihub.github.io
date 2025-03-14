//https://wintermelonc.github.io/WintermelonC_Docs/zju/basic_courses/data_structure/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 10010
char s[12][12],ori[N];
int n,m;
// given 0 1 2 3 4 5 6 7 8 9 10
//gap   0 1 2 3 4 5 6 7 8 9,star[i]=1 -> marked
//  l=2,len=3,  star[2,5]
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    int t=n,A=0;
    while(t)
    {
        A+=t%10;
        t/=10;
    }
    int tt=m,B=1;
    while(tt)
    {
        B*=tt%10;
        tt/=10;
    }
//    printf("A=%d B=%d\n",A,B);
    int pw=1,ta=A,tb=B;
    if(A>B)
    {
        while(tb)
        {
            pw*=10;
            tb/=10;
        }
        if(B==0)
            pw=10;
        printf("%lld\n",1ll*pw*A+B);
    }
    else{
        while(ta)
        {
            pw*=10;
            ta/=10;
        }
        if(A==0)
            pw=10;
        printf("%lld\n",1ll*pw*B+A);
    }
    return 0;
}