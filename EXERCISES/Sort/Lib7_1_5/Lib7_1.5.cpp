#include <iostream>

int Check(int a[], int N)
{
    int i;
    for (i = 1; i < N; i++) 
        if (a[i] != i) break;
    return i;
}
void Swap(int& a, int& b)
{
    int t = a; a = b; b = t;
}
int Find(int a[], int N, int x)
{
    int i;
    for (i = 0; i < N; i++) 
        if (a[i] == x) break;
    return i;
}
int main()
{
    using namespace std;

    int N;
    cin >> N;
    int* a = new int[N];
    for (int i = 0; i < N; i++) cin >> a[i];
    int* collected = new int[N];
    for (int i = 0; i < N; i++) collected[i] = 0;
    int total = 0, cnt;
    for (int i = 0; i < N; i++) {
        int j = i, in0 = 0, crt = 0;
        cnt = 0;
        while (a[j] != i && collected[j] == 0) {
            crt = 1;
            if (a[a[j]] == 0) in0 = 1;
            collected[j] = 1;
            j = a[j];
            cnt++;
        }
        if(collected[j] == 0)collected[j] = 1;
        if (in0 == 0) cnt += 2;
        if(crt == 1) total += cnt;
    }
    
    cout << total << endl;
    return 0;
}

