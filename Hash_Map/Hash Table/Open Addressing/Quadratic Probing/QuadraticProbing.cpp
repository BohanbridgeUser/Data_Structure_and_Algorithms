#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define MAXTABLESIZE 100000
typedef int ElementType;
typedef int Index;
typedef Index Position;
typedef enum{Legitimate,Empty, Deleted} EntryType;

typedef struct HashEntry Cell;
struct HashEntry {
    ElementType Data;
    EntryType Info;
};
typedef struct TblNode* HashTable;
struct TblNode {
    int TableSize;
    Cell* Cells;
};

int NextPrim(int N)
{
    /* 返回一个大于N，但小于MAXTABLESIZE的素数 */
    int i, p = (N % 2) ? N + 2 : N + 1; // 从大于N的下一个奇数开始

    while (p <= MAXTABLESIZE) {
        for (i = (int)sqrt(p); i>2; i--)
            if (p % i == 0)break;
        if (i == 2)break;
        else p += 2;
    }
    return p;
}
int LastPrim(int TableSize)
{
    int i, p = (TableSize % 2) ? TableSize - 2 : TableSize - 1; // 从小于N的下一个奇数开始
    while (p >= 3 ) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (p % i == 0)break;
        if (i == 2)break;
        else p -= 2;
    }
    return p;
}
int Hash(int N, int TableSize)
{
    int prim = LastPrim(TableSize);
    return N % prim;
}
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;
    H->Cells = (Cell*)malloc(TableSize*sizeof(Cell));
    for (int i = 0; i < TableSize; i++)
        H->Cells[i].Info = Empty;
    return H;
}
Position FindTable(HashTable H, ElementType Key)
{
    Position CurrentPos, NewPos;
    int CNum = 0;

    NewPos = CurrentPos = Hash(Key, H->TableSize);
    while (H->Cells[NewPos].Info == Legitimate && H->Cells[NewPos].Data != Key) {
        if (++CNum % 2) {
            NewPos = CurrentPos + (CNum + 1) / 2 * (CNum + 1) / 2;
            if (NewPos >= H->TableSize)
                NewPos = NewPos % H->TableSize;
        }
        else {
            NewPos = CurrentPos - CNum * CNum / 4;
            while(NewPos < 0)
                NewPos += H->TableSize;
        }
    }
    return NewPos;
}
int InsertTable(HashTable H, ElementType Key)
{
    Position Pos = FindTable(H, Key);

    if (H->Cells[Pos].Info != Legitimate) {
        H->Cells[Pos].Data = Key;
        H->Cells[Pos].Info = Legitimate;
        return 1;
    }
    else {
        return 0;
    }
}
int main()
{
    
    return 0;
}

