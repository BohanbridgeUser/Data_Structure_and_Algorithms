#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;
typedef struct SNode* PtrToSNode;
struct SNode{
	ElementType* Data;
	int Size;
	int Top;
};
typedef PtrToSNode Stack;

Stack CreateS( int N )
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType*)malloc(N*sizeof(ElementType));
	S->Size = N;
	S->Top = -1;
	return S;
}
bool IsFullS( Stack S )
{
	if ( S->Top + 1 == S->Size ) return true;
	else return false;
}
void Push( Stack S, ElementType X )
{
	if ( !IsFullS(S) ){
		S->Data[++S->Top] = X;
	}
}
ElementType Peek( Stack S )
{
	ElementType RET = S->Data[S->Top];
	return RET;
}
ElementType Pop( Stack S )
{
	ElementType RET = S->Data[S->Top--];
	return RET;
}
int main(int agc,const char* agv[])
{
	int M, N, K;
	scanf("%d %d %d",&M, &N, &K);
	int i;
	for(i=0;i<K;i++){
		int* Input = (int*)malloc(N*sizeof(int));
		int j;
		for(j=0;j<N;j++) scanf("%d",&Input[j]);
		int E[N];
		for(j=0;j<N;j++) E[j] = j+1;
		Stack S = CreateS(M);
		int k,cnt=0,l;
		for(j=0;j<N;j++){
			for(k=0;k<Input[j];k++){
				if( E[k] ){
					if ( !IsFullS(S) ){
						Push( S, E[k] );
						E[k] = 0; 
					}else{
						cnt = 1;
						break;
					}		
				}
			}
			if ( cnt == 1 ) break;
			l = Pop(S);
			if ( l != Input[j] ) {
				cnt = 1;
				break;
			}
		}
		
		if ( cnt == 1 ) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}

