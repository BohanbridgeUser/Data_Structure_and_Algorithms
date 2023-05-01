#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef int ElementofSort;

void Swap(ElementofSort* a, ElementofSort* b)
{
    ElementofSort tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void SimpleSelectionSort(ElementofSort* A, int N)
{
    for (int i = 0; i < N - 1; i++) {
        int min = i;
        for (int j = i + 1; j < N; j++) 
            if (A[j] <  A[min]) min = j;
        Swap(&A[i], &A[min]);
    }
}

int main()
{
    int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
    SimpleSelectionSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ';
    return 0;
}


