#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int CompareI(const void* a, const void* b)
{
	return (*(int*)a) - (*(int*)b);
}
int FindI(int* Order, int b, int e, int Num)
{
	int RET,i;
	for (i = b; i <= e; i++) {
		if (Order[i] == Num) {
			RET = i;
			break;
		}
	}
	if (i > e) RET = -1;
	return RET;
}
int MainCheck( int* Input, int N, int ib, int ie, int* Order, int ob, int oe, int tag ,int* Output, int Outroot)
{
	int Iroot = ib;
	int Oroot = FindI(Order, ob, oe, Input[Iroot]);
	Output[Outroot] = Input[Iroot];
	if (Oroot == ob) {
		if (ib != ie) {
			int ret = MainCheck(Input, N, ib + 1, ie, Order, Oroot + 1, oe, tag, Output, Outroot - 1);
			if (ret == 1) return 1;
			else return 0;
		}
		else {
			return 1;
		}
	}
	else if (Oroot == oe) {
		if (ib != ie) {
			int ret = MainCheck(Input, N, ib + 1, ie, Order, ob, Oroot - 1, tag, Output, Outroot - 1);
			if (ret == 1) return 1;
			else return 0;
		}
		else {
			return 1;
		}
	}
	else {
		if ( Input[ib + 1] < Input[ib] && tag == 1 ) {
			return 0;
		}
		else if( Input[ib+1] >= Input[ib] && tag == 0) {
			return 0;
		}
		else if( Input[ib+1] < Input[ib] ){
			tag = 0;
			int llen = Oroot - ob, rlen = oe - Oroot;
			int l = MainCheck(Input, N, ib + 1, ib + llen, Order, ob, ob + llen - 1, tag, Output, Outroot - rlen - 1 );
			int r = MainCheck(Input, N, ib + llen + 1, ib + llen + rlen, Order, Oroot + 1, Oroot + rlen, tag, Output, Outroot - 1);
			if (l == 1 && r == 1) return 1;
			else return 0;
		}
		else if (Input[ib + 1] >= Input[ib]) {
			tag = 1;
			int llen = oe - Oroot, rlen = Oroot - ob;
			int l = MainCheck(Input, N, ib + 1, ib + llen, Order, Oroot + 1, Oroot + llen, tag, Output, Outroot - rlen - 1);
			int r = MainCheck(Input, N, ib + llen + 1, ib + llen + rlen, Order, ob, ob + rlen - 1, tag, Output, Outroot - 1);
			if (l == 1 && r == 1) return 1;
			else return 0;
		}
	}
}

int main(int argc, char* argv[])
{
	int N;
	scanf("%d", &N);
	int* Input = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) scanf("%d", &Input[i]);
	int* Order = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) Order[i] = Input[i];
	qsort(Order, N, sizeof(int), CompareI);
	int* Output = (int*)malloc(N * sizeof(int));
	int tag = 2;
	int ret = MainCheck(Input, N, 0, N - 1, Order, 0, N - 1, tag, Output, N - 1);
	if ( ret ) {
		printf("YES\n");
		printf("%d", Output[0]);
		for (int i = 1; i < N; i++) printf(" %d", Output[i]);
	}
	else {
		printf("NO\n");
	}
	return 0;
}