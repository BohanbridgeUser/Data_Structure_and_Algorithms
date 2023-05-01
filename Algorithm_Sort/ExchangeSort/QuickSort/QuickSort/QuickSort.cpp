#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define Cutoff 100

using namespace std;
typedef int ElementofQuickSort;
typedef int ElementofSimpleInsertionSort;

void Swap(ElementofQuickSort& a, ElementofQuickSort& b);
void QSort(ElementofQuickSort a[], int Left, int Right);

ElementofQuickSort Media2(ElementofQuickSort a[], int Left, int Right)
{
    int M = (Left + Right) / 2;
    if (a[Left] > a[Right]) Swap(a[Left], a[Right]);
    if (a[Left] > a[M]) Swap(a[Left], a[M]);
    if (a[M] > a[Right]) Swap(a[M], a[Right]);
    cout << a[Right] << ' ';
    cout << a[M] << ' ';
    cout << a[Left] << endl;
    Swap(a[M], a[Right-1]);
   
    return a[Right - 1];
}
void SimpleInsertionSort(ElementofSimpleInsertionSort a[], int Left,int Right)
{
    int i, j;
    ElementofSimpleInsertionSort tmp;

    for (i = Left + 1; i <= Right; i++) {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

void QSort(ElementofQuickSort a[], int Left,int Right)
{
    int Pivot,low = Left,high = Right - 1;
    

    if (Cutoff <= Right - Left) {
        Pivot = Media2(a, Left, Right);
        while (1) {
            while (a[++low] < Pivot) low++;
            while (a[--high] > Pivot) high--;
            if (low < high) Swap(a[low], a[high]);
            else break;
        }
        Swap(a[low], a[Right - 1]);
        QSort(a, Left, low - 1);
        QSort(a, low + 1, Right - 1);
    }
    else SimpleInsertionSort(a, Left, Right);
}
int main()
{
    int a[9] = { 9,8,7,6,5,5,3,2,1 };
    QSort(a, 0,8);
    for (int i = 0; i < 9; i++) cout << a[i] << ' ';

    return 0;
}

void Swap(ElementofQuickSort &a, ElementofQuickSort &b)
{
    ElementofQuickSort tmp = a;
    a = b;
    b = tmp;
}
void QSort1(ElementofQuickSort a[], int Left, int Right)
{
    int ref = Left;
    int tmp = a[ref];
    a[ref] = a[Right];
    a[Right] = tmp;

    int low = Left, high = Right - 1;
    while (low < high) {
        while (a[low] < a[Right] && low < Right - 1) low++;
        while (a[high] > a[Right] && high > Left) high--;
        if (low < high) {
            Swap(a[low], a[high]);
        }
    }
    if (a[low] > a[Right]) Swap(a[low], a[Right]);
    for (int i = 0; i < 9; i++) cout << a[i] << ' ';
    cout << endl;
    if (high > Left) QSort(a, Left, high);
    if (low < Right - 1) QSort(a, low + 1, Right);
}
