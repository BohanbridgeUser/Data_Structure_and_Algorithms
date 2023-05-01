/*
	1.��һ��˼·���������ö��������ٽ��бȽ�
				  (1)���ɶ�������
				  (2)�Աȶ������� 
	2.�ڶ���˼·���Ƿ���ڹ��ɣ�����ֱ�ӽ����жϣ�
				  (1)�ҵ����ڵ�,�Ƚϸ��ڵ�; 
				  (2)�������Ϊ����������������
				  (3)�ݹ�Ƚ�; 
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int ElementType;
typedef struct TNode* PtrToTNode;
struct TNode{
	ElementType Node;
	PtrToTNode Left;
	PtrToTNode Right;
}; 
typedef PtrToTNode SearchTree;

SearchTree Add( SearchTree T, ElementType X );
bool Compare( SearchTree T1, SearchTree T2 );
void DeleteTree( SearchTree T );
void InorderTraversal( SearchTree T );

int main(int agc,const char* agv[])
{
	int i,N=1,L,tmp;
	SearchTree T1=NULL,T2=NULL;
	while ( N ){
		scanf(" %d",&N);
		if ( N == 0 ) break;
		scanf(" %d",&L);
		for(i=0;i<N;i++){
			scanf(" %d", &tmp );
			T1 = Add( T1, tmp );
		}
		for(i=0;i<L;i++){
			int j;
			for(j=0;j<N;j++){
				scanf(" %d", &tmp );
				T2 = Add( T2, tmp );
			}
			if ( Compare(T1, T2) == 1 ){
				printf("Yes\n");
			} else {
				printf("No\n");
			}
			DeleteTree(T2);
			T2 = NULL;
		}
	}
	
	
	return 0;
}

SearchTree Add( SearchTree T, ElementType X )
{
	if ( !T ) {
		T = (SearchTree)malloc(sizeof(struct TNode));
		T->Node = X;
		T->Left = NULL;
		T->Right = NULL;
	} else {
		if ( X < T->Node ) {
			T->Left = Add( T->Left, X );
		} else if ( X > T->Node ){
			T->Right = Add( T->Right, X );
		}
	}
	return T;
}

bool Compare( SearchTree T1, SearchTree T2 )
{
	if( !T1 && T2 ){
		return false;
	}else if ( T1 && !T2 ){
		return false;
	}else if ( !T1 && !T2){
		return true;
	}else if ( T1 && T2 && T1->Node != T2->Node ){
		return false;
	}else if ( T1 && T2 && T1->Node == T2->Node){
		bool ret1 = true;
		bool ret2 = Compare( T1->Left , T2->Left );
		bool ret3 = Compare( T1->Right , T2->Right );
		bool ret = ret1&ret2&ret3;
		return ret;
	}
}

void DeleteTree( SearchTree T )
{
	if ( T ){
		DeleteTree( T->Left );
		DeleteTree( T->Right );
		free(T);
		return;
	}else{
		return;
	}
	
}

void InorderTraversal( SearchTree T )
{
	if ( T ) {
		InorderTraversal( T->Left );
		InorderTraversal( T->Right );
	} else {
		return;
	}
}
