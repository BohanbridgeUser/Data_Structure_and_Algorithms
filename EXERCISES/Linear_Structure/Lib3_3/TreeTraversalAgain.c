#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
/*
	1.Input接收：用一个字符串和一个整形变量接收 
*/

typedef int ElementType;

//Binary Tree
	//动态链表二叉树（不方便寻找上一个节点） 
	typedef struct TNode* PtrToTNode;
	struct TNode{
		ElementType Node;
		PtrToTNode Left;
		PtrToTNode Right;
	};
	typedef PtrToTNode BinTree;
	// 
	
	//静态链表二叉树(存在问题，
	//当回到上一层时有可能本层已经pop过
	//此时较麻烦确定到底回到哪一层） 
	#define MAXSIZE 30
	struct BNode{
		ElementType Node;
		ElementType Left;
		ElementType Right;
	}B[MAXSIZE];
	// 

void InorderBuild( BinTree T, int* i, int N );
void InorderTraversal( BinTree T );
void PostorderTraversal( BinTree T, int Output[], int* i );
int StrToNum( char num[] );

int main(int agc,const char* agv[])
{
	int N;
	scanf("%d",&N);
	int i=0,tag=0;
	BinTree T = (BinTree)malloc(sizeof(struct TNode));
	InorderBuild(T, &i, 2*N);
	BinTree tmp = T;
	T=T->Left;
	free(tmp);
//	InorderTraversal(T);
 	int Output[N];
 	i=0;
	PostorderTraversal(T,Output,&i);
	for(i=0;i<N;i++) {
		if ( i != N - 1 ){
			printf("%d ",Output[i]);
		}else{
			printf("%d",Output[i]);
		}
	}
	//
	return 0;
}

void InorderBuild( BinTree T, int* i, int N )
{
	char str[10],num[10];
	int ret=0;
	//Left
	scanf(" %[a-zA-Z]%[^\n]",str,num);
	*i+=1;
	if ( !memcmp(str,"Push",4) ){
		BinTree P = (BinTree)malloc(sizeof(struct TNode));
		T->Left = P;
		P->Node = StrToNum(num);
		InorderBuild( P, i, N );
	}
	//
	
	//Right
	if ( *i >= N ) return;
	scanf(" %[a-zA-Z]%[^\n]",str,num);
	*i+=1;
	if ( !memcmp(str,"Push",4) ){
		BinTree P = (BinTree)malloc(sizeof(struct TNode));
		T->Right = P;
		P->Node = StrToNum(num);
		InorderBuild( P, i, N );
	} else {
		return;
	}
	//
}

void InorderTraversal( BinTree T )
{
	if ( T ){
		InorderTraversal( T->Left );
		printf("%d\n", T->Node);
		InorderTraversal(T->Right);
	}
	return;
}

void PostorderTraversal( BinTree T, int Output[], int* i )
{
	if ( T ){
		PostorderTraversal( T->Left, Output, i );
		PostorderTraversal(T->Right, Output, i );
		Output[*i] = T->Node;
		*i+=1;
	}
	return;
}

int StrToNum( char num[] )
{
	int len = strlen(num);
	int n=0,j=1;
	for(len-=1;len>0;len--){
		n += (num[len] - '0') * j;
		j*=10;	
	}
	return n;
}
