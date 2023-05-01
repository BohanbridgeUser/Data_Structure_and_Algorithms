#include <stdio.h>
#include <stdlib.h>
#include <iostream>



typedef int ElementofSimpleInsertionSort;

void SimpleInsertionSort(ElementofSimpleInsertionSort a[], int N)
{
    int i, j;
    ElementofSimpleInsertionSort tmp;
    
    for (i = 1; i < N; i++) {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}


int main()
{
    using namespace std;
    int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
    SimpleInsertionSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ';
    return 0;
}

