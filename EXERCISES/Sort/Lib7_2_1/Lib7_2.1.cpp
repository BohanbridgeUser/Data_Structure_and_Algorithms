#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void Swap(int& a, int& b)
{
    int t = a; a = b; b = t;
}

void InsertSort(int a[], int Beg, int End)
{
    for (int i = Beg; i < End; i++) {
        for (int j = i + 1; j <= End; j++)
            if (a[j] < a[j - 1]) Swap(a[j], a[j - 1]);
    }
}
int Media3(int a[], int Left, int Right,int Midle)
{
    if (a[Left] > a[Right]) Swap(a[Left], a[Right]);
    if (a[Left] > a[Midle]) Swap(a[Left], a[Midle]);
    if (a[Midle] > a[Right]) Swap(a[Midle], a[Right]);
    Swap(a[Midle], a[Right - 1]);
    return a[Right - 1];
}
void QSort(int a[], int Left, int Right)
{
    int Cutoff = 4;
    if (Cutoff <= Right - Left + 1) {
        int Midle = (Left + Right) / 2;
        int Pivot = Media3(a, Left, Right, Midle);
        int low = Left, high = Right - 1;
        while (low < high) {
            while (a[++low] < Pivot);
            while (a[--high] > Pivot);
            if (low < high) Swap(a[low], a[high]);
        }
        Swap(a[low], a[Right - 1]);
        QSort(a, Left, low - 1);
        QSort(a, low + 1, Right);
    }
    else InsertSort(a, Left, Right);
}
int MaxReturn(int sales[], int coupon[], int N, int M)
{
    int max = 0;
    int ps =0, pc = 0;
    while (sales[ps] < 0 && coupon[pc] < 0) {
        max += sales[ps++] * coupon[pc++];
    }
    ps = N-1, pc =M-1;
    while (sales[ps] > 0 && coupon[pc] > 0) {
        max += sales[ps--] * coupon[pc--];
    }
    
    return max;
}

int main()
{
    int N, M;
    cin >> N;
    int* sales = new int[N];
    for (int i = 0; i < N; i++) cin >> sales[i];
    cin >> M;
    int* coupon = new int[M];
    for (int i = 0; i < N; i++) cin >> coupon[i];

    QSort(sales, 0, N - 1);
    QSort(coupon, 0, M - 1);

    cout << MaxReturn(sales, coupon, N, M);
    return 0;
}
