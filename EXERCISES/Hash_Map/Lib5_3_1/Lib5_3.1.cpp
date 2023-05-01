#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string.h>

using namespace std;

typedef struct Information ElementofHash;
struct Information {
    char* ID;
    int Len;
};

typedef struct HashNode* PtrToHashNode;
struct HashNode {
    ElementofHash Data;
    PtrToHashNode Next;
};
struct HashT {
    int TableSize;
    PtrToHashNode* Heads;
};
typedef struct HashT* HashTable;

HashTable CreateH(int TableSize)
{
    HashTable H = new struct HashT;
    H->TableSize = TableSize;
    H->Heads = new PtrToHashNode[H->TableSize];
    for (int i = 0; i < H->TableSize; i++) {
        H->Heads[i] = new struct HashNode;
        H->Heads[i]->Next = NULL;
    }
    return H;
}
int Hash(ElementofHash X, int P)
{
    long long t = 0;
    for (int i = 0; i < 17; i++)
        t = 10 * t + (X.ID[i] - '0');
    t = t % P;
    return t;
}
PtrToHashNode FindX(HashTable H, ElementofHash X, int P)
{
    int Pos = Hash(X,P);
    PtrToHashNode p = H->Heads[Pos]->Next; 
    while (p && memcmp(p->Data.ID,X.ID,19) != 0 ) {
        p = p->Next;
    }
    return p;
}
void InsertH(HashTable H, ElementofHash X, int P)
{
    PtrToHashNode p = FindX(H,X,P);
    if (!p) {
        int Pos = Hash(X, P);
        PtrToHashNode NewNode = new struct HashNode;
        NewNode->Data = X;
        NewNode->Next = H->Heads[Pos]->Next;
        H->Heads[Pos]->Next = NewNode;
    }
    else {
        p->Data.Len += X.Len;
    }
}
void Length(HashTable H, ElementofHash X, int P)
{
    PtrToHashNode p = FindX(H, X, P);
    if (!p) printf("No Info\n");
    else {
        printf("%d\n",p->Data.Len);
    }
}
int main()
{
    int N, K;
    scanf("%d %d\n", &N, &K);
    int P = 100007;
    HashTable H = CreateH(P);
    for (int i = 0; i < N; i++) {
        ElementofHash x;
        x.ID = (char*)malloc(19 * sizeof(char));
        scanf("%s %d", x.ID, &x.Len);
        if (x.Len < K) x.Len = K;
        InsertH(H, x, P);
    }
    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        ElementofHash x;
        x.ID = (char*)malloc(19 * sizeof(char));
        scanf("%s", x.ID);
        Length(H, x, P);
    }
    return 0;
}