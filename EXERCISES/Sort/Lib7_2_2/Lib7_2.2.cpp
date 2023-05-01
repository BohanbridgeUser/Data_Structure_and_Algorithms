#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int IsInsertionSort(int Mid[],int Ori[], int N)
{
    int i;
    for (i = 0; i < N - 1; i++)
        if (Mid[i] > Mid[i+1]) break;
    int k = i;
    for (i; i < N; i++)
        if (Ori[i] != Mid[i]) break;
    if (i == N) return k;
    else return k;
}
void Swap(int& a, int& b)
{
    int t = a; a = b; b = t;
}
void NextInsertion(int Mid[], int k)
{
    for (int j = k; j>0 && Mid[j] < Mid[j-1]; j--) {
        Swap(Mid[j], Mid[j - 1]);
    }
}
int FindLastHeap(int Mid[], int N)
{
    int top = Mid[0],i=1;
    while (Mid[i] < Mid[0]) i++;
    return i - 1;
}
void Percdown(int Mid[], int size)
{
    int Parent, Child;
    int x = Mid[0];
    for (Parent = 0; Parent * 2 + 1 <= size; Parent = Child){
        Child = Parent * 2 + 1;
        if (Child + 1 <= size && Mid[Child + 1] > Mid[Child])
            Child += 1;
        if (Mid[Child] > x) Mid[Parent] = Mid[Child];
        else break;
    }
    Mid[Parent] = x;
}

int main()
{
    int N;
    cin >> N;
    int* Ori = new int[N];
    for (int i = 0; i < N; i++) cin >> Ori[i];
    int* Mid = new int[N];
    for (int i = 0; i < N; i++) cin >> Mid[i];
    int k;
    if ((k =IsInsertionSort(Mid,Ori,N)) == 0) {
        cout << "Heap Sort\n";
        int size = FindLastHeap(Mid, N);
        Swap(Mid[0], Mid[size--]);
        Percdown(Mid, size);
        cout << Mid[0];
        for (int i = 1; i < N; i++) cout <<' ' <<  Mid[i];
    }
    else {
        cout << "Insertion Sort\n";
        NextInsertion(Mid, k + 1);
        cout << Mid[0];
        for (int i = 1; i < N; i++) cout <<' ' <<  Mid[i];
    }
    return 0;
}

