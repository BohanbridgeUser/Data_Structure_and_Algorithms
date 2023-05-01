#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

int HeightCal(int N)
{
    double h = log(N+1) / log(2);
    double integer, decimal;
    decimal = modf(h, &integer);
    if (decimal == 0) {
        return integer;
    }
    else {
        return integer + 1;
    }
}

void OrderChange(int* Input, int Beg, int End, int* Output, int O)
{
    int N = End - Beg + 1;
    if (N <= 0) return;
    else if (N == 1) {
        Output[O] = Input[Beg];
    }
    else {
        int h = HeightCal(N);
        if (N - (pow(2, h - 1) - 1) <= pow(2, h - 1) / 2) {
            int nr = ((pow(2, h - 1) - 1) - 1) / 2;
            Output[O] = Input[End - nr];
            OrderChange(Input, Beg, End - nr - 1, Output, O * 2);
            OrderChange(Input, End - nr + 1, End, Output, O * 2 + 1);
        }
        else {
            int nr = ((pow(2, h - 1) - 1) - 1) / 2 + ((N - (pow(2, h - 1) - 1)) - (pow(2, h - 1) / 2));
            Output[O] = Input[End - nr];
            OrderChange(Input, Beg, End - nr - 1, Output, O * 2);
            OrderChange(Input, End - nr + 1, End, Output, O * 2 + 1);
        }
        return;
    }
}

int main()
{
    int N;
    cin >> N ;
    
    int* Input = new int[1000];
    for (int i = 0; i < N; i++) cin >> Input[i];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (Input[j] > Input[j + 1]) {
                int tmp = Input[j];
                Input[j] = Input[j + 1];
                Input[j + 1] = tmp;
            }
        }
    }

    int* Output = new int[N + 1];
    OrderChange(Input, 0, N-1, Output,1);
    delete(Input);
    cout << Output[1];
    for (int i = 2; i <= N; i++) cout << ' ' << Output[i];
    return 0;
}
