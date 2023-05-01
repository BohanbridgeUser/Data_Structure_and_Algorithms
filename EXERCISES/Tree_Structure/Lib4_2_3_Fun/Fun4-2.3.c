#include<stdio.h>
#include<stdlib.h> 

typedef enum { false, true } bool;

typedef char ElementType;

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag;
};

/*------��ջ�Ķ���-------*/
typedef Position SElementType;
typedef struct SNode *PtrToSNode;
struct SNode {
    SElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

/* ����ʵ�֣�ϸ�ڲ��� */
Stack CreateStack();
bool IsEmpty( Stack S );
bool Push( Stack S, SElementType X );
SElementType Pop( Stack S ); /* ɾ����������S��ջ��Ԫ�� */
SElementType Peek( Stack S );/* ������S��ջ��Ԫ�� */
/*----��ջ�Ķ������-----*/

BinTree CreateBinTree(); /* ����ʵ�֣�ϸ�ڲ��� */
void InorderTraversal( BinTree BT )
{
	Stack S = CreateStack();
	Push( S, BT );
	BinTree T = BT->Left;
	while( !IsEmpty(S) ){
		while( T ){
			Push( S, T );
			T = T->Left;
		}
		T = Pop( S );
		printf(" %c",T->Data);
		T = T->Right;
	}
}
void PreorderTraversal( BinTree BT )
{
	Stack S = CreateStack();
	printf(" %c",BT->Data);
	Push( S, BT );
	BinTree T = BT->Left;
	while( !IsEmpty(S) ){
		while( T ){
			printf(" %c",T->Data);
			Push( S, T );
			T = T->Left;
		}
		T = Pop( S );
		T = T->Right;
	}
}
void PostorderTraversal( BinTree BT )
{
	Stack S = CreateStack();
	Push( S, BT );
	BinTree T = BT->Left;
	while( !IsEmpty(S) ){
		while( T ){
			Push( S, T );
			T = T->Left;
		}
		T = Peek( S );
		if ( T->flag == 0 ) {
			T->flag = 1;
			T = T->Right;
		}else if ( T->flag == 1 ){
			printf(" %c",T->Data);
			T = Pop(S);
			T = Pop(S);
			T = T->Right;
		}	
	}
}

int main(int agc,const char* agv[])
{

	return 0;
}
void InorderTraversal( BinTree BT )
{
	if ( BT ) {
		Stack S = CreateStack();
		BinTree T = BT;
		while( T || !IsEmpty(S) ){
			while( T ){
				Push( S, T );
				T = T->Left;
			}
			T = Pop( S );
			printf(" %c",T->Data);
			T = T->Right;
		}
	}	
}
void PreorderTraversal( BinTree BT )
{
	if ( BT ) {
		Stack S = CreateStack();
		BinTree T = BT;
		while( T || !IsEmpty(S) ){
			while( T ){
				printf(" %c",T->Data);
				Push( S, T );
				T = T->Left;
			}
			T = Pop( S );
			T = T->Right;
		}
	}	
}
void PostorderTraversal( BinTree BT )
{
	if( BT ){
		Stack S = CreateStack();
		BinTree T = BT;
		while( T || !IsEmpty(S) ){
			while( T && T->flag ==0 ){
				Push( S, T );
				T = T->Left;
			}
			T = Peek( S );
			if ( T->flag == 0 ) {
				T->flag = 1;
				T = T->Right;
			}else if ( T->flag == 1 ){
				printf(" %c",T->Data);
				T = Pop(S);
				if( IsEmpty(S) ) return;
			}
		}
	}	
}
