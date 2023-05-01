#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

typedef struct Information ElementofHash;
struct Information {
    string ID;
    string PassWord;
};

typedef struct HashNode* PtrToHashNode;
struct HashNode {
    ElementofHash Data;
    PtrToHashNode Next;
};
struct HashList {
    int TableSize;
    PtrToHashNode* Heads;
};
typedef HashList* HashTable;

HashTable CreateH(int TableSize)
{
    HashTable H = new struct HashList;
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
    int len = X.ID.length();
    string t;
    if (len < 5) t = X.ID.substr(0);
    else t = X.ID.substr(len - 5);
    stringstream stream;
    stream << t;
    int ret;
    stream >> ret;
    ret /= 2;
    return ret;
}
PtrToHashNode FindX(HashTable H, ElementofHash X)
{
    int Pos = Hash(X);
    PtrToHashNode p = H->Heads[Pos];
    while (p && p->Data.ID != X.ID) {
        p = p->Next;
    }
    return p;
}
void InsertHN(HashTable H, ElementofHash X)
{
    PtrToHashNode p = FindX(H, X);
    if (!p) {
        int Pos = Hash(X);
        PtrToHashNode NewNode = new struct HashNode;
        NewNode->Data = X;
        NewNode->Next = H->Heads[Pos]->Next;
        H->Heads[Pos]->Next = NewNode;
        cout << "New: OK" << endl;
    }
    else {
        cout << "ERROR: Exist" << endl;
    }
}
void InsertHL(HashTable H, ElementofHash X)
{
    PtrToHashNode p = FindX(H, X);
    if (!p) {
        cout << "ERROR: Not Exist" << endl;
    }
    else {
        if(p->Data.PassWord == X.PassWord) cout << "Login: OK" << endl;
        else cout << "ERROR: Wrong PW" << endl;
    }
}
int main()
{
    int N;
    cin >> N;
    HashTable H = CreateH(50000);
    for (int i = 0; i < N; i++) {
        string t,id,pw;
        cin >> t;
        cin >> id;
        cin >> pw;
        ElementofHash x = { id,pw };
        //cout << Hash(x) << endl;
        if (t == "N") {
            InsertHN(H, x);
        }
        else if (t == "L") {
            InsertHL(H, x);
        }
    }
    return 0;
}
