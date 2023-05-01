#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int ElementofHeapSort;

void Swap(ElementofHeapSort* a, ElementofHeapSort* b)
{
    ElementofHeapSort t = *a; 
    *a = *b; 
    *b = t;
}

void Percdown(ElementofHeapSort h[], int beg, int end)
{
    int Parent = beg, Child;
    ElementofHeapSort X = h[beg];
    for (Parent; Parent * 2 + 1 <= end; Parent = Child) {
        Child = Parent * 2 + 1;
        if (Child + 1 <= end && h[Child] < h[Child + 1])
            Child += 1;
        if (X >= h[Child]) break;
        else  h[Parent] = h[Child];
    }
    h[Parent] = X;
}
void HeapSort(ElementofHeapSort h[], int N)
{
    for (int i = N/2 - 1; i > -1; i--) {
        Percdown(h, i, N - 1); 
    }
    for (int i = N-1;i>0; i--) {
        Swap(&h[0], &h[i]);
        Percdown(h, 0, i-1);
    }
}

int main()
{
    int a[10] = { 2, 5, 6, 7,8,5,6,1,3,2 };
    HeapSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ';
    return 0;
}

