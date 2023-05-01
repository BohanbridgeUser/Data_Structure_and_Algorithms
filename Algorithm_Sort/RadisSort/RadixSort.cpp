#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int ElementofBucket;
#define Error 65535
#define Radix 10;
/* 基数分解适用于已经知道排序范围的情况 */

typedef struct BNode* PtrToBNode;
struct BNode {
    ElementofBucket Data;
    PtrToBNode Next;
};
struct Buck {
    PtrToBNode Head;
    PtrToBNode Rear;
};
typedef struct Buck* Bucket;
Bucket CreateB()
{
    Bucket B = new Buck;
    B->Head = new BNode;
    B->Head->Next = NULL;
    B->Rear = B->Head;
    return B;
}
int IsEmptyB(Bucket B)
{
    return B->Head->Next ? 0 : 1;
}
Bucket AddB(Bucket B, ElementofBucket X)
{
    PtrToBNode NewNode = new BNode;
    NewNode->Data = X;
    NewNode->Next = B->Head->Next;
    B->Head->Next = NewNode;
    return B;
}
Bucket InB(Bucket B, ElementofBucket X)
{
    PtrToBNode NewNode = new BNode;
    NewNode->Data = X;
    NewNode->Next = B->Rear->Next;
    B->Rear->Next = NewNode;
    B->Rear = B->Rear->Next;
    return B;
}
ElementofBucket DelB(Bucket B)
{
    if (!IsEmptyB(B)) {
        ElementofBucket ret = B->Head->Next->Data;
        PtrToBNode tmp = B->Head->Next;
        if (B->Head->Next->Next) {
            B->Head->Next = B->Head->Next->Next;
            delete tmp;
            return ret;
        }
        else {
            B->Head->Next = NULL;
            B->Rear = B->Head;
            delete tmp;
            return ret;
        }
    }
    else {
        return Error;
    }
}
int Digit(ElementofBucket X,int loc)
{
    int c = 1,ret = -1;
    for (int i = 1; i <= loc; i++) {
        ret = X % Radix;
        X /= Radix;
    }
    return ret;
}
void RadixSort(ElementofBucket a[], int N)
{
    int radix = Radix;
    Bucket* B = new Buck*[radix];
    for (int j = 0; j < radix; j++) B[j] = CreateB();

    /* 已知排序范围使用使用基数分解较为方便，假定0~999排序 */
    /* 初始化 */
    Bucket List = new Buck;
    List = CreateB();
    for (int i = 0; i < N; i++) List = AddB(List, a[i]);


    /* 排序过程 */
    for (int i = 1; i <= 3; i++) {
        Bucket p = List;
        while (!IsEmptyB(p)) {
            ElementofBucket tmp = DelB(List);
            int d = Digit(tmp, i);
            B[d] = InB(B[d], tmp);
        }

        for (int j = radix - 1; j >= 0; j--) {
            if (!IsEmptyB(B[j])) {
                B[j]->Rear->Next = List->Head->Next;
                List->Head->Next = B[j]->Head->Next;
                B[j]->Head->Next = NULL;
                B[j]->Rear = B[j]->Head;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        a[i] = DelB(List);
    }
    for (int j = 0; j < radix; j++) free(B[j]);
    free(List);
}
int main()
{
    int a[10] = { 64,8,512,216,27,729,0,1,343,125 };
    RadixSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ';
    return 0;
}
