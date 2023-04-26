#include <stdio.h>
#include <stdlib.h>

typedef int ElementofList;
typedef struct Node* PtrToNode;
struct Node{
    ElementofList Data;
    PtrToNode Next;
};

