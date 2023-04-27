#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementofQueue;

typedef struct QNode* PtrToQNode;
struct QNode{
    ElementofQueue Data;
    PtrToQNode Next;
};
struct Que{
    PtrToQNode Head;
    PtrToQNode Rear;
};
typedef struct Que* Queue;

Queue CreateQ()
{
    Queue Q = (Queue)malloc(sizeof(struct Que));
    Q->Head = NULL;
    Q->Rear = NULL;
    return Q;
}
bool IsEmptyQ(Queue Q)
{
    return (Q->Head)? false:true;
}
Queue InQueue(Queue Q, ElementofQueue X)
{
    PtrToQNode NewNode = (PtrToQNode)malloc(sizeof(struct QNode));
    NewNode->Data = X;
    NewNode->Next = NULL;
    if(IsEmptyQ(Q)){
        Q->Head = NewNode;
        Q->Rear = NewNode;
    }else{
        Q->Rear = NewNode;
    }
    return Q;
}
bool DeQueue(Queue Q, ElementofQueue* X)
{
    if(!IsEmptyQ(Q)){
        *X = Q->Head->Data;
        PtrToQNode temp = Q->Head;
        if(Q->Head->Next){
            Q->Head = Q->Head->Next;
        }else{
            Q->Head = NULL;
            Q->Rear = NULL;
        }
        free(temp);
        return true;
    }else{
        return false;
    }
}
void DeleteQ(Queue Q)
{
    PtrToQNode temp = Q->Head;
    while(temp){
        Q->Head = Q->Head->Next;
        free(temp);
        temp = Q->Head;
    }
    free(Q);
}