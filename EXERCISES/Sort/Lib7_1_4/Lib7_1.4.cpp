#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
    int N;
    cin >> N;
    int* c = new int[51];
    for (int i = 0; i < 51; i++) c[i] = 0;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        c[t]++;
    }

    for (int i = 0; i < 51; i++) {
        if (c[i] > 0) cout << i << ":" << c[i] << endl;
    }
    return 0;
}

