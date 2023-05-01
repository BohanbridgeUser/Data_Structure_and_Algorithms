#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

typedef struct Inf* PtrToInf;
struct Inf {
    int ID;
    int DG;
    int CG;
    int Sum;
};
//void InsertSort(PtrToInf a, int Beg, int End)
//{
//    for (int i = Beg; i < End; i++) {
//        for (int j = i + 1; j > 0; j--)
//            if (Compare(&a[j],&a[j - 1]) == 1) Swap(a[j], a[j - 1]);
//    }
//}
//void SelectionSort(PtrToInf a, int Beg, int End)
//{
//    for (int i = Beg; i <= End - 1; i++) {
//        int max = i;
//        for (int j = i + 1; j <= End; j++) {
//            if (a[j].Sum > a[max].Sum) max = j;
//        }
//        Swap(a[max], a[i]);
//    }
//}
//int Media3(PtrToInf a, int Left, int Right, int Midle)
//{
//    if (Compare(a[Left], a[Midle]) == -1) Swap(a[Left], a[Midle]);
//    if (Compare(a[Left], a[Right]) == -1) Swap(a[Left], a[Right]);
//    if (Compare(a[Midle], a[Right]) == -1) Swap(a[Midle], a[Right]);
//    Swap(a[Midle], a[Right - 1]);
//    return a[Right - 1].Sum;
//}
//void QSort(PtrToInf a, int Left, int Right)
//{
//    int Cutoff = 4;
//    if (Cutoff <= Right - Left + 1) {
//        int Midle = (Left + Right) / 2;
//        int Pivot = Media3(a, Left, Right, Midle);
//        int low = Left, high = Right - 1;
//
//        while (low < high) {
//            while (Compare(a[++low], a[Right - 1]) == 1);
//            while (Compare(a[--high], a[Right - 1]) == -1);
//            if (low < high) Swap(a[low], a[high]);
//        }
//        Swap(a[low], a[Right - 1]);
//        QSort(a, Left, low - 1);
//        QSort(a, low + 1, Right);
//    }
//    else InsertSort(a, Left, Right);
//}
//void Swap(struct Inf& a, struct Inf& b)
//{
//    struct Inf t = a; a = b; b = t;
//}
int Compare(const void* a, const void* b)
{
    PtrToInf p1 = (PtrToInf)a, p2 = (PtrToInf)b;
    if (p1->Sum == p2->Sum) {
        if (p1->DG == p2->DG) {
            return p1->ID < p2->ID? -1 : 1;
        }
        return p1->DG > p2->DG ? -1 : 1;
    }
    return p1->Sum > p2->Sum ? -1 : 1;
}

int main()
{
    int N, L, H;
    cin >> N;
    cin >> L;
    cin >> H;
    PtrToInf Input1 = new Inf[N];
    PtrToInf Input2 = new Inf[N];
    PtrToInf Input3 = new Inf[N];
    PtrToInf Input4 = new Inf[N];
    int i = 0, j = 0, k = 0, m = 0, total = 0;
    for (int l = 0; l < N; l++) {
        int a ;
        cin >> a;
        int b;
        cin >> b;
        int c;
        cin >> c;
        if (b >= H && c >= H) {
            Input1[i].ID= a;
            Input1[i].DG = b;
            Input1[i].CG = c;
            Input1[i].Sum = Input1[i].DG + Input1[i].CG;
            i++;
            total++;
        }
        else if (b >= H && c < H && c >= L) {
            Input2[j].ID = a;
            Input2[j].DG = b;
            Input2[j].CG = c;
            Input2[j].Sum = Input2[j].DG + Input2[j].CG;
            j++;
            total++;
        }
        else if (b < H && b >=c && b >= L && c < H && c>= L) {
            Input3[k].ID = a;
            Input3[k].DG = b;
            Input3[k].CG = c;
            Input3[k].Sum = Input3[k].DG + Input3[k].CG;
            k++;
            total++;
        }
        else if(b>=L && c>=L) {
            Input4[m].ID = a;
            Input4[m].DG = b;
            Input4[m].CG = c;
            Input4[m].Sum = Input4[m].DG + Input4[m].CG;
            m++;
            total++;
        }
    }
    cout << total << endl;

    if(i != 0 )qsort(Input1, i, sizeof(struct Inf), Compare);
    if(j != 0)qsort(Input2, j, sizeof(struct Inf), Compare);
    if(k != 0)qsort(Input3, k, sizeof(struct Inf), Compare);
    if(m != 0)qsort(Input4, m, sizeof(struct Inf), Compare);
    for (int x = 0; x < i; x++) {
        cout << Input1[x].ID << ' ';
        cout << Input1[x].DG << ' ';
        cout << Input1[x].CG << endl;
    }
    for (int x = 0; x < j; x++) {
        cout << Input2[x].ID << ' ';
        cout << Input2[x].DG << ' ';
        cout << Input2[x].CG << endl;
    }
    for (int x = 0; x < k; x++) {
        cout << Input3[x].ID << ' ';
        cout << Input3[x].DG << ' ';
        cout << Input3[x].CG << endl;
    }
    for (int x = 0; x < m; x++) {
        cout << Input4[x].ID << ' ';
        cout << Input4[x].DG << ' ';
        cout << Input4[x].CG << endl;
    }
    return 0;
}