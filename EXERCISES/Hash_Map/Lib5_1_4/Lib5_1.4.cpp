#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int HKey(string a)
{
    int len = a.length();
    int i = 0,ret = 0;
    i = len >= 3 ? len - 1 - 2 : 0;
    for (i; i < len; i++) {
        ret = ret << 5;
        ret += a[i] - 'A';
    }
    return ret;
}
int Hash(string HashTable[],string Input[], int N, int P,int i)
{
    int Pos = HKey(Input[i]) % P;
    int ret;
    if (HashTable[Pos] == "\0") {
        HashTable[Pos] = Input[i];
        ret = Pos;
    }
    else {
        int NewPos, CurrentPos, c = 0;
        NewPos = CurrentPos = Pos;
        while (HashTable[NewPos] != "\0" && HashTable[NewPos] != Input[i]) {
            if (++c % 2) {
                NewPos = CurrentPos + (c + 1) / 2 * (c + 1) / 2;
                if (NewPos >= P) NewPos = NewPos % P;
            }
            else {
                NewPos = CurrentPos - (c / 2) * (c / 2);
                while (NewPos <= 0) NewPos += P;
            }
        }
        HashTable[NewPos] = Input[i];
        ret = NewPos;
    }
    return ret;
}

int main()
{
    int N, P;
    cin >> N;
    cin >> P;
    string* Input = new string[N];
    for (int i = 0; i < N; i++) cin >> Input[i];
    string* HashTable = new string[P];
    for (int i = 0; i < P; i++) HashTable[i] = "\0";
    int out = Hash(HashTable, Input, N, P, 0);
    cout << out;
    for (int i = 1; i < N; i++) cout <<" "<< Hash(HashTable, Input, N, P, i);
    return 0;
}

