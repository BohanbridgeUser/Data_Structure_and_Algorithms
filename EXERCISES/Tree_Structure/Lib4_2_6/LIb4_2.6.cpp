#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Oridinary Tree */
typedef char ElementofOriTree;
typedef struct TNode* PtrToTNode;	// 普通树结构
typedef struct CNode* PtrToCNode;	// 存储指向子树的指针的链表
typedef PtrToTNode ElementofCNode;
struct CNode {
	ElementofCNode Data;
	PtrToCNode Next;
};
struct TNode {
	ElementofOriTree* Data;
	int Tag;
	PtrToCNode Child;
};
typedef PtrToTNode OriTree;

OriTree BuildTree()
{
	OriTree T = (OriTree)malloc(sizeof(struct TNode));
	T->Data = (ElementofOriTree*)malloc(261 * sizeof(ElementofOriTree));
	memcpy(T->Data, "root\0", 5);
	T->Tag = -1;
	T->Child = (PtrToCNode)malloc(sizeof(struct CNode));
	T->Child->Data = NULL;
	T->Child->Next = NULL;
	return T;
}
void InsertTree(OriTree T, ElementofOriTree* X)
{
	int i = 0, len = strlen(X);
	if (!T) return;
	OriTree TEMP = T;
	while (i < len ) {
		int j = 0;
		char* tmp = (char*)malloc(261 * sizeof(char));
		while (X[i] != '\\' && X[i] != '\0') {
			tmp[j++] = X[i++];
		}
		tmp[j] = '\0';
		int tag = 0;
		if (X[i++] == '\\') tag = 1;
		
		int n = strlen(tmp);

		while ( (memcmp(TEMP->Data, tmp,n) != 0 || TEMP->Tag != tag)  ) {
			PtrToCNode CTMP;
			if (TEMP->Child) {
				CTMP = TEMP->Child;
			}
			else {
				TEMP->Child = (PtrToCNode)malloc(sizeof(struct CNode));
				TEMP->Child->Data = NULL;
				TEMP->Child->Next = NULL;
				CTMP = TEMP->Child;
			}
			while ( CTMP->Next ) {
				if ( strcmp(tmp, CTMP->Next->Data->Data) == 0 && CTMP->Next->Data->Tag == tag ) {
					TEMP = CTMP->Next->Data;
					break;
				}
				else if (tag == CTMP->Next->Data->Tag) {
					if (strcmp(tmp, CTMP->Next->Data->Data) < 0) {
						PtrToCNode NewNode = (PtrToCNode)malloc(sizeof(struct CNode));
						NewNode->Data = (ElementofCNode)malloc(sizeof(struct TNode));
						NewNode->Data->Data = (ElementofOriTree*)malloc(261 * sizeof(char));
						strcpy(NewNode->Data->Data, tmp);
						NewNode->Data->Tag = tag;
						NewNode->Data->Child = NULL;
						NewNode->Next = CTMP->Next;
						CTMP->Next = NewNode;
					}
					else {
						CTMP = CTMP->Next;
					}
				}
				else if (tag == 1 && CTMP->Next->Data->Tag == 0) {
					PtrToCNode NewNode = (PtrToCNode)malloc(sizeof(struct CNode));
					NewNode->Data = (ElementofCNode)malloc(sizeof(struct TNode));
					NewNode->Data->Data = (ElementofOriTree*)malloc(261 * sizeof(char));
					strcpy(NewNode->Data->Data, tmp);
					NewNode->Data->Tag = tag;
					NewNode->Data->Child = NULL;
					NewNode->Next = CTMP->Next;
					CTMP->Next = NewNode;
				}
				else if (tag == 0 && CTMP->Next->Data->Tag == 1) {
					CTMP = CTMP->Next;
				}
			}
			if (!CTMP->Next) {
				CTMP->Next = (PtrToCNode)malloc(sizeof(struct CNode));
				CTMP->Next->Data = (ElementofCNode)malloc(sizeof(struct TNode));
				CTMP->Next->Data->Data = (ElementofOriTree*)malloc(261 * sizeof(char));
				strcpy(CTMP->Next->Data->Data, tmp);
				CTMP->Next->Data->Tag = tag;
				CTMP->Next->Data->Child = NULL;
				CTMP->Next->Next = NULL;
			}
			TEMP = CTMP->Next->Data;
		}
		free(tmp);
	}
}

void PreorderTraversal(OriTree T, int Layer)
{
	if (T) {
		for (int i = 0; i < Layer; i++) printf("  ");
		printf("%s\n", T->Data);
		if (T->Child) {
			for (PtrToCNode TEMP = T->Child; TEMP->Next; TEMP = TEMP->Next) {
				PreorderTraversal(TEMP->Next->Data,Layer+1);
			}
		}
	}
}
int main( int argc, char* argv )
{
	int N;
	scanf("%d\n", &N);
	OriTree T = BuildTree();
	for (int i = 0; i < N; i++) {
		char* tmp = (char*)malloc(260 * sizeof(char));
		scanf("%s", tmp);
		char gc;
		while ((gc = getchar()) != '\n');
		InsertTree(T, tmp);
	}
	PreorderTraversal(T,0);
	return 0;
}