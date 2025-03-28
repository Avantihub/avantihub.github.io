#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 10010
int n,a[N],h[N]={0};
void percup(int p)
{
    int i,x=a[p];
    for(i=p;a[i/2]>x;i/=2)
        a[i]=a[i/2];
    a[i]=x;
}
void percdown(int p)
{
    int i,x=a[p];
    for(i=p*2;i<=n;i*=2)
    {
        if(i<n&&a[i]>a[i+1]) i++;
        if(x<=a[i]) break;
        a[i/2]=a[i];
    }
    a[i/2]=x;
}
void inord(int x)
{
    if(x>n) return;
    inord(x*2);
    h[x]=a[++h[0]];
    inord(x*2+1);
}
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
int main()
{
    int T,i,j;

    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    qsort(a+1,n,sizeof(int),cmp);
    inord(1);
    printf("%d",h[1]);
    for(i=2;i<=n;i++)
        printf(" %d",h[i]);
    printf("\n");
    return 0;
}