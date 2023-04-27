#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementofStack;
#define Null 0

typedef struct SNode* PtrToSNode;
struct SNode{
    ElementofStack Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Data = Null;
    S->Next = NULL;
    return S;
}
bool IsEmpty(Stack S)
{
    return (S->Next)? false:true;
}
Stack Push(Stack S, ElementofStack X)
{
    PtrToSNode NewNode = (PtrToSNode)malloc(sizeof(struct SNode));
    NewNode->Data = X;
    NewNode->Next = S->Next;
    S->Next = NewNode;
    return S;
}  
bool Pop(Stack S, ElementofStack* X)
{
    if(!IsEmpty(S)){
        *X = S->Next->Data;
        PtrToSNode temp = S->Next;
        S->Next = S->Next->Next;
        free(temp);
        return true;
    }else{
        return false;
    }
}
void DeleteS(Stack S)
{
    PtrToSNode temp = S;
    while(S){
        S = S->Next;
        free(temp);
        temp = S;
    }
}