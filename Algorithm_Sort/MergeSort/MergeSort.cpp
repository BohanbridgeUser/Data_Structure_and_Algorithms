#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int ElementofMergeSort;

void MergeSort(ElementofMergeSort a[],ElementofMergeSort atmp[], int Left, int Right)
{
    int Midle = (Left + Right) / 2;
    int n = Left;

    if (Left >= Right) return;
    else {
        MergeSort(a, atmp, Left, Midle);
        MergeSort(a, atmp, Midle + 1, Right);
        int i = Left, j = Midle + 1;
        while (i <= Midle && j <= Right) {
            if (a[i] <= a[j]) atmp[n++] = a[i++];
            else atmp[n++] = a[j++];
        }
        while (i <= Midle) atmp[n++] = a[i++];
        while (j <= Right) atmp[n++] = a[j++];
        cout << "atmp:";
        for (int i = 0; i < 10; i++) cout << atmp[i] << ' ';
        cout << endl;
        cout << "a:";
        for (int i = 0; i < 10; i++) cout << a[i] << ' ';
        cout << endl;
        for (int k = Right; k>= Left; k--)
            a[k] = atmp[k];
    }
}

int main() 
{
    int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
    int atmp[10] = { 0 };
    MergeSort(a, atmp, 0, 9);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ';
    return 0;
}

