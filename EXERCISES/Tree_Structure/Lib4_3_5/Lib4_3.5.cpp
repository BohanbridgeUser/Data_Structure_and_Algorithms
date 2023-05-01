#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

typedef struct TNode* PtrToTNode;
struct TNode {
    char C;
    int Weight;
    int Layer;
    PtrToTNode Left;
    PtrToTNode Right;
};
typedef PtrToTNode BinTree;

PtrToTNode* Input(int N)
{
    PtrToTNode* I = new PtrToTNode[N];
    for (int i = 0; i < N; i++) {
        I[i] = new TNode;
    }
    for (int i = 0; i < N; i++) {
        cin >> I[i]->C;
        cin.get();
        cin >> I[i]->Weight;
        cin.get();
        I[i]->Left = NULL;
        I[i]->Right = NULL;
    }
    return I;
}

/* Heap */
typedef PtrToTNode ElementofHeap;
typedef struct HNode* Heap;
struct HNode {
    ElementofHeap* Data;
    int Size;
};

Heap CreateH()
{
    Heap H = new HNode;
    H->Data = new ElementofHeap[64];
    H->Size = 0;
    return H;
}
int IsEmptyH(Heap H)
{
    if (H->Size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
Heap Push(Heap H,ElementofHeap X) 
{
    H->Data[++H->Size] = X;
    int Child = H->Size;
    while (Child / 2!= 0&&H->Data[Child]->Weight < H->Data[Child / 2]->Weight) {
        ElementofHeap TEMP = H->Data[Child];
        H->Data[Child] = H->Data[Child / 2];
        H->Data[Child / 2] = TEMP;
        Child /= 2;
    }
    return H;
}
ElementofHeap Pop(Heap H)
{
    if (!IsEmptyH(H)) {
        ElementofHeap RET = H->Data[1];
        H->Data[1] = H->Data[H->Size--];
        int Parent = 1,Child;
        for (Parent; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && H->Data[Child]->Weight > H->Data[Child + 1]->Weight)
                Child += 1;
            if (H->Data[Parent]->Weight > H->Data[Child]->Weight) {
                ElementofHeap TEMP = H->Data[Parent];
                H->Data[Parent] = H->Data[Child];
                H->Data[Child] = TEMP;
            }
        }
        return RET;
    }
    else {
        return NULL;
    }
}
BinTree BuildTree(Heap H)
{
    while (H->Size > 1) {
        PtrToTNode NewNode = new TNode;
        NewNode->Left = Pop(H);
        NewNode->Right = Pop(H);
        NewNode->Weight = NewNode->Left->Weight + NewNode->Right->Weight;
        H = Push(H, NewNode);
    }
    return Pop(H);
}
BinTree CreateTree()
{
    BinTree T = (BinTree)malloc(sizeof(struct TNode));
    T->C = '\0';
    T->Left = NULL;
    T->Right = NULL;
    T->Weight = -1;
    return T;
}
void PreorderTraversal(BinTree T)
{
    if (T) {
        cout << T->Weight << ' ';
        PreorderTraversal(T->Left);
        PreorderTraversal(T->Right);
    }
}

/* Stack */
typedef BinTree ElementofStack;
typedef struct SNode* PtrToSNode;
struct SNode {
    ElementofStack Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
    Stack S = new SNode;
    S->Next = NULL;
    return S;
}
Stack Push(Stack S, ElementofStack X)
{
    PtrToSNode NewNode = new SNode;
    NewNode->Data = X;
    NewNode->Next = S->Next;
    S->Next = NewNode;
    return S;
}
int IsEmptyS(Stack S)
{
    if (!S->Next) return 1;
    else return 0;
}
ElementofStack Pop(Stack S)
{
    ElementofStack ret = NULL;
    if (!IsEmptyS(S)) {
        ret = S->Next->Data;
        if (S->Next->Next) {
            PtrToSNode TEMP = S->Next;
            S->Next = S->Next->Next;
            free(TEMP);
            return ret;
        }
        else {
            PtrToSNode TEMP = S->Next;
            S->Next = NULL;
            free(TEMP);
            return ret;
        }
    }
    else {
        return NULL;
    }
}
int WVLCal(BinTree T)
{
    int wvl = 0;
    if (T) {
        BinTree P = T;
        P->Layer = 0;
        Stack S = CreateS();
        while (P || !IsEmptyS(S)) {
            while (P) {
                if (P->Left) P->Left->Layer = P->Layer+1;
                if (P->Right) P->Right->Layer = P->Layer+1;
                S = Push(S,P);
                P = P->Left;
            }
            P = Pop(S);
            P = P->Right;
        }
    }
    if (T) {
        BinTree P = T;
        Stack S = CreateS();
        while (P || !IsEmptyS(S)) {
            while (P) {
                S = Push(S, P);
                P = P->Left;
            }
            P = Pop(S);
            if (!P->Right) {
                wvl += P->Weight * P->Layer;
               
            }
            P = P->Right;
        }
    }
    return wvl;
}
int Judge(string* Input, int N)
{
    BinTree T = CreateTree();
    int flag = 1;
    for (int i = 0; i < N; i++) {
        BinTree TEMP = T;
        string tmp = Input[i].substr(2);
        char* c = new char[tmp.length() + 1];
        int j = 0;
        for (; j < tmp.length() + 1; j++) {
            c[j] = tmp[j];
        }
        for (int j = 0; j < tmp.length(); j++) {
            if (c[j] == '0') {
                if (TEMP->Left && j+1 != tmp.length()) {
                    TEMP = TEMP->Left;
                }
                else if (TEMP->Left && j + 1 == tmp.length()) {
                    flag = 0;
                    return flag;
                }
                else if (!TEMP->Left) {
                    TEMP->Left = new TNode;
                    TEMP = TEMP->Left;
                    TEMP->C = '\0';
                    TEMP->Left = NULL;
                    TEMP->Right = NULL;
                    TEMP->Weight = -1;
                }
            }
            else {
                if (TEMP->Right && j + 1 != tmp.length()) {
                    TEMP = TEMP->Right;
                }
                else if (TEMP->Right && j + 1 == tmp.length()) {
                    flag = 0;
                    return flag;
                }
                else if (!TEMP->Right) {
                    TEMP->Right = new TNode;
                    TEMP = TEMP->Right;
                    TEMP->C = '\0';
                    TEMP->Left = NULL;
                    TEMP->Right = NULL;
                    TEMP->Weight = -1;
                }
            }
        }
    }
    return flag;
}
int main()
{
    int N;
    cin >> N;
    PtrToTNode* T = Input(N);
    Heap H = CreateH();
    for (int i = 0; i < N; i++) {
        H = Push(H, T[i]);
    }
    
    BinTree BT = BuildTree(H);
    int WVL = WVLCal(BT);
    
    int M;
    cin >> M;
    cin.get();
    for (int i = 0; i < M; i++) {
        string* tmp = new string[N];
        for (int j = 0; j < N; j++) {
            getline(cin, tmp[j]);
        }
        int wvl = 0;
        for (int j = 0; j < N; j++) {
            wvl += (tmp[j].length()-2) * T[j]->Weight;
        }
        if (wvl != WVL) {
            printf("No\n");
        }
        else {
            if (Judge(tmp, N) == 1) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
            
        }
    }


    return 0;
}

