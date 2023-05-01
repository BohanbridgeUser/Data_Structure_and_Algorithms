#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

typedef enum{Legitimate, Empty, Deleted} EntryType;

typedef int ElementofHash;

typedef struct HashEntry* Cell;
struct HashEntry {
    ElementofHash Data;
    EntryType Info;
};
struct HashNode {
    int TableSize;
    Cell* Cells;
};
typedef struct HashNode* HashTable;

int NextPrimeNumber(int TableSize)
{
    int i;
    int flag;
    if (TableSize == 1)
        TableSize++;
    while (1)
    {
        flag = 1;
        for (i = sqrt(TableSize); i > 1; i--)
        {
            if (!(TableSize % i))
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
        else
            TableSize++;
    }
    return TableSize;
}
HashTable CreateHash(int TableSize)
{
    HashTable H = (HashTable)malloc(sizeof(struct HashNode));
    H->TableSize = NextPrimeNumber(TableSize);
    H->Cells = (Cell*)malloc(H->TableSize * sizeof(struct HashEntry));
    for (int i = 0; i < H->TableSize; i++) {
        H->Cells[i] = (Cell)malloc(sizeof(struct HashEntry));
        H->Cells[i]->Info = Empty;
    }
        
    return H;
}
int NextPrim(int TableSize)
{
    int i;
    int flag;
    if (TableSize == 1)
        TableSize++;
    while (1)
    {
        flag = 1;
        for (i = sqrt(TableSize); i > 1; i--)
        {
            if (!(TableSize % i))
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
        else
            TableSize++;
    }
    return TableSize;
}

//int NextPrim(int MSize)
//{
//    if (MSize == 1) return 2;
//    int i, P = MSize % 2 ? MSize + 2 : MSize + 1;
//    while ( P <= 65535) {
//        for (i = sqrt(P); i > 2; i--) {
//            if (P % i == 0) break;
//        }
//        if (i == 2) return P;
//        else P += 2;
//    }
//}
int IsPrim(int MSize)
{
    int i;
    if (MSize == 1) return 0;
    int max = MSize > 15 ? sqrt(MSize) : MSize - 1;
    for (i = max; i > 1; i--) {
        if (MSize % i == 0) break;
    }
    if (i == 1) return 1;
    else return 0;
}
int HKey(int Key, int MSize)
{
    return Key % MSize;
}
int FindX(HashTable H,ElementofHash X)
{
    int NewPos, CurrentPos, CNum = 0,cnt = 0;
    NewPos = CurrentPos = HKey(X, H->TableSize);
    int* path = new int[H->TableSize];
    for (int i = 0; i < H->TableSize; i++) path[i] = -1;
    while (H->Cells[NewPos]->Info != Empty && H->Cells[NewPos]->Data != X) {
        CNum++;
        NewPos = CurrentPos + CNum * CNum;
        if (NewPos >= H->TableSize) NewPos = NewPos % H->TableSize;

        if (path[NewPos] == -1) path[NewPos] = 1;
        else {
            NewPos = -2;
            break;
        }
    }
    free(path);
    return NewPos;
}
void InsertAndOutput(HashTable H, ElementofHash key)
{
    int Pos = FindX(H, key);
    if (Pos == -2)
    {
        printf("-");
    }

    else if (H->Cells[Pos]->Info != Legitimate)
    {
        H->Cells[Pos]->Data = key;
        H->Cells[Pos]->Info = Legitimate;
        printf("%d", Pos);
    }
}

int main()
{
    int MSize, N;
    cin >> MSize;
    cin >> N;
    HashTable H = CreateHash(MSize);
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        if (i == N - 1)
            InsertAndOutput(H, tmp);
        else {
            InsertAndOutput(H, tmp);
            cout << " ";
        }
    }
    return 0;
}