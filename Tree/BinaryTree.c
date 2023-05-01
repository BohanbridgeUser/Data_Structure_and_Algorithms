#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define ElementType int

typedef struct TNode* Position;
typedef Position BinTree;
struct TNode{
	ElementType Data;
	BinTree Left;
	BinTree Right;
};
BinTree CreateT( ElementType X )
{
	BinTree T = (BinTree)malloc(sizeof(struct TNode));
	T->Data = X;
	T->Left = NULL;
	T->Right = NULL;
	return T;
}
bool IsEmpty( BinTree T )
{
	if( !T ) return true;
	else return false;
}
void InorderTraversal( BinTree T )
{
	if ( T ){
		InorderTraversal( T->Left );
		printf("%d ",T->Data);
		InorderTraversal( T->Right );
	}else return;
}
void PreorderTraversal( BinTree T )
{
	if ( T ){
		printf("%d ",T->Data);
		PreorderTraversal( T->Left );
		PreorderTraversal( T->Right );
	}else return;
}
void PostorderTraversal( BinTree T )
{
	if ( T ){
		PostorderTraversal( T->Left );
		PostorderTraversal( T->Right );
		printf("%d ",T->Data);
	}else return;
}

/* Stack */
#define ElementTypeofStack Position
typedef struct SNode* PtrToSNode;
typedef PtrToSNode Stack;
struct SNode{
	ElementTypeofStack Data;
	PtrToSNode Next;
};

Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
Stack Push ( Stack S, ElementTypeofStack X )
{
	PtrToSNode TEMP = (PtrToSNode)malloc(sizeof( struct SNode));
	TEMP->Data = X;
	TEMP->Next = S->Next;
	S->Next = TEMP;
	return S;
}
bool IsEmptyS( Stack S )
{
	if ( !S->Next ) {
		printf("EMPTY\n");
		return true;
	}
	else return false; 
}
ElementTypeofStack Pop( Stack S )
{
	ElementTypeofStack RET;
	if ( IsEmptyS( S ) ) return NULL;
	else{
		RET = S->Next->Data;
		Stack temp = S->Next;
		S->Next = S->Next->Next;
		free(temp);
		return RET;
	}
}

/* Nonrecursion Traversal */
void NonInorderTraversal( BinTree T )
{
	Stack S = CreateS();
	Position P = T;
	while( P || !IsEmptyS( S ) ){
		while( P ){
			S = Push( S, P );
			P = P->Left;
		}
		P = Pop( S );
		printf("%d ",P->Data);
		P = P->Right;
	}	
}
void NonPreorderTraversal( BinTree T )
{
	Stack S = CreateS();
	Position P = T;
	while( P || !IsEmptyS( S ) ){
		while( P ){
			printf("%d ",P->Data);
			S = Push( S, P );
			P = P->Left;
		}
		P = Pop( S );
		P = P->Right;
	}
}
void NonPostorderTraversal( BinTree T )
{
	Stack S = CreateS();
	Position P = T;
	while( P || !IsEmptyS( S ) ){
		while( P ){
			S = Push( S, P );
			P = P->Left;
		}
		P = Pop( S );
		while ( P && P->Data == 65535 ) {
			P = Pop(S); 
			printf("%d ",P->Data);
			if ( !IsEmptyS( S )) P = Pop(S);
			else return;
		}
		Position Flag = (Position)malloc(sizeof(struct TNode));
		Flag->Data = 65535;
		S = Push( S, P ) ;
		S = Push( S, Flag );
		P = P->Right;
	}
}

/* Queue */
#define ElementTypeofQueue Position
#define MAXQUE 100
typedef struct QNode* PtrToQNode;
struct QNode{
	ElementTypeofQueue Data;
	PtrToQNode Next;
};
struct Que{
	PtrToQNode Head;
	PtrToQNode Rear;
	int Maxsize;
};
typedef struct Que* Queue;

Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct Que));
	Q->Head = NULL;
	Q->Rear = NULL;
	Q->Maxsize = MAXQUE;
	return Q;
}
bool IsFullQ( Queue Q )
{
	int cnt=0;
	PtrToQNode TEMP = Q->Head;
	for(;TEMP;TEMP=TEMP->Next) cnt++;
	if (cnt == Q->Maxsize) return true;
	else return false;
}
Queue AddQ( Queue Q, ElementTypeofQueue X )
{
	if ( !IsFullQ( Q ) ){
		if ( !Q -> Head ){
			PtrToQNode P = (PtrToQNode)malloc(sizeof(struct QNode));
			P->Data = X;
			P->Next = NULL;
			Q->Head = P;
			Q->Rear = P;
			return Q;
		}else{
			PtrToQNode P = (PtrToQNode)malloc(sizeof(struct QNode));
			P->Data = X;
			P->Next = NULL;
			Q->Rear->Next = P;
			Q->Rear = Q->Rear->Next;
			return Q;
		}
	}else{
		return Q;
	}
}
bool IsEmptyQ( Queue Q )
{
	if ( !Q->Head ) {
		return true;
	}
	else return false;
}
ElementTypeofQueue DeleteQ( Queue Q )
{
	ElementTypeofQueue RET;
	if ( !IsEmptyQ(Q) ){
		RET = Q->Head->Data;
		PtrToQNode TEMP = Q->Head;
		if ( !Q->Head->Next ) Q->Head = NULL, Q->Rear = NULL;
		else Q->Head = Q->Head->Next;
		free( TEMP );
		return RET;
	}else return NULL;
}
void LevelorderTraversal( BinTree T )
{
	if (!T) return; 
	Queue Q = CreateQ();
	Q = AddQ( Q, T );
	while( !IsEmptyQ(Q) ){
		BinTree P = DeleteQ(Q);
		printf("%d ",P->Data);
		if ( P->Left ) Q = AddQ( Q, P->Left );
		if ( P->Right )	Q = AddQ( Q, P->Right );
	}
}
int main(int agc,const char* agv[])
{
	BinTree T = CreateT(1);
	T->Left = CreateT(2);
	T->Right = CreateT(3);
	T->Left->Left = CreateT(4);
	T->Left->Right = CreateT(5);
	T->Right->Left = CreateT(6);
	T->Right->Right = CreateT(7);
	LevelorderTraversal( T );
	return 0;
}

