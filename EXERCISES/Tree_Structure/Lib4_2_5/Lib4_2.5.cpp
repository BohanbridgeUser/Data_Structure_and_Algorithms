#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Heap Defination */
#define maxsize 1010
typedef int ElementofHeap;
typedef struct HNode* PtrToHNode;
struct HNode {
	ElementofHeap* Data;
	int Size;
	int MaxSize;
};
typedef PtrToHNode Heap;

Heap CreateH()
{
	Heap H = (Heap)malloc(sizeof(struct HNode));
	H->Data = (ElementofHeap*)malloc(maxsize * sizeof(ElementofHeap));
	H->MaxSize = maxsize;
	H->Size = 0;
	H->Data[0] = -10010;
	for (int i = 1; i < H->MaxSize; i++) H->Data[i] = 10010;
	return H;
}
int IsFullH(Heap H)
{
	if (H->Size == maxsize )return 1;
	else return 0;
}
Heap PushHeap( Heap H, ElementofHeap X )
{
	if (!IsFullH(H)) {
		int Child = ++H->Size, Parent = Child / 2;
		H->Data[Child] = X;
		while ( H->Data[Parent] >= H->Data[Child]) {
			int tmp = H->Data[Parent];
			H->Data[Parent] = H->Data[Child];
			H->Data[Child] = tmp;
			Parent /= 2;
			Child /= 2;
		}
		return H;
	}
	else {
		return H;
	}
}
int IsEmptyH(Heap H)
{
	if (!H->Size) return 1;
	else return 0;
}
ElementofHeap PopHeap(Heap H)
{
	ElementofHeap RET = -10010;
	if (!IsEmptyH(H)) {
		RET = H->Data[1];
		int Parent = 1, Child;
		H->Data[1] = H->Data[H->Size];
		while (Parent * 2 <= H->Size) {
			Child = Parent * 2;
			if (Parent * 2 + 1 <= H->Size && H->Data[Child] > H->Data[Child + 1]) Child += 1;
			int tmp = H->Data[Parent];
			H->Data[Parent] = H->Data[Child];
			H->Data[Child] = tmp;
			Parent = Child;
		}
		H->Size--;
		return RET;
	}
	else {
		return RET;
	}
}
int FindHeap(Heap H, ElementofHeap X)
{
	int Parent = 1;
	for (; Parent <= H->Size; Parent++) {
		if (H->Data[Parent] == X) return Parent;
	}
	if (Parent == H->Size + 1) return -1;
}
int Char2Int(char* tmp, int Beg)
{
	char* figure = (char*)malloc(6 * sizeof(char));
	for (int i = 0; i < 6; i++)figure[i] = '\0';
	int i = 0;
	if (tmp[Beg] == '-') {
		Beg += 1;
		while (tmp[Beg] != ' ' && tmp[Beg] != '\0') {
			figure[i++] = tmp[Beg++];
		}
		i = strlen(figure);
		int RET = 0, c = 1;
		for (i -= 1; i >= 0; i--) {
			RET += (figure[i] - 48) * c;
			c *= 10;
		}
		free(figure);
		return -RET;
	}
	else {
		while (tmp[Beg] != ' ' && tmp[Beg] != '\0') {
			figure[i++] = tmp[Beg++];
		}
		i = strlen(figure);
		int RET = 0, c = 1;
		for (i -= 1; i >= 0; i--) {
			RET += (figure[i] - 48) * c;
			c *= 10;
		}
		free(figure);
		return RET;
	}
}
void Check(Heap H, int M)
{
	for (int i = 0; i < M; i++) {
		char* tmp = (char*)malloc(30 * sizeof(char));
		int x, y;
		scanf("%d %[^\n]", &x, tmp);
		if (memcmp(tmp, "is the root", 11) == 0) {
			if (x == H->Data[1]) printf("T\n");
			else printf("F\n");
		}
		else if (memcmp(tmp, "and", 3) == 0) {
			y = Char2Int(tmp,4);
			int xi = FindHeap(H, x);
			int yi = FindHeap(H, y);
			if (xi / 2 == yi / 2)printf("T\n");
			else printf("F\n");

		}
		else if (memcmp(tmp, "is the parent of", 16) == 0) {
			y = Char2Int(tmp, 17);
			int xi = FindHeap(H, x);
			int yi = FindHeap(H, y);
			if (yi / 2 == xi) printf("T\n");
			else printf("F\n");
		}
		else if (memcmp(tmp, "is a child of", 13) == 0) {
			y = Char2Int(tmp, 14);
			int xi = FindHeap(H, x);
			int yi = FindHeap(H, y);
			if (xi / 2 == yi) printf("T\n");
			else printf("F\n");
		}
	}
}
int main(int argc, char* argv )
{
	int N, M;
	scanf("%d %d\n", &N, &M);
	Heap H = CreateH();
	for (int i = 0; i < N; i++) {
		int tmp;
		scanf("%d", &tmp);
		H = PushHeap(H, tmp);
	}
	Check(H, M);
	return 0;
}