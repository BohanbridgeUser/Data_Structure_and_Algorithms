#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

typedef struct INode* PtrToINode;
struct INode {
	string Data;
	int Pri;
};

typedef PtrToINode ElementofHeap;
typedef struct HNode* PtrToHNode;
struct HNode {
	ElementofHeap* Data;
	int Size;
};
typedef PtrToHNode Heap;

Heap CreateH()
{
	Heap H = (Heap)malloc(sizeof(struct HNode));
	H->Data = (ElementofHeap*)malloc(10001 * sizeof(ElementofHeap));
	H->Data[0] = new INode;
	H->Data[0]->Pri = 0;
	H->Size = 0;
	return H;
}
int IsEmptyH(Heap H)
{
	if (!H->Size) {
		return 1;
	}
	else {
		return 0;
	}
}
Heap Push(Heap H, ElementofHeap X)
{
	H->Data[++H->Size] = X;
	int Child = H->Size;
	while ( H->Data[Child]->Pri <= H->Data[Child / 2]->Pri ) {
		ElementofHeap TEMP = H->Data[Child];
		H->Data[Child] = H->Data[Child / 2];
		H->Data[Child / 2] = TEMP;
		Child /= 2;
	}
	return H;
}
ElementofHeap Pop( Heap H )
{
	if (!IsEmptyH(H)) {
		ElementofHeap RET = H->Data[1];
		H->Data[1] = H->Data[H->Size--];
		int Parent = 1, Child = Parent * 2;
		for (;Parent * 2 <= H->Size; Parent = Child) {
			Child = Parent * 2;
			if (Child + 1 <= H->Size && H->Data[Child]->Pri >= H->Data[Child + 1]->Pri ) Child += 1;
			if (H->Data[Child]->Pri <= H->Data[Parent]->Pri) {
				ElementofHeap TEMP = H->Data[Parent];
				H->Data[Parent] = H->Data[Child];
				H->Data[Child] = TEMP;
			}
		}
		return RET;
	}
	else {
		return NULL;
	}
}
int Char2int(string S3)
{
	int sum = 0;
	int len = S3.length();
	int c = 1;
	for (int i = len - 1; i >= 0; i--) {
		sum += c * (S3[i] - 48);
		c *= 10;
	}
	return sum;
}
Heap Insert( Heap H, int N )
{
	for (int i = 0; i <= N; i++) {
		string TMP;
		getline(cin, TMP);
		string S1;
		int n;
		n = TMP.find(' ');
		S1 = TMP.substr(0, n);
		TMP = TMP.substr(n + 1);
		n = TMP.find(' ');
		string S2 = TMP.substr(0, n);
		TMP = TMP.substr(n + 1);
		string S3 = TMP;
		if (S1 == "PUT") {
			PtrToINode NewNode = new INode;
			NewNode->Data = S2;
			NewNode->Pri = Char2int(S3);
			H = Push(H, NewNode);
		}
		else if (S1 == "GET") {
			ElementofHeap Out = Pop(H);
			if (Out != NULL ) {
				cout << Out->Data << '\n';
			}
			else {
				cout << "EMPTY" <<' '<< "QUEUE!" << endl;
			}
		}
	}
	return H;
}
int main()
{
	int N;
	cin >> N;
	Heap H = CreateH();
	H = Insert(H, N);
	return 0;
}