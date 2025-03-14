//https://wintermelonc.github.io/WintermelonC_Docs/zju/basic_courses/data_structure/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 10010
int n,m;
int tot,p[N],np[N];
struct node{
    char id[12];
    char tx[150];
    int val;
}s[N];
int cmp(const void* a,const void* b)
{
    const struct node *x = a;
    const struct node *y = b;
    int v1=x->val,v2=y->val;
    if(v1==v2)
        return strcmp(x->id,y->id);
    else
        return v1-v2;
}
int calc(char *s)
{
    int i,j,n=strlen(s);
    int sum=0;
    for(i=0;i+6<n;i++)
    {
        if((s[i]=='c'||s[i]=='C')&&(s[i+1]=='h'||s[i+1]=='H')&&(s[i+2]=='a'||s[i+2]=='A')&&
        (s[i+3]=='t'||s[i+3]=='T')&&
        (s[i+4]=='g'||s[i+4]=='G')&&
        (s[i+5]=='p'||s[i+5]=='P')&&
        (s[i+6]=='t'||s[i+6]=='T'))
            ++sum;
    }
    return sum;
}
int main()
{
    int i,j,tot0=0;
    //euler();
    scanf("%d\n",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s\n",s[i].id);
        fgets(s[i].tx,150,stdin);
        s[i].val=calc(s[i].tx);
        if(s[i].val>0)
            ++tot0;
    }
    qsort(s+1,n,sizeof(struct node),cmp);
    for(i=0;i<3;i++)    
    {
        printf("%s %d\n",s[i].id,s[i].val);
    }
    
    return 0;
}
/*
1
233
I gonna talk about chatgpt,and Chatgpt,and CHATGPT
*/