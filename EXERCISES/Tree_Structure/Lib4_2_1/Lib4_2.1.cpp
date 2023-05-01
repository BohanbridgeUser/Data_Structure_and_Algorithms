#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/* Input Data */
typedef struct InputData* PtrToInputData;
struct InputData {
	char Data;
	char Left;
	char Right;
};
/* Input Data End */

/* Stack Defination */
typedef int ElementOfStack;
typedef struct SNode* PtrToSNode;
struct SNode {
	ElementOfStack Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;
Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
int IsEmptyS( Stack S )
{
	if (S->Next == NULL ) return 1;
	else return 0;
}
Stack Push( Stack S, ElementOfStack X)
{
	PtrToSNode NewNode = (PtrToSNode)malloc(sizeof(struct SNode));
	NewNode->Data = X;
	NewNode->Next = S->Next;
	S->Next = NewNode;
	return S;
}
ElementOfStack Pop( Stack S )
{
	if (!IsEmptyS(S)) {
		ElementOfStack RET = S->Next->Data;
		PtrToSNode TEMP = S->Next;
		S->Next = S->Next->Next;
		free(TEMP);
		return RET;
	}
	else {
		return -1;
	}
}
/* Stack Defination End */

/* BinTree Define */
typedef char Element;
typedef struct TNode* PtrToTNode;
struct TNode {
	Element Data;
	PtrToTNode Left;
	PtrToTNode Right;
};
typedef PtrToTNode BinTree;

BinTree RecursiveB( BinTree T, PtrToInputData Input, int root )
{
	T = (BinTree)malloc(sizeof(struct TNode));
	T->Data = Input[root].Data;
	if ( Input[root].Left != '-' ) {
		T->Left = RecursiveB(T->Left, Input, Input[root].Left - 48 );
	}
	else {
		T->Left = NULL;
	}

	if (Input[root].Right != '-') {
		T->Right = RecursiveB(T->Right, Input, Input[root].Right - 48);
	}
	else {
		T->Right = NULL;
	}
	return T;
}

BinTree BuildTree(int Num)
{
	int* Check = (int*)malloc(Num*sizeof(int));
	for (int i = 0; i < Num; i++) Check[i] = 0;
	PtrToInputData Input = (PtrToInputData)malloc(Num*sizeof(struct InputData));
	for (int i = 0; i < Num; i++) {
		scanf("%c %c %c", &Input[i].Data, &Input[i].Left, &Input[i].Right);
		if (Input[i].Left >= '0' && Input[i].Left <= '9') Check[Input[i].Left - 48] = 1;
		if (Input[i].Right >= '0' && Input[i].Right <= '9') Check[Input[i].Right - 48] = 1;
		char gc;
		while ((gc = getchar()) != '\n');
	}
	int root = 0;
	for (int i = 0; i < Num; i++) {
		if (Check[i] == 0) {
			root = i;
			break;
		}
	}

	BinTree T = NULL;
	T = RecursiveB( T, Input, root );
	free(Input);
	free(Check);
	return T;
}

void PreorderTraversal( BinTree T )
{
	if (T) {
		printf("%c ", T->Data);
		PreorderTraversal(T->Left);
		PreorderTraversal(T->Right);
	}
}
int CheckTree(BinTree T1, BinTree T2)
{
	if ( T1 && T2 ) {
		if ( T1->Data == T2->Data ) {
			if (T1->Left && T2->Left && T1->Right && T2->Right && T1->Left->Data == T2->Left->Data && T1->Right->Data == T2->Right->Data) {
				return CheckTree(T1->Left, T2->Left) & CheckTree(T1->Right, T2->Right);
			}
			else if (T1->Left && T2->Left && T1->Right && T2->Right && T1->Left->Data == T2->Right->Data && T1->Right->Data == T2->Left->Data) {
					return CheckTree(T1->Left, T2->Right) & CheckTree(T1->Right, T2->Left);
			}
			else if (T1->Left && T2->Right && !T1->Right && !T2->Left && T1->Left->Data == T2->Right->Data) {
				return CheckTree(T1->Left, T2->Right);
			}
			else if (T1->Left && T2->Left && !T1->Right && !T2->Right && T1->Left->Data == T2->Left->Data) {
				return CheckTree(T1->Left, T2->Left);
			}
			else if (T1->Right && T2->Left && !T1->Left && !T2->Right && T1->Right->Data == T2->Left->Data) {
				return CheckTree(T1->Right, T2->Left);
			}
			else if (T1->Right && T2->Right && !T1->Left && !T2->Left && T1->Right->Data == T2->Right->Data) {
				return CheckTree(T1->Right, T2->Right);
			}
			else if (!T1->Left && !T2->Left && !T1->Right && !T2->Right){
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else if (!T1 && !T2) {
		return 1;
	}
	else {
		return 0;
	}
}

int main(int argc, char* argv[])
{
	int N;
	scanf("%d\n", &N);
	BinTree T1 = NULL, T2 = NULL;
	if(N) T1 = BuildTree(N);
	scanf("%d\n", &N);
	if(N) T2 = BuildTree(N);
	if (!N )  printf("Yes\n");
	else {
		if (!CheckTree(T1, T2)) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}