#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int FindHash(int Hash[], int P, int Key)
{
    int pos = Key % P;
    if (Hash[pos] == Key) return pos;
    else {
        int newpos = pos;
        while (Hash[newpos] > -1 && Hash[newpos] != Key) {
            newpos++;
            if (newpos >= P) newpos = newpos - P;
        }
        return newpos;
    }
}

void HashTable(int Num[], int N, int Hash[], int P)
{
    int j = 0;
    for (int i = 0; i < N; i++) {
        int pos = FindHash(Hash,P,Num[i]);
        if (Hash[pos] == -1) Hash[pos] = Num[i];
    }
}

int main()
{
    int N, P;
    cin >> N;
    cin >> P;
    int* Num = new int[N];
    for (int i = 0; i < N; i++) cin >> Num[i];
    int* Hash = new int[P];
    for (int i = 0; i < P; i++) Hash[i] = -1;
    HashTable(Num, N, Hash, P);
    cout << FindHash(Hash, P, Num[0]);
    for (int i = 1; i < N; i++) {
        cout <<' ' << FindHash(Hash, P, Num[i]);
    }
    return 0;
}

