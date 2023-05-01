#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
struct Mdata {
    int M;
    int T;
};

int HashChekc(int* T,int* collected, int Key, int N)
{
    int hash = Key % N;
    if (T[hash] == Key) {
        return 1;
    }
    else {
        int NewPos;
        NewPos = hash;
       // printf("hash = %d\n", hash);
        while (collected[NewPos] != 0 && T[NewPos] != Key) {
            NewPos += 1;
            //printf("NewPos = %d\n", NewPos);
            if (NewPos >= N) NewPos %= N;
        }
        if (T[NewPos] == Key) {
            return 1;
        }
        else {
            return 0;
        }
    }
}
int FindNext(int* T,int* collected, int N, int i)
{
    int minv = 65535, min = -1;
    for (int j = 0; j < N; j++) {
        if (T[j] > i && T[j] < minv && collected[j] == 0) {
            min = j;
            minv = T[j];
        }
    }
    return min;
}
void Func(int* T, int* O,struct Mdata* M, int N, int j)
{
    int* collected = new int[N];
    for (int i = 0; i < N; i++) collected[i] = 0;
    int* po = O;
    int p = 0,q = 0,flag =0;
    //int cnt = 0;
    while (p < j ) {
        //cnt++;
        if (collected[M[p].T] == 1 && flag == 0) {
            p++;
            q++;
            continue;
        }
        else if(collected[M[p].T] == 1 && flag == 1){
            p++;
            continue;
        }
        if (HashChekc(T, collected, M[p].M, N) == 1) {
            *(po++) =  M[p].M;
            collected[M[p].T] = 1;
            if (flag == 1) {
                p = q;
                flag = 0;
            }
            else {
                p++;
                q++;
            }
        }
        else {
            if (flag == 0) {
                q = p;
                flag = 1;
            }
            p++;
        }
        /*printf("O = ");
        for (int i = 0; i < j; i++) {
            printf("%d ", O[i]);
        }
        printf("\n");
        printf("collected = ");
        for (int i = 0; i < j; i++) {
            printf("%d ", collected[i]);
        }
        printf("\t");

        printf("p = %d  q = %d flag = %d\n", p, q, flag);*/
    }
}
int Compare(const void* a, const void* b)
{
    return (*(struct Mdata*)a).M - (*(struct Mdata*)b).M;
}
int main()
{
    int N;
    scanf("%d", &N);
    int* T = new int[N];
    int j = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &T[i]);
        if (j > -1) j++;
    }
    int* O = new int[j];
    for (int i = 0; i < j; i++) O[i] = -1;
    struct Mdata* M = new struct Mdata[j];
    j = 0;
    for (int i = 0; i < N; i++) {
        if (T[i] > -1) {
            M[j].M = T[i];
            M[j++].T = i;
        }
    }
    qsort(M, j, sizeof(struct Mdata), Compare);
    /*for (int i = 0; i < j; i++) {
        printf("%d %d\n", M[i].M, M[i].T);
    }*/
    Func(T, O, M, N,j);
    int i = 1;
    printf("%d", O[0]);
    while(O[i] != -1 && i < N) printf(" %d", O[i++]);
    return 0;
}

