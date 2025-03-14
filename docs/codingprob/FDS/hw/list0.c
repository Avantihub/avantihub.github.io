#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b )
{
    Polynomial head=malloc(sizeof(struct Node));
    head->Next=NULL;
    PtrToNode p=head;
    int ca,cb;
    while(a->Next&&b->Next)
    {
        PtrToNode temp=malloc(sizeof(struct Node));
        ca=a->Next->Coefficient;
        cb=b->Next->Coefficient;
        if(a->Next->Exponent==b->Next->Exponent)
        {
            if(ca+cb)
            {
                temp->Coefficient=ca+cb;
                temp->Exponent=a->Next->Exponent;
                p->Next=temp;
                p=temp;
            }
            a=a->Next;
            b=b->Next;
        }
        else if(a->Next->Exponent>b->Next->Exponent)
        {
            temp->Coefficient=ca;
            temp->Exponent=a->Next->Exponent;
            p->Next=temp;
            p=temp;
            a=a->Next;
        }
        else
        {
            temp->Coefficient=cb;
            temp->Exponent=b->Next->Exponent;
            p->Next=temp;
            p=temp;
            b=b->Next;
        }
    }
    while(a->Next)
    {
        PtrToNode temp=malloc(sizeof(struct Node));
        temp->Coefficient=a->Next->Coefficient;
        temp->Exponent=a->Next->Exponent;
        p->Next=temp;
        p=temp;
        a=a->Next;
    }
    while(b->Next)
    {
        PtrToNode temp=malloc(sizeof(struct Node));
        temp->Coefficient=b->Next->Coefficient;
        temp->Exponent=b->Next->Exponent;
        p->Next=temp;
        p=temp;
        b=b->Next;
    }
    p->Next=NULL;
    return head;
}

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

/* Your function will be put here */
