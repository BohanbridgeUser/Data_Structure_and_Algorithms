#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//void Merge(int a[], int atmp[], int Left, int Right ,int m)
//{
//    int i = Left, j = m+1,k = Left;
//    while (i <= m && j <= Right) {
//        if (a[i] < a[j]) atmp[k++] = a[i++];
//        else atmp[k++] = a[j++];
//    }
//    while (i <= m) atmp[k++] = a[i++];
//    while (j <= Right) atmp[k++] = a[j++];
//    for (int l = Left; l <= Right; l++) a[l] = atmp[l];
//}
//void MergeSort(int a[],int atmp[], int Left, int Right)
//{
//    if (Left < Right) {
//        int m = (Left + Right) / 2;
//        MergeSort(a, atmp, Left, m);
//        MergeSort(a, atmp, m + 1, Right);
//        Merge(a, atmp, Left, Right,m);
//    }
//    else {
//        return ;
//    }
//}
int SeqCheck(int a[], int Left, int Right)
{
    int ret = 1;
    for (int i = Left; i < Right; i++) {
        if (a[i] > a[i + 1]) {
            ret = 0;
            break;
        }
    }
    return ret;
}
void Merge(int a[], int atmp[], int Left, int Right, int c)
{
    int i = Left, j = c+1, k = Left;
    while (i <= c && j <= Right) {
        if (a[i] < a[j]) atmp[k++] = a[i++];
        else atmp[k++] = a[j++];
    }
    while (i <= c) atmp[k++] = a[i++];
    while (j <= Right) atmp[k++] = a[j++];

    for (k = Right; k >= Left; k--) a[k] = atmp[k];
}
//int MergeSortCheck(int a[], int atmp[], int Left, int Right)
//{
//    if (Left < Right) {
//        int b, c, d , e;
//        c = (Left + Right) / 2;
//        b = MergeSortCheck(a,atmp, Left, c - 1);
//        d = MergeSortCheck(a,atmp, c, Right);
//        if (b == 2 && d == 2) return 2;
//        else if (b == 2 && d != 2) return 0;
//        else if (b != 2 && d == 2) return 0;
//        else {
//            e = SeqCheck(a, Left, Right);
//            if (b == 1 && d == 1 && e == 1) return 1;
//            else if (b == 1 && d == 1 && e == 0) {
//                Merge(a, atmp, Left, Right, c);
//                return 2;
//            }
//            else {
//                return 0;
//            }
//        }
//    }
//    else {
//        return 1;
//    }
//}
int JudgeMerge(int Mid[],int atmp[], int N)
{
    int crt = 0;
    for (int i = 2; i <= N; i *= 2) {
        int j = 0,crt2 = 0;
        for (j = 0; j + i - 1 < N || j+ i/2 - 1 < N; j += i) {
            int k;
            if (j + i - 1 < N) {
                k = j + i - 1;
                if (SeqCheck(Mid, j, k) != 1) {
                    if (crt == 1) {
                        Merge(Mid, atmp, j, k, (j + k) / 2);
                        crt2 = 1;
                    }
                    else {
                        crt = 0;
                        return crt;
                    }
                }
            }
            else if (j + i / 2 - 1 < N) {
                k = j + i / 2 - 1;
                if (SeqCheck(Mid, j, N-1) != 1) {
                    if (crt == 1) {
                        Merge(Mid, atmp, j, N - 1, k);
                        crt2 = 1;
                    }
                    else {
                        crt = 0;
                        return crt;
                    }
                }
            }
        }
        crt = 1;
        if (crt2 == 1) return 1;
    }
}
void Swap(int& a, int& b)
{
    int t = a; a = b; b = t;
}
int main()
{   
    int N;
    cin >> N;
    int* Ori = new int[N];
    int* Mid = new int[N];
    for (int j = 0; j < N; j++) {
        cin >> Ori[j];
    }
    for (int j = 0; j < N; j++) {
        cin >> Mid[j];
    }
    int* atmp = new int[N];
    if (JudgeMerge(Mid,atmp, N) == 1) {
        cout << "Merge Sort\n";
        cout << Mid[0];
        for (int i = 1; i < N; i++)cout <<" " << Mid[i];
    }
    else {
        cout << "Insertion Sort\n";
        for (int i = 0; i < N - 1; i++) {
            if (Mid[i+1] < Mid[i]) {
                for (int j = i+1; j > 0; j--) {
                    if (Mid[j] < Mid[j - 1]) Swap(Mid[j], Mid[j - 1]);
                    else break;
                }
                break;
            }
        }
        cout << Mid[0];
        for (int i = 1; i < N; i++)cout <<" " << Mid[i];
    }
    return 0;
}