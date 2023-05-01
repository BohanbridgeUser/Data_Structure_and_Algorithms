#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Heap */
#define maxsize 10001
typedef int ElementofHeap;
typedef struct HNode* PtrToHNode;
struct HNode {
	ElementofHeap* Data;
	int Size;
	int MaxSize;
};
typedef PtrToHNode Heap;

Heap CreateHeap( int N )
{
	Heap H = (Heap)malloc(sizeof(struct HNode));
	H->Data = (ElementofHeap*)malloc((N+1) * sizeof(ElementofHeap));
	H->Size = 0;
	H->Data[0] = -1;
	H->MaxSize = N;
	return H;
}
int IsEmptyH(Heap H)
{
	if (!H->Size) return 1;
	else return 0;
}
int IsFullH(Heap H)
{
	if (H->Size == H->MaxSize) return 1;
	else return 0;
}
Heap Push(Heap H, ElementofHeap X)
{
	if (IsFullH(H)) return H;
	else {
		H->Data[++H->Size] = X;
		int Child = H->Size, Parent = Child / 2;
		for (Child; Child > 0; Child /= 2, Parent = Child / 2) {
			if (H->Data[Child] <=  H->Data[Parent]) {
				ElementofHeap tmp = H->Data[Parent];
				H->Data[Parent] = H->Data[Child];
				H->Data[Child] = tmp;
			}
		}
		return H;
	}
}
ElementofHeap Pop(Heap H)
{
	ElementofHeap RET;
	if (IsEmptyH(H)) {
		RET = 0;
		return RET;
	}
	else {
		RET = H->Data[1];
		H->Data[1] = H->Data[H->Size--];
		int Parent = 1, Child;
		while (Parent * 2 <= H->Size) {
			Child = Parent * 2;
			if (Parent * 2 + 1 <= H->Size && H->Data[Child] >= H->Data[Child + 1]) Child++;
			if (H->Data[Parent] >= H->Data[Child]) {
				ElementofHeap tmp = H->Data[Parent];
				H->Data[Parent] = H->Data[Child];
				H->Data[Child] = tmp;
			}
			Parent = Child;
		}
		return RET;
	}
}
int main()
{
	int N;
	scanf("%d\n", &N);

	Heap H = CreateHeap(N);
	for (int i = 0; i < N; i++) {
		int tmp = 0;
		scanf("%d", &tmp);
		H = Push(H, tmp);
	}

	int sumlen = 0;
	for (int i = 1; i <= H->Size; i++) {
		sumlen += H->Data[i];
	}

	int sumcost = 0;
	int tmp = 1;
	while (H->Size>1) {
		tmp = 0;
		tmp = Pop(H)+Pop(H);
		sumcost += tmp;
		H = Push(H, tmp);
	}
	printf("%d\n", sumcost);
	return 0;
}

