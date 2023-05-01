#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

struct Info {
    string Number;
    int Times;
};

typedef struct Info ElementofHash;

typedef struct HashNode* PtrToHashNode;
struct HashNode {
    ElementofHash Data;
    PtrToHashNode Next;
};
typedef PtrToHashNode* List;
struct HashT {
    int TableSize;
    List Heads;
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
int Hash(ElementofHash X)
{
    string t = X.Number.substr(7, 11);
    stringstream stream;
    stream << t;
    int ret;
    stream >> ret;
    //ret = ret % 100;
    return ret;
}
PtrToHashNode FindH(HashTable H, ElementofHash X)
{
    int Pos = Hash(X);
    PtrToHashNode  p = H->Heads[Pos]->Next;
    while (p && p->Data.Number != X.Number) {
        p = p->Next;
    }
    return p;
}
void InsertH(HashTable H, ElementofHash X)
{
    PtrToHashNode p = FindH(H, X);
    if (!p) {
        int Pos = Hash(X);
        PtrToHashNode NewNode = new struct HashNode;
        NewNode->Data = X;
        NewNode->Next = H->Heads[Pos]->Next;
        H->Heads[Pos]->Next = NewNode;
        NewNode->Data.Times++;
    }
    else {
        p->Data.Times++;
    }
}
int Compare(ElementofHash a, ElementofHash b)
{
    if (a.Times == b.Times) {
        return a.Number < b.Number ? 1:-1;
    }
    return a.Times > b.Times ? 1 : -1;
}
void FindMax(HashTable H)
{
    ElementofHash max = { "0",0};
    int cnt = 0;
    for (int i = 0; i < 10000; i++) {
        PtrToHashNode p = H->Heads[i]->Next;
        while (p) {
            if (Compare(p->Data, max) == 1) max = p->Data;
            p = p->Next;
        }
    }
    for (int i = 0; i < 10000; i++) {
        PtrToHashNode p = H->Heads[i]->Next;
        while (p) {
            if (p->Data.Times == max.Times) cnt++;
            p = p->Next;
        }
    }
    if (cnt == 1) cout << max.Number << ' ' << max.Times;
    else cout << max.Number << ' ' << max.Times << ' ' << cnt;
}
int main()
{
    int N;
    cin >> N;
    HashTable H = CreateH(10000);
    for (int i = 0; i < N; i++) {
        string t1, t2;
        cin >> t1;
        cin >> t2;
        ElementofHash x1 = { t1,0 }, x2 = { t2,0 };
        InsertH(H, x1);
        InsertH(H, x2);
    }
    FindMax(H);

    return 0;
}
