#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef int ElementofStack;
struct HeadNode {
    ElementofStack* Data;
    int* HI;
    int* Loc;
    int Head;
    int Size;
};
typedef struct HeadNode* Stack;

#define MaxHeap 100001
#define MinHeap -1
typedef int ElementofHeap;
struct HNode {
    ElementofHeap* Data;
    int Size;
};
typedef struct HNode* Heap;

Heap CreateMinH()
{
    Heap H = (Heap)malloc(sizeof(struct HNode));
    H->Data = (ElementofHeap*)malloc(200000 * sizeof(ElementofHeap));
    H->Data[0] = MinHeap;
    H->Size = 0;
    return H;
}
Heap InHeapMin(Heap H, Stack S, ElementofHeap X)
{
    int Child = ++H->Size;
    for (; Child > 1 && S->Data[X] < S->Data[H->Data[Child / 2]]; Child /= 2) {
        H->Data[Child] = H->Data[Child / 2];
        S->Loc[H->Data[Child / 2]] = Child;
    }
    H->Data[Child] = X;
    S->Loc[X] = Child;
    return H;
}
int IsEmptyH(Heap H) 
{
    return H->Size ? 0 : 1;
}
ElementofHeap DeHeapMin(Heap H, Stack S)
{
    ElementofHeap RET = -1;
    if (!IsEmptyH(H)) {
        RET = H->Data[1];
        ElementofHeap X = H->Data[H->Size--];
        int Parent, Child;
        for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && S->Data[H->Data[Child]] > S->Data[H->Data[Child + 1]])
                Child += 1;
            if (S->Data[H->Data[Child]] < S->Data[X]) {
                H->Data[Parent] = H->Data[Child];
                S->Loc[H->Data[Child]] = Parent;
            }
            else break;
        }
        H->Data[Parent] = X;
        S->Loc[X] = Parent;
    }
    return RET;
}
Heap CreateMaxH()
{
    Heap H = (Heap)malloc(sizeof(struct HNode));
    H->Data = (ElementofHeap*)malloc(200000 * sizeof(ElementofHeap));
    H->Data[0] = MaxHeap;
    H->Size = 0;
    return H;
}
Heap InHeapMax(Heap H,Stack S, ElementofHeap X)
{
    int Child = ++H->Size;
    for (; Child > 1 && S->Data[X] > S->Data[H->Data[Child / 2]]; Child /= 2) {
        H->Data[Child] = H->Data[Child / 2];
        S->Loc[H->Data[Child / 2]] = Child;
    }
    H->Data[Child] = X;
    S->Loc[X] = Child;
    return H;
}
ElementofHeap DeHeapMax(Heap H, Stack S)
{
    ElementofHeap RET = -1;
    if (!IsEmptyH(H)) {
        RET = H->Data[1];
        ElementofHeap X = H->Data[H->Size--];
        int Parent, Child;
        for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && S->Data[H->Data[Child]] < S->Data[H->Data[Child + 1]])
                Child += 1;
            if (S->Data[H->Data[Child]] > S->Data[X]) {
                H->Data[Parent] = H->Data[Child];
                S->Loc[H->Data[Child]] = Parent;
            }
            else break;
        }
        H->Data[Parent] = X;
        S->Loc[X] = Parent;
    }
    return RET;
}
Stack CreateS()
{
    Stack S = (Stack)malloc(sizeof(struct HeadNode));
    S->Data = (ElementofStack*)malloc(100000 * sizeof(ElementofStack));
    S->HI = (int*)malloc(100000 * sizeof(int));
    S->Loc = (int*)malloc(100000 * sizeof(int));
    for (int i = 0; i < 100000; i++) {
        S->Data[i] = -1;
        S->HI[i] = -1;
        S->Loc[i] = -1;
    }
    S->Head = 100000;
    S->Size = 0;
    return S;
}
int IsEmpty(Stack S)
{
    return S->Size ? 0 : 1;
}
void BalanceH(Heap MaxH, Heap MinH, Stack S)
{
    if (MaxH->Size > MinH->Size + 1) {
        ElementofHeap tmp = DeHeapMax(MaxH, S);
        InHeapMin(MinH, S, tmp);
        S->HI[tmp] = 1;
    }
    else if (MaxH->Size < MinH->Size) {
        ElementofHeap tmp = DeHeapMin(MinH, S);
        InHeapMax(MaxH, S, tmp);
        S->HI[tmp] = 0;
    }
}
Stack Push(Stack S, Heap MinH, Heap MaxH, ElementofStack X) 
{
    S->Data[--S->Head] = X;
    S->Size++;
    if (IsEmptyH(MinH) && IsEmptyH(MaxH)) {
        InHeapMax(MaxH, S, S->Head);
        S->HI[S->Head] = 0;
    }
    else {
        //printf("\nX=%d,MaxH->Data[1] = %d\n", X, S->Data[MaxH->Data[1]]);
        if (X > S->Data[MaxH->Data[1]]) {
            InHeapMin(MinH, S, S->Head);
            S->HI[S->Head] = 1;
        }
        else {
            InHeapMax(MaxH, S, S->Head);
            S->HI[S->Head] = 0;
        }
    }
   /* printf("Max =");
    for (int i = 1; i <= MaxH->Size; i++) {
        if (MaxH->Data[i] >= 0 && MaxH->Data[i] <= 100000) printf("%d ", S->Data[MaxH->Data[i]]);
    }
    printf("\n");
    printf("Min =");
    for (int i = 1; i <= MinH->Size; i++) {
        if (MinH->Data[i] >= 0 && MinH->Data[i] <= 100000)printf("%d ", S->Data[MinH->Data[i]]);
    }
    printf("\n");*/
    BalanceH(MaxH, MinH, S);
    /*printf("Sb=");
    for (int i = 99999; i > 99990; i--) printf("%d\n", S->Data[i]);*/
    return S;
}
void DaSMaxH(Heap H, Stack S, ElementofHeap i)
{
    ElementofHeap RET = -1;
    if (!IsEmptyH(H)) {
        RET = H->Data[i];
        ElementofHeap X = H->Data[H->Size--];
        int Parent, Child;
        for (Parent = i; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && S->Data[H->Data[Child]] < S->Data[H->Data[Child + 1]])
                Child += 1;
            if (S->Data[H->Data[Child]] > S->Data[X]) {
                H->Data[Parent] = H->Data[Child];
                S->Loc[H->Data[Child]] = Parent;
            }
            else break;
        }
        H->Data[Parent] = X;
        S->Loc[X] = Parent;
    }
}
void DaSMinH(Heap H, Stack S, ElementofHeap i)
{
    ElementofHeap RET = -1;
    if (!IsEmptyH(H)) {
        RET = H->Data[i];
        ElementofHeap X = H->Data[H->Size--];
        int Parent, Child;
        for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && S->Data[H->Data[Child]] > S->Data[H->Data[Child + 1]])
                Child += 1;
            if (S->Data[H->Data[Child]] < S->Data[X]) {
                H->Data[Parent] = H->Data[Child];
                S->Loc[H->Data[Child]] = Parent;
            }
            else break;
        }
        H->Data[Parent] = X;
        S->Loc[X] = Parent;
    }
}
ElementofStack Pop(Stack S, Heap MaxH, Heap MinH)
{
    if (!IsEmpty(S)) {
        ElementofStack RET = S->Data[S->Head];
        if (S->HI[S->Head] == 0) {
            DaSMaxH(MaxH, S, S->Loc[S->Head]);
        }
        else {
            DaSMinH(MinH, S, S->Loc[S->Head]);
        }   
        S->Head++;
        S->Size--;
        BalanceH(MaxH, MinH, S);
        return RET;
    }
    else {
        printf("Invalid\n");
        return -1;
    }
}
ElementofStack PeepMedian(Stack S,Heap MaxH,Heap MinH) 
{
    if (!IsEmptyH(MaxH)) {
        return S->Data[MaxH->Data[1]];
    }
    else {
        printf("Invalid\n");
        return -1;
    }
}
int main()
{
    int N;
    scanf("%d\n", &N);
    Stack S = CreateS();
    Heap MinH = CreateMinH();
    Heap MaxH = CreateMaxH();
    for (int i = 0; i < N; i++) {
        char* Input = (char*)malloc(12 * sizeof(char));
        scanf("%[^\n]", Input);
        getchar();
        if (strncmp(Input, "Push", 4) == 0) {
            char* value = (char*)malloc(7 * sizeof(char));
            memset(value, '\0', 7);
            int j = 0;
            for (int k = 5; k < strlen(Input); k++) {
                value[j++] = Input[k];
            }
            int v = atoi(value);
            S = Push(S, MinH, MaxH, v);
        }
        else if(strncmp(Input,"Pop",3)==0){
            int ret = Pop(S,MaxH,MinH);
            if (ret != -1) printf("%d\n", ret);
        }
        else if (strncmp(Input, "PeekMedian", 10) == 0) {
            int ret = PeepMedian(S,MaxH,MinH);
            if (ret != -1) printf("%d\n", ret);
        }
        /*printf("S =");
        for (int i = 99999; i > 99999-S->Size; i--) printf("%d ", S->Data[i]);
        printf("\n");
        printf("Max =");
        for (int i = 1; i <= MaxH->Size; i++) {
            if(MaxH->Data[i] >= 0 && MaxH->Data[i] <= 100000) printf("%d ", S->Data[MaxH->Data[i]]);
        }
        printf("\n");
        printf("Min =");
        for (int i = 1; i <= MinH->Size; i++) {
            if(MinH->Data[i] >=0 && MinH->Data[i] <= 100000)printf("%d ", S->Data[MinH->Data[i]]);
        }
        printf("\n");*/
    }
    return 0;
}
