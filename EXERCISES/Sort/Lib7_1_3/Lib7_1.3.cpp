#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void Swap(int& a, int& b)
{
    int t = a; a = b; b = t;
}
void InsertionSort(int a[], int Beg, int End)
{
    int i, j;
    for (i = Beg; i < End; i++) {
        for (j = i + 1; j > Beg; j--) {
            if (a[j] > a[j - 1]) Swap(a[j], a[j - 1]);
            else break;
        }  
    }
}
void SelectionSort(int a[], int Beg, int End,int M)
{
    int Max, i, j;
    for (i = Beg; i <= Beg + M - 1; i++) {
        Max = i;
        for (j = i + 1; j <= End; j++)
            if (a[j] > a[Max]) Max = j;
        Swap(a[Max], a[i]);
    }
}


int main()
{
    int N, M;
    cin >> N;
    cin >> M;
    if (N < M) M = N;
    int* a = new int[N];
    for (int i = 0; i < N; i++) cin >> a[i];
    //InsertionSort(a, 0, N - 1);
    SelectionSort(a, 0, N - 1, M);
    cout << a[0];
    for (int i = 1; i < M; i++) cout << ' ' << a[i] ;
    return 0;
}

