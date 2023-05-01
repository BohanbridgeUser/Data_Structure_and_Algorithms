#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct DNode* PtrToDNode;
struct DNode{
	char* Data;
};

typedef PtrToDNode Element;
typedef struct TNode* BinTree;
struct TNode{
	Element Data;
	double Num;
	double Perc;
	BinTree Left;
	BinTree Right;
};

BinTree AddT( BinTree T , Element X, int N )
{
	if( !T ){
		T = (BinTree)malloc(sizeof(struct TNode));
		T->Data = X;
		T->Num = 1;
		T->Perc = 1.0 / N;
		T->Left = NULL;
		T->Right = NULL;
	}else{
		if ( strcmp( T->Data->Data, X->Data ) > 0 ) T->Left = AddT( T->Left, X, N);
		else if ( strcmp( T->Data->Data, X->Data ) < 0) T->Right = AddT( T->Right, X, N);
		else {
			T->Num++;
			T->Perc = T->Num / N;
		}
	}
	return T;
}

void InorderTraversal( BinTree T )
{
	if ( T ){
		InorderTraversal( T->Left );
		printf("%s %.4lf%%\n",T->Data->Data,100 * T->Perc);
		InorderTraversal( T->Right );
		return;
	}else{
		return;
	}
}
int main(int agc,const char* agv[])
{
	int N;
	scanf("%d",&N);
	char c;
	while( (c = getchar()) !='\n');
	
	BinTree T = NULL;
	int i;
	for(i=0;i<N;i++){
		char* Input = (char*)malloc(100*sizeof(char));
		scanf("%[^\n]",Input);
		while( (c = getchar()) != '\n');
		
		PtrToDNode D = (PtrToDNode)malloc(sizeof(struct DNode));
		D->Data = Input;
		T = AddT( T, D, N );
	}
	InorderTraversal( T );
	return 0;
}

