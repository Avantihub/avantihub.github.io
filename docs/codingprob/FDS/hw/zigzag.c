#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 50

int n,inord[N],posord[N];
struct node 
{
    int val;
    struct node *l,*r;
};

struct node* build(int il, int ir, int pl, int pr) 
{
    if (pl > pr) return NULL;
    struct node *root = (struct node*)malloc(sizeof(struct node));
    root->val = posord[pr];
    root->l = root->r = NULL;
    int currt;
    for (int i = il; i <= ir; i++) 
    {
        if (inord[i] == root->val) 
        {
            currt = i;
            break;
        }
    }
    int lSize = currt - il;
    root->l = build(il, currt - 1, pl, pl + lSize - 1);
    root->r = build(currt + 1, ir, pl + lSize, pr - 1);
    return root;
}

void zigzag(struct node* root) 
{
    
}
void printprefix(struct node* root) 
{
    if (root == NULL) return;
    printf("%d ", root->val);
    printprefix(root->l);
    printprefix(root->r);
}

int main() 
{
    int T,i,j,ans;

    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&inord[i]);
    }
    for(i=0;i<n;i++)
    {
        scanf("%d",&posord[i]);
    }
    struct node* root = build(0, n - 1 , 0, n - 1);
    
    //zigzag(root); 
    printprefix(root);
    return 0;
}
