#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>
#include<math.h>

using namespace std;

void Gets(char* TMP)
{
	int i = 0;
	char gc;
	while ((gc = getchar()) != '\n') {
		TMP[i++] = gc;
	}
	int j = i;
	TMP[i] = '\0';
	while (TMP[--j] == ' ') {
		TMP[j] = '\0';
	}
}

/* Oridinary Tree */
typedef string ElementofOriTree;
typedef struct TNode* PtrToTNode;	// 普通树结构
typedef struct CNode* PtrToCNode;	// 存储指向子树的指针的链表
typedef PtrToTNode ElementofCNode;
struct CNode {
	ElementofCNode Data;
	PtrToCNode Next;
};
struct TNode {
	ElementofOriTree Data;
	PtrToCNode Child;
};
typedef PtrToTNode OriTree;

/* Stack */
typedef PtrToTNode ElementofStack;
typedef struct SNode* PtrToSNode;
struct SNode {
	ElementofStack Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;
Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
int IsEmptyS(Stack S)
{
	if (!S->Next)return 1;
	else return 0;
}
Stack Push(Stack S, ElementofStack X)
{
	PtrToSNode NewNode = (Stack)malloc(sizeof(struct SNode));
	NewNode->Data = X;
	NewNode->Next = S->Next;
	S->Next = NewNode;
	return S;
}
ElementofStack Pop(Stack S)
{
	ElementofStack RET;
	if (!IsEmptyS(S)) {
		RET = S->Next->Data;
		if (S->Next->Next) {
			PtrToSNode TEMP = S->Next;
			S->Next = S->Next->Next;
			free(TEMP);
			return RET;
		}
		else {
			PtrToSNode TEMP = S->Next;
			S->Next = NULL;
			free(TEMP);
			return RET;
		}
	}
	else {
		return NULL;
	}
}
void DeleteS(Stack S)
{
	PtrToSNode P = S;
	while (P) {
		PtrToSNode TEMP = P;
		P = P->Next;
		free(TEMP);
	}
}
OriTree BuildTree()
{
	OriTree T = new TNode;
	T->Child = (PtrToCNode)malloc(sizeof(struct CNode));
	T->Child->Data = NULL;
	T->Child->Next = NULL;
	return T;
}
int BlankCalculation(string TMP)
{
	int ret = 0;
	for (int i = 0; i < TMP.length(); i++) {
		string tmp = TMP.substr(i, 1);
		if (tmp == " ") ret++;
	}
	return ret;
}
void InsertTree(OriTree T, int N)
{
	string TMP;
	getline(cin, TMP);
	T->Data = TMP;

	Stack S = CreateS();
	S = Push(S, T);
	int BlankLast = 0;
	for (int i = 1; i < N; i++) {
		getline(cin, TMP);
		int BlankNow = BlankCalculation(TMP);
		TMP = TMP.substr(BlankNow, TMP.length() - BlankNow);
		OriTree TEMP = Pop(S);
		if (BlankNow > BlankLast) {
			S = Push(S, TEMP);
			PtrToCNode NewCNode = (PtrToCNode)malloc(sizeof(struct CNode));
			NewCNode->Data = new TNode;
			NewCNode->Data->Data = TMP;
			NewCNode->Data->Child = (PtrToCNode)malloc(sizeof(struct CNode));
			NewCNode->Data->Child->Data = NULL;
			NewCNode->Data->Child->Next = NULL;

			NewCNode->Next = TEMP->Child->Next;
			TEMP->Child->Next = NewCNode;
			BlankLast = BlankNow;
			S = Push(S, TEMP->Child->Next->Data);
		}
		else if (BlankNow == BlankLast) {
			TEMP = Pop(S);
			S = Push(S, TEMP);
			PtrToCNode NewCNode = (PtrToCNode)malloc(sizeof(struct CNode));
			NewCNode->Data = new TNode;
			NewCNode->Data->Data = TMP;
			NewCNode->Data->Child = (PtrToCNode)malloc(sizeof(struct CNode));
			NewCNode->Data->Child->Data = NULL;
			NewCNode->Data->Child->Next = NULL;

			NewCNode->Next = TEMP->Child->Next;
			TEMP->Child->Next = NewCNode;
			BlankLast = BlankNow;
			S = Push(S, TEMP->Child->Next->Data);
		}
		else if (BlankNow < BlankLast) {
			for (int i = 0; i <= (BlankLast - BlankNow) / 2; i++) {
				TEMP = Pop(S);
			}
			S = Push(S, TEMP);
			PtrToCNode NewCNode = (PtrToCNode)malloc(sizeof(struct CNode));
			NewCNode->Data = new TNode;
			NewCNode->Data->Data = TMP;
			NewCNode->Data->Child = (PtrToCNode)malloc(sizeof(struct CNode));
			NewCNode->Data->Child->Data = NULL;
			NewCNode->Data->Child->Next = NULL;

			NewCNode->Next = TEMP->Child->Next;
			TEMP->Child->Next = NewCNode;
			BlankLast = BlankNow;
			S = Push(S, TEMP->Child->Next->Data);
		}
	}
	DeleteS(S);
}
void PreorderTravelsal(OriTree T, int layer)
{
	if (T) {
		for (int i = 0; i < layer; i++) printf("  ");
		cout << T->Data << '\n';
		for (PtrToCNode TEMP = T->Child; TEMP->Next; TEMP = TEMP->Next) {
			PreorderTravelsal(TEMP->Next->Data, layer + 1);
		}
	}
	else {
		return;
	}
}
PtrToTNode FindX(OriTree T, string X)
{
	if (!T) return NULL;
	Stack S = CreateS();
	S = Push(S, T);
	PtrToTNode  P = T;
	while (!IsEmptyS(S)) {
		P = Pop(S);
		if (P->Data == X) {
			DeleteS(S);
			return P;
		}
		else {
			for (PtrToCNode TEMP = P->Child; TEMP->Next; TEMP = TEMP->Next) {
				S = Push(S, TEMP->Next->Data);
			}
		}
	}
	DeleteS(S);
	return NULL;
}
PtrToTNode FindParent(OriTree T, string X)
{
	if (!T) return NULL;
	Stack S = CreateS();
	S = Push(S, T);
	PtrToTNode RET = NULL;
	while (!IsEmptyS(S)) {
		PtrToTNode P = Pop(S);
		for (PtrToCNode TEMP = P->Child; TEMP->Next; TEMP = TEMP->Next) {
			if (TEMP->Next->Data->Data == X) {
				DeleteS(S);
				return RET = P;
			}
			S = Push(S, TEMP->Next->Data);
		}
	}
	DeleteS(S);
	return RET;
}
int JudgeChild(OriTree T, string X, string Y)
{
	PtrToTNode TofY = FindX(T, Y);
	for (PtrToCNode TEMP = TofY->Child; TEMP->Next; TEMP = TEMP->Next) {
		if (TEMP->Next->Data->Data == X) return 1;
	}
	return 0;
}
int JudgeParent(OriTree T, string X, string Y)
{
	PtrToTNode TofX = FindX(T, X);
	for (PtrToCNode TEMP = TofX->Child; TEMP->Next; TEMP = TEMP->Next) {
		if (TEMP->Next->Data->Data == Y) return 1;
	}
	return 0;
}
int JudgeSibling(OriTree T, string X, string Y)
{
	PtrToTNode PofX = FindParent(T, X);
	if (PofX) {
		for (PtrToCNode TEMP = PofX->Child; TEMP->Next; TEMP = TEMP->Next) {
			if (TEMP->Next->Data->Data == Y) return 1;
		}
		return 0;
	}
	else {
		return 0;
	}
}
int JudgeDescendant(OriTree T, string X, string Y)
{
	PtrToTNode TofY = FindX(T, Y);
	if (FindX(TofY, X) == NULL) {
		return 0;
	}
	else {
		return 1;
	}
	return 0;
}
int JudgeAncestor(OriTree T, string X, string Y)
{
	PtrToTNode TofX = FindX(T, X);
	if (FindX(TofX, Y) == NULL) {
		return 0;
	}
	else {
		return 1;
	}
	return 0;
}
int CheckSentence(OriTree T)
{
	string TMP[6];
	for (int i = 0; i < 6; i++) {
		cin >> TMP[i];
	}

	int RET = 0;
	if (TMP[3] == "child") {
		if (JudgeChild(T, TMP[0], TMP[5]) == 1) RET = 1;
	}
	else if (TMP[3] == "parent") {
		if (JudgeParent(T, TMP[0], TMP[5]) == 1)RET = 2;
	}
	else if (TMP[3] == "sibling") {
		if (JudgeSibling(T, TMP[0], TMP[5]) == 1) RET = 3;
	}
	else if (TMP[3] == "descendant") {
		if (JudgeDescendant(T, TMP[0], TMP[5]) == 1)RET = 4;
	}
	else if (TMP[3] == "ancestor") {
		if (JudgeAncestor(T, TMP[0], TMP[5]) == 1) RET = 5;
	}
	return RET;
}
int main()
{
	int N, M;
	scanf("%d %d\n", &N, &M);
	OriTree T = BuildTree();
	InsertTree(T, N);
	//PreorderTravelsal(T,0);
	for (int i = 0; i < M; i++) {
		if (CheckSentence(T) > 0) {
			printf("True\n");
		}
		else {
			printf("False\n");
		}
	}
	return 0;
}