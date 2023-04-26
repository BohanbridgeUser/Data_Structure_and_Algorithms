#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementofList;
#define Null 0;
typedef struct Node* PtrToNode;
struct Node{
    ElementofList Data;
    PtrToNode Next;
};

PtrToNode Create()
{
    PtrToNode NewNode = (PtrToNode)malloc(sizeof(struct Node));
    NewNode->Data = Null;
    NewNode->Next = NULL;
    return NewNode;
}
bool IsEmpty(PtrToNode L)
{
    return (L->Next)? false:true;
}
PtrToNode Add(PtrToNode L, ElementofList X)
{
    PtrToNode NewNode = (PtrToNode)malloc(sizeof(struct Node));
    NewNode->Data = X;
    NewNode->Next = L->Next;
    L->Next = NewNode;
    return L;
}
ElementofList Del(PtrToNode L)
{
    if(IsEmpty(L)) {
        return Null;
    }
    else {
        ElementofList temp = L->Next->Data;
        PtrToNode t = L->Next;
        L->Next = L->Next->Next;
        free(t);
        return temp;
    }
}

int main()
{
    return 0;
}