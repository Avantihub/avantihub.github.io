#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L )
{
    Position pre = NULL;
    Position curr = L->Next;
    Position nxt;
    while (curr) {
        nxt = curr->Next;
        curr->Next = pre;
        pre = curr;
        curr = nxt;
    }   
    L->Next = pre;
    return L;
}
/* 如果要优化内存使用，可以采用原地逆序的方法：
    Position prev = NULL;
    Position current = L->Next;
    Position next;
    
    while (current) {
        next = current->Next;
        current->Next = prev;
        prev = current;
        current = next;
    }
    
    L->Next = prev;
    return L;
    */
int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* Your function will be put here */
