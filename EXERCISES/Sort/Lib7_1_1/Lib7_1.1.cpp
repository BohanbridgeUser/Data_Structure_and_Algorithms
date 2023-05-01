#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

typedef struct Inf* PtrToInf;
struct Inf {
    char* ID;
    char* Name;
    int Grade;
};
typedef PtrToInf Information;
typedef PtrToInf* Information2;

void Swap(Information I, int a, int b)
{
    struct Inf tmp = I[a];
    I[a] = I[b];
    I[b] = tmp;
}

int Comp1(const void* a, const void* b)
{
    return strcmp((*((PtrToInf*)a))->ID, (*((PtrToInf*)b))->ID);
}
int Comp2(const void* a, const void* b)
{
    int k = strcmp((*((PtrToInf*)a))->Name, (*((PtrToInf*)b))->Name);
    if(!k) k = strcmp((*((PtrToInf*)a))->ID, (*((PtrToInf*)b))->ID);
    return k;
}
int Comp3(const void* a, const void* b)
{
    int k = (*((PtrToInf*)a))->Grade > (*((PtrToInf*)b))->Grade ? 1 : 0;
    if (!k) {
        k = (*((PtrToInf*)a))->Grade < (*((PtrToInf*)b))->Grade ? -1 : 0;
        if (!k) {
            k = strcmp((*((PtrToInf*)a))->ID, (*((PtrToInf*)b))->ID);
        }
    }
    return k;
}
void SSS(Information I, int N, int C)
{
    switch(C) {
    case 1: qsort(I,N, sizeof(struct Inf), Comp1);
        break;
    case 2: qsort(I, N, sizeof(struct Inf), Comp2);
        break;
    case 3: qsort(I, N, sizeof(struct Inf), Comp3);
        break;
    }
}
void SSS2(Information2 I, int N, int C)
{
    switch (C) {
    case 1: qsort(I, N, sizeof(PtrToInf), Comp1);
        break;
    case 2: qsort(I, N, sizeof(PtrToInf), Comp2);
        break;
    case 3: qsort(I, N, sizeof(PtrToInf), Comp3);
        break;
    }
}

int main()
{
    int N, C;
    cin >> N;
    cin >> C;

    /*Information I = new Inf[N];
    for (int i = 0; i < N; i++) {
        I[i].Name = new char[9];
        I[i].ID = new char[7];
        cin >> I[i].ID;
        cin >> I[i].Name;
        cin >> I[i].Grade;
    }*/

    Information2 I = new PtrToInf[N];
    for (int i = 0; i < N; i++) I[i] = new Inf;
    for (int i = 0; i < N; i++) {
        I[i]->Name = new char[9];
        I[i]->ID = new char[7];
        cin >> I[i]->ID;
        cin >> I[i]->Name;
        cin >> I[i]->Grade;
    }
    SSS2(I,N, C);
    for (int i = 0; i < N; i++) {
        cout << I[i]->ID<<' ';
        cout << I[i]->Name << ' ';
        cout << I[i]->Grade << endl;
    }
    return 0;
}

