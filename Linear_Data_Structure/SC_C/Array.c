/* this code is a simple array structure and its algorithm */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
bool IsFull(PtrToArray A)
{
    return (A->num < A->size)? false:true;
}
bool IsEmpty(PtrToArray A)
{
    return (A->num > 0)? false:true;
}
bool AddArray(PtrToArray A, ElementofArray X)
{
    if(!IsFull(A)){
        A->Data[A->num++] = X;
        return true;
    }else{
        printf("FULL ARRAY\n");
        return false;
    }
}
bool DelArray(PtrToArray A, ElementofArray* X)
{
    if(!IsEmpty(A)){
        *X = A->Data[--A->num];
        return true;
    }else{
        printf("EMPTY ARRAY\n");
        return false;
    }
}

int main()
{
    return 0;
}