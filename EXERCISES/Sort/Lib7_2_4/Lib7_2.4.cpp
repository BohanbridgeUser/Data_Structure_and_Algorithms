#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct Inf* PtrToInf;
struct Inf {
    long long ID;
    int Grade;
    int Rank;
};
struct Head {
    PtrToInf Data;
    int Beg;
    int End;
    int Size;
};
typedef struct Head* List;

int Compare(const void* a, const void* b)
{
    PtrToInf p = (PtrToInf)a, q = (PtrToInf)b;
    if (p->Grade == q->Grade) {
        return p->ID < q->ID ? -1 : 1;
    }
    return p->Grade > q->Grade ? -1 : 1;
}

void Sort(List head, int N)
{
    for (int i = 0; i < N; i++) {
        qsort(head[i].Data, head[i].Size, sizeof(struct Inf), Compare);
        head[i].Data[head[i].Beg].Rank = 1;
        for (int j = head[i].Beg + 1; j <= head[i].End; j++) {
            if (head[i].Data[j].Grade == head[i].Data[j - 1].Grade) head[i].Data[j].Rank = head[i].Data[j - 1].Rank;
            else head[i].Data[j].Rank = j + 1;
        }
    }

    int total = 0;
    for (int i = 0; i < N; i++) total += head[i].Size;
    cout << total << endl;
    int max, rank1 = 1, last = 101, rank2;
    for (int k = 0; k < total; k++) {
        int i = 0;
        while (head[i].Beg >= head[i].Size) i++;
        max = i;
        for (i = max + 1; i < N; i++)
            if (head[i].Beg < head[i].Size && Compare(&(head[i].Data[head[i].Beg]), &(head[max].Data[head[max].Beg])) == -1) max = i;
        
        if (head[max].Data[head[max].Beg].Grade != last) rank1 = k + 1;

        cout << head[max].Data[head[max].Beg].ID << ' ' << rank1 << ' ' << max + 1 << ' ' << head[max].Data[head[max].Beg].Rank << endl;
        last = head[max].Data[head[max].Beg].Grade;
        head[max].Beg++;
    }
}

int main()
{
    int N;
    cin >> N;
    List head = new Head[N];
    for (int i = 0; i < N; i++) {
        cin >> head[i].Size;
        head[i].Beg = 0;
        head[i].End = -1;
        head[i].Data = new Inf[head[i].Size];
        for (int j = 0; j < head[i].Size; j++) {
            cin >> head[i].Data[j].ID;
            cin >> head[i].Data[j].Grade;
            head[i].End++;
        }
        head[i].Size = head[i].End + 1;
    }
    Sort(head, N);
    return 0;
}
