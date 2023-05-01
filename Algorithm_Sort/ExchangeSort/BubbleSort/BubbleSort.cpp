#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef int ElementofBubbleSort;

void Swap(ElementofBubbleSort& a, ElementofBubbleSort& b)
{
    ElementofBubbleSort t = a;
    a = b;
    b = t;
}

void BubbleSort(ElementofBubbleSort a[], int N)
{
    for (int i = 0; i < N; i++) {
        int flag = false;
        for (int j = 0; j < N - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                Swap(a[j], a[j + 1]);
                flag = true;
            }
        }
        if (flag == false) break;
    }
}

int main()
{
    using namespace std;
    int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
    BubbleSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ' ;
    return 0;
}
