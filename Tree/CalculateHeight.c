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

int CalculateHeight( BinTree T )
{
	int HL, HR;
	if ( T ){
		HL = CalculateHeight( T->Left ) + 1;
		HR = CalculateHeight( T->Right ) + 1;
		return HL > HR ? HL:HR;
	}else {
		return 0;
	}
}
int main(int agc,const char* agv[])
{
	BinTree T = CreateT(1);
	T->Left = CreateT(2);
	T->Right = CreateT(3);
	T->Left->Left = CreateT(4);
	T->Left->Left->Left = CreateT(5);
	T->Left->Left->Left->Left = CreateT(6);
	printf("%d\n",CalculateHeight( T ));
	return 0;
}

