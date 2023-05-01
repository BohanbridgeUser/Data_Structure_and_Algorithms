#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int ElementofSet;
struct SNode {
    ElementofSet* Data;
};
typedef struct SNode* Set;

Set CreateS()
{
    Set S = (Set)malloc(sizeof(struct SNode));
    S->Data = (ElementofSet*)malloc(10001 * sizeof(ElementofSet));
    for (int i = 1; i <= 10001; i++) {
        S->Data[i] = 10001;
    }
    S->Data[0] = 0;
    return S;
}
int FindS(Set S, ElementofSet X)
{
    int OX = X;
    while (S->Data[OX] >= 0 && S->Data[OX] < 10001) {
        OX = S->Data[OX];
    }
    if (X != OX) {
        S->Data[X] = OX;
    }
    return OX;
}
Set MergeS(Set S, ElementofSet X,ElementofSet Y)
{
    int OX, OY;
    OX = FindS(S, X);
    OY = FindS(S, Y);
    if (fabs(S->Data[OX]) < fabs(S->Data[OY])) {
        S->Data[OY] = OX;
        S->Data[OX]--;
    }
    else {
        S->Data[OX] = OY;
        S->Data[OY]--;
    }
    return S;
}
int CheckS(Set S, ElementofSet X, ElementofSet Y)
{
    return 0;
}
int main()
{
    int N;
    scanf("%d", &N);
    Set S = CreateS();

    for (int i = 0; i < N; i++) {
        int K;
        scanf("%d", &K);
        int O;
        scanf("%d", &O);
        if (S->Data[O] == 10001) S->Data[O] = -1;
        for (int j = 0; j < K - 1; j++) {
            int P;
            scanf("%d", &P);
            MergeS(S,O,P);
        }
    }
    for (int i = 1; i < 10001; i++) {
        if (S->Data[i] < 10001) S->Data[0] ++;
    }
    printf("%d ", S->Data[0]);
    int cnt=0;
    for (int i = 1; i < 10001; i++) {
        if (S->Data[i] < 0) cnt++;
    }
    printf("%d\n", cnt);

    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int X1, X2;
        scanf("%d %d", &X1, &X2);
        if (FindS(S, X1) == FindS(S, X2)) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}

