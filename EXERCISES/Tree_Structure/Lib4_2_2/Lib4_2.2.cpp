#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/* Input Define */
typedef struct InNode* Input;
struct InNode {
	char Left;
	char Right;
};
/* Input Define End */

/* Tree Define */
typedef int ElementofTree;
typedef struct TNode* PtrToTNode;
struct TNode {
	ElementofTree Data;
	PtrToTNode Left;
	PtrToTNode Right;
};
typedef PtrToTNode BinTree;
/* Tree Define End */

/* Queue Define */
typedef BinTree ElementofQueue;
typedef struct QNode* PtrToQNode;
struct QNode {
	ElementofQueue Data;
	PtrToQNode Next;
};
typedef struct Que* Queue;
struct Que {
	PtrToQNode Head;
	PtrToQNode Rear;
};
/* Queue Define End*/

Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct Que));
	Q->Head = (PtrToQNode)malloc(sizeof(struct QNode));
	Q->Head->Next = NULL;
	Q->Rear = Q->Head;
	return Q;
}
int IsEmptyQ(Queue Q)
{
	if ( !Q->Head->Next ) return 1;
	else return 0;
}
Queue InQueue(Queue Q, ElementofQueue X)
{
	PtrToQNode NewNode = (PtrToQNode)malloc(sizeof(struct QNode));
	NewNode->Data = X;
	NewNode->Next = NULL;
	Q->Rear->Next = NewNode;
	Q->Rear = Q->Rear->Next;
	return Q;
}
ElementofQueue DeQueue(Queue Q)
{
	ElementofQueue RET;
	if (!IsEmptyQ(Q)) {
		RET = Q->Head->Next->Data;
		if (Q->Head->Next->Next) {
			PtrToQNode TEMP = Q->Head->Next;
			Q->Head->Next = Q->Head->Next->Next;
			free(TEMP);
		}
		else {
			PtrToQNode TEMP = Q->Head->Next;
			Q->Head->Next = NULL;
			Q->Rear = Q->Head;
			free(TEMP);
		}
		return RET;
	}
	else {
		return NULL;
	}
}

BinTree BuildTree(BinTree T, Input In, int root)
{
	T = (BinTree)malloc(sizeof(struct TNode));
	T->Data = root;
	if (In[root].Left != '-') {
		T->Left = BuildTree(T->Left, In, In[root].Left - 48);
	}
	else {
		T->Left = NULL;
	}
	if (In[root].Right != '-') {
		T->Right = BuildTree(T->Right, In, In[root].Right - 48);
	}
	else {
		T->Right = NULL;
	}
	return T;
}
void CheckLeaf(BinTree T, Queue Q, int* Leaf)
{
	if (T) {
		Q = InQueue(Q, T);
		PtrToTNode TEMP = NULL;
		int i = 0;
		while (!IsEmptyQ(Q)) {
			TEMP = DeQueue(Q);
			if (!TEMP->Left && !TEMP->Right) Leaf[i++] = TEMP->Data;
			if (TEMP->Left) Q = InQueue(Q, TEMP->Left);
			if (TEMP->Right) Q = InQueue(Q, TEMP->Right);
		}
	}
}
void PreorderTraversal(BinTree T)
{
	if (T) {
		PreorderTraversal(T->Left);
		printf("%d ", T->Data);
		PreorderTraversal(T->Right);
	}
}
int main(int argc, char* argv[])
{
	int N;
	scanf("%d\n", &N);
	Input In = (Input)malloc(N * sizeof(struct InNode));
	char gc;
	int* Check = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) Check[i] = 0;
	for (int i = 0; i < N; i++) {
		scanf("%c %c", &In[i].Left, &In[i].Right);
		if (In[i].Left >= '0' && In[i].Left <= '9' ) Check[ In[i].Left - 48 ] = 1;
		if( In[i].Right >= '0' && In[i].Right <= '9' ) Check[In[i].Right - 48] = 1;
		while ((gc = getchar()) != '\n');
	}
	int root;
	for (int i = 0; i < N; i++) {
		if (!Check[i]) {
			root = i;
			break;
		}
	}
	
	BinTree T = NULL;
	T = BuildTree(T, In, root);
	int* Leaf = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) Leaf[i] = -1;
	Queue Q = CreateQ();
	CheckLeaf(T, Q, Leaf);
	if (Leaf[0] != -1) {
		printf("%d", Leaf[0]);
		for (int i = 1; i < N; i++) {
			if (Leaf[i] != -1) {
				printf(" %d", Leaf[i]);
			}
		}
	}
	return 0;
}