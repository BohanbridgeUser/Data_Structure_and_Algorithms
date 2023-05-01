#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

typedef int ElementofType;

typedef struct HashEntry* Position;
struct HashEntry {
    ElementofType Data;
    Position Next;
};
typedef Position List;
typedef struct TblNode* HashTable;
struct TblNode {
    int TableSize;
    List Heads;
};

int LastPrim(int TableSize)
{
    int i, p = (TableSize % 2) ? TableSize - 2 : TableSize - 1;
    while (p >= 3) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (p % i == 0) break;
        if (p == 2) break;
        else p -= 2;
    }
    return p;
}
int Hash(int N, int TableSize)
{
    int Prim = LastPrim(TableSize);
    return N % Prim;
}
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;
    H->Heads = (List)malloc(H->TableSize * sizeof(struct HashEntry));
    for (int i = 0; i < H->TableSize; i++)
        H->Heads[i].Next = NULL;
    return H;
}
Position FindTable(HashTable H, ElementofType Key)
{
    int Pos = Hash(Key, H->TableSize);
    
    Position P = H->Heads[Pos].Next;
    while (P && P->Data == Key) P = P->Next;
    return P;
}
int InsertTable(HashTable H, ElementofType Key)
{
    Position P = FindTable(H, Key),NewNode;
    if (!P) {
        NewNode = (Position)malloc(sizeof(struct HashEntry));
        NewNode->Data = Key;
        int Pos = Hash(Key, H->TableSize);
        NewNode->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewNode;
        return 1;
    }
    else {
        return 0;
    }
}
void DestroyTable(HashTable H)
{
    int i;
    Position P, TMP;

    for (i = 0; i < H->TableSize; i++) {
        P = H->Heads[i].Next;
        while (P) {
            TMP = P->Next;
            free(P);
            P = TMP;
        }
    }
    free(H->Heads);
    free(H);
}
int main()
{
    return 0;
}

