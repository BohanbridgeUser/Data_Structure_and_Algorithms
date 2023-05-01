#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;

/* Stack */
typedef struct SNode* PtrToSNode;
struct SNode{
	ElementType* Data;
	int Top;
	int Size;
};
typedef PtrToSNode Stack;

Stack CreateS( int N )
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType*)malloc(N*sizeof(ElementType));
	S->Top = -1;
	S->Size = N;
	return S;
}
int IsFullS( Stack S )
{
	if ( S->Top + 1 == S->Size ) return 1;
	else return 0;
}
void Push( Stack S, ElementType X )
{
	if ( !IsFullS(S) ) {
		S->Data[++S->Top] = X;
	}
}
int IsEmptyS( Stack S )
{
	if( S->Top == -1 ) return 1;
	else return false;
}
ElementType Pop( Stack S )
{
	if ( !IsEmptyS(S) ) {
		ElementType RET = S->Data[S->Top--];
		return RET;
	}else {
		return -1;
	}
}
ElementType Peek( Stack S )
{
	if ( !IsEmptyS(S) ) {
		ElementType RET = S->Data[S->Top];
		return RET;
	}else {
		return -1;
	}
}
/* Stack Define End */

/* Queue */
void AddQ( ElementType X, Stack S1, Stack S2 )
{
	if ( !IsFullS(S2) ) {
		Push( S2, X );
	}else if( IsFullS(S2) && !IsEmptyS(S1)){
		printf("ERROR:Full\n");
	}else if ( IsFullS(S2) && IsEmptyS(S1)){
		int i;
		for(i=0;i<S2->Size;i++){
			Push( S1, Pop(S2) );
		}
		Push( S2, X );
	}
}
ElementType DeleteQ( Stack S1, Stack S2 )
{
	ElementType RET;
	if( !IsEmptyS(S1) ){
		RET = Pop( S1 );
	}else if( IsEmptyS(S1) && !IsEmptyS( S2 )){
		int i;
		int j = S2->Top;
		for(i=0;i<=j;i++){
			Push( S1, Pop(S2) );
		}
		RET = Pop(S1);
	}else if( IsEmptyS(S1) && IsEmptyS(S1) ){
		printf("ERROR:Empty\n");
		return -1;
	}
	return RET;
}
/* Queue End */

int main(int agc,const char* agv[])
{
	int NS1, NS2;
	scanf("%d %d",&NS1,&NS2);
	if( NS1 < NS2 ){
		int tmp = NS1;
		NS1 = NS2;
		NS2 = tmp;
	}
	Stack S1 = CreateS( NS1 );
	Stack S2 = CreateS( NS2 );
	char CI;
	int NI;
	while( (scanf("%c",&CI)) == 1){
		if ( CI == 'A' ){
			scanf("%d",&NI);
			AddQ( NI, S1, S2 );
		}else if( CI == 'D' ){
			int x = DeleteQ( S1, S2 );
			if( x != -1 ) printf("%d\n",x);
		}else if( CI == 'T' ){
			break;
		}else{
			continue;
		}
		
	}
	return 0;
}

