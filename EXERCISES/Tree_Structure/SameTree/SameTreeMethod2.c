/*
	1.第一种思路：生成两棵二叉树，再进行比较
				  (1)生成二叉树；
				  (2)对比二叉树； 
	2.第二种思路：是否存在规律，可以直接进行判断？
				  (1)找到根节点,比较根节点; 
				  (2)将数组分为左子树和右子树；
				  (3)递归比较; 
				  和第一种区别不大。
	3.第三种思路：只用一棵树，设置flag，通过查找过程中若经过没经过过的节点，说明不是同一棵树 
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
	int flag; 
}; 
typedef PtrToTNode SearchTree;

SearchTree Add( SearchTree T, ElementType X );
bool Compare( SearchTree T1, ElementType X );
void DeleteTree( SearchTree T );
void ResetTree( SearchTree T1 );

int main(int agc,const char* agv[])
{
	int i,N=1,L,tmp;
	SearchTree T1=NULL;
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
			int flag = 1;
			for(j=0;j<N;j++){
				scanf(" %d", &tmp );
				if ( flag == 1 && Compare( T1, tmp ) == 0 ) flag = 0;
			}
			if ( flag ) printf("Yes\n");
			else printf("No\n");
			ResetTree(T1);
		}
		DeleteTree(T1);
		T1 = NULL;
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
		T->flag = 0;
	} else {
		if ( X < T->Node ) {
			T->Left = Add( T->Left, X );
		} else if ( X > T->Node ){
			T->Right = Add( T->Right, X );
		}
	}
	return T;
}

bool Compare( SearchTree T1, ElementType X )
{
	bool flag ;
	if ( X == T1->Node ){
		T1->flag = 1;
		flag = true;
	}else if ( T1->flag == 1){
		if ( X > T1->Node ) {
			flag = Compare( T1->Right, X );
		} else {
			flag = Compare( T1->Left, X );
		}
	}else if ( T1->flag == 0 && T1->Node != X ){
		flag = false;
	}
	return flag;
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

void ResetTree( SearchTree T1 )
{
	if (!T1){
		return;
	}else{
		if ( T1->flag ){
			T1->flag = 0;
			ResetTree( T1->Left );
			ResetTree( T1->Right );
		} else {
			return;
		}
	}	
}
