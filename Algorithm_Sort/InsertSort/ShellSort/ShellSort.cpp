#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef int ElementofShellSort;

void ShellSort(ElementofShellSort a[], int N)
{
    int Sedgewick[9] = { 929,505,209,109,41,19,5,1,0 };
    int i, j, k;

    for (i = 0; Sedgewick[i] >= N; i++);

    for (; Sedgewick[i] > 0; i++) {
        for (j = Sedgewick[i]; j < N; j++) {
            ElementofShellSort tmp = a[j];
            for (k = j; k > 0 && a[k - 1] > tmp; k--)
                a[k] = a[k - 1];
            a[k] = tmp;
        }
    }
}

int main()
{
    using namespace std;
    ElementofShellSort a[10] = { 10,9,8,7,6,5,4,3,2,1 };
    ShellSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << ' ';
    return 0;
}
