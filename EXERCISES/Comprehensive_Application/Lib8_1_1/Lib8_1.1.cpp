#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

typedef struct HashNode ElementofHash;
typedef struct HashEntry* Position;
struct HashNode {
    int ID;
    int Couple;
    int Show;
};
struct HashEntry {
    ElementofHash Data;
    Position Next;
};
typedef Position List;
typedef struct TblNode* HashTable;
struct TblNode {
    int TableSize;
    List Heads;
};

int NextPrim(int TableSize)
{
    int i, p = (TableSize % 2) ? TableSize + 2 : TableSize + 1;
    while ( p <= 100000) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (p % i == 0) {
                break;
            }
        if (i == 2) break;
        else p += 2;
    }
    return p;
}
int Hash(int N, int TableSize)
{
    return N / 3;
}
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrim(TableSize);
    //printf("%d\n", H->TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct HashEntry));
    for (int i = 0; i < H->TableSize; i++)
        H->Heads[i].Next = NULL;
    return H;
}
Position FindTable(HashTable H, int Key)
{
    int Pos = Hash(Key, H->TableSize);
    Position P = H->Heads[Pos].Next;
    while (P && P->Data.ID != Key) P = P->Next;
    return P;
}
int InsertTable(HashTable H, ElementofHash Key)
{
    Position P = FindTable(H, Key.ID), NewNode;
    if (!P) {
        NewNode = (Position)malloc(sizeof(struct HashEntry));
        NewNode->Data = Key;
        int Pos = Hash(Key.ID, H->TableSize);
        NewNode->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewNode;
        return 1;
    }
    else {
        return 0;
    }
}
int Compare(const void* a, const void* b) 
{
    return *(int*)a - *(int*)b;
}
int main()
{
    int N;
    scanf("%d", &N);
    HashTable H = CreateTable(50000);
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d %d\n", &a, &b);
        ElementofHash x = { a,b,0 };
        InsertTable(H, x);
        x = { b,a,0 };
        InsertTable(H, x);
    }
    int M;
    scanf("%d", &M);
    int* customer = new int[M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &customer[i]);
        Position p = FindTable(H, customer[i]);
        if (p) {
            Position q = FindTable(H, p->Data.Couple);
            q->Data.Show = 1;
        }
    }
    qsort(customer, M, sizeof(int), Compare);

    int cnt = 0;
    int* issingle = new int[M];
    for (int i = 0; i < M; i++) issingle[i] = -1;
    int j = 0;
    for (int i = 0; i < M; i++) {
        Position p = FindTable(H, customer[i]);
        if (p && p->Data.Show != 1) {
            issingle[cnt++] = customer[i];
        }
        else if (!p) {
            issingle[cnt++] = customer[i];
        }
    }
    printf("%d\n", cnt);
    if (cnt != 0) {
        printf("%05d", issingle[0]);
        j = 1;
        while (issingle[j] != -1 && j < M) {
            printf(" %05d", issingle[j++]);
        }
    }
       
    return 0;
}
