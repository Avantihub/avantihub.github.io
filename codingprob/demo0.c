#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define N 10010

void print(int x)
{
    if(x<10)
    {
        printf("0%d",x);
    }
    else
    {
        printf("%d",x);
    }
}
int main()
{
    int a[100], x, i, n;
    int h,m,s;
    char x1,x2;
    scanf("%c%c",&x1,&x2);
    h=(x1-'0')*10+(x2-'0');
    getchar();
    scanf("%c%c",&x1,&x2);
    m=(x1-'0')*10+(x2-'0');
    getchar();
    scanf("%c%c",&x1,&x2);
    s=(x1-'0')*10+(x2-'0');
    scanf("%d",&n);
    s+=n;
    if(s>=60)
    {
        m+=s/60;
        s%=60;
    }
    if(m>=60)
    {
        h+=m/60;
        m%=60;
    }
    if(h>=24)
    {
        h%=24;
    }
    print(h);
    printf(":");
    print(m);
    printf(":");
    print(s);
        
    return 0;
}