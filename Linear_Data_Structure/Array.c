/* this code is a simple array structure and its algorithm */
#include <stdlib>
#include <stdio>

#define MAXITEM 100
#define Null 0

typedef int ElementofArray;
struct Array{
    ElementofArray Data[MAXITEM];
    int num;
    int size;
};
typedef struct Array* PtrToArray;

PtrToArray CreateArray()
{
    PtrToArray NewArray = (PtrToArray)malloc(sizeof(struct Array));
    NewArray->Data[0] = Null;
    int num = 0;
    int size = MAXITEM;
    return NewArray;
}
bool IsFUll(PtrToArray A)
{
    return (num < size)? false:true;
}
bool IsEmpty(PtrToArray A)
{
    return (num > 0)? false:true;
}
bool AddArray(PtrToArray A, ElementofArray X)
{
    if(!IsFull(A)){
        A->Data[num++] = X;
        return true;
    }else{
        printf("FULL ARRAY\n");
        return false;
    }
}
bool DelArray(PtrToArray A, ElementofArray* X)
{
    if(!IsEmpty(A)){
        *X = A->Data[--num];
        return true;
    }else{
        printf("EMPTY ARRAY\n");
        return false;
    }
}