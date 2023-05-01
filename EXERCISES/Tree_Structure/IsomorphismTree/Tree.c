/*
	1.静态链表接收数据
	2.导入链表表示的BinaryTree，然后遍历
	3.对比同构 
*/ 


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//树的数据结构 
typedef char ElementType;
typedef struct TreeNode* Position;
typedef Position BinTree;
struct TreeNode{
	ElementType Data;
	BinTree Left;
	BinTree Right;
};
//

//静态链表接收input
#define Null -1
typedef struct SL* PtrToSL;
struct SL{
	char Node;
	int Left;
	int Right;
}; 
//

//堆栈
typedef BinTree ElementType2;
typedef struct Stack* PtrToSNode;
struct SNode{
	ElementType2 Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;
// 

BinTree Add( struct SL T[], int node );
void PrintTraversal( BinTree Tree );//Check The Tree
bool CompareBinTree( BinTree Tree1, BinTree Tree2 );

int main(int agc,const char* agv[])
{
	int i;
	//input
	int N1;
	scanf("%d",&N1);
	struct SL T1[N1];
	int Mark1[N1];
	if ( N1 ){
		for(i=0;i<N1;i++) Mark1[i] = 0;
		for(i=0;i<N1;i++){
			char cl, cr;
			scanf(" %c %c %c",&T1[i].Node,&cl,&cr);
			if ( cl == '-' ) {
				T1[i].Left = Null;
			} else {
				T1[i].Left = cl - '0';
				Mark1[T1[i].Left] = 1; 
			} 
			if ( cr == '-' ) {
				T1[i].Right = Null;
			} else {
				T1[i].Right = cr - '0';
				Mark1[T1[i].Right ] = 1; 
			}
		}
	} 	

	int N2;
	scanf("%d",&N2);
	struct SL T2[N2];
	int Mark2[N2];
	if (N2){	
		for(i=0;i<N2;i++) Mark2[i] = 0;
		for(i=0;i<N2;i++){
			char cl, cr;
			scanf(" %c %c %c",&T2[i].Node,&cl,&cr);
			if ( cl == '-' ) {
				T2[i].Left = Null;
			} else {
				T2[i].Left = cl - '0';
				Mark2[T2[i].Left ] = 1 ; 
			} 
			if ( cr == '-' ) {
				T2[i].Right = Null;
			} else {
				T2[i].Right = cr - '0';
				Mark2[T2[i].Right ] = 1 ; 
			}
		}
	}
		
	//
	
	//method 1
	int root;
	BinTree Tree1,Tree2;
	if (N1){
		for(i=0;i<N1;i++) {
			if( !Mark1[i] ) {
				root = i;
				break;
			}
		}
		Tree1 = Add( T1, root );
	} else {
		Tree1 = NULL;
	}
		 
	if(N2){
		for(i=0;i<N2;i++) {
			if( !Mark2[i] ) {
				root = i;
				break;
			}
		}
		Tree2 = Add( T2, root );
	}else {
		Tree2 = NULL;
	}
		
	//
	
	//method 2
	
	
	//
	
	//output
	if( Tree1 && Tree2 ){
		if( CompareBinTree( Tree1, Tree2 ) ){
			printf("Yes");
		}else {
			printf("No");
		}
	}else if ( !Tree1 && !Tree2 ){
		printf("Yes");
	}else {
		printf("No");
	}	
	//
	return 0;
}

BinTree Add( struct SL T[], int node )
{
	//Create node
	BinTree Tree = (BinTree)malloc(sizeof(struct TreeNode));
	Tree->Data = T[node].Node;
	Tree->Left = NULL;
	Tree->Right = NULL;
	//
	
	//Add Left Right
	if ( T[node].Left != Null ) {
		Tree->Left = Add( T, T[node].Left ); 
	}
	if ( T[node].Right != Null ){
		Tree->Right = Add( T, T[node].Right ); 
	}
	//
	
	return Tree; 
}

//检查树是否输入正确 
void PrintTraversal( BinTree Tree )
{
	if ( Tree ) {
		printf("%c\n",Tree->Data);
		PrintTraversal( Tree->Left );
		PrintTraversal( Tree->Right);
	}
}
//

bool CompareBinTree( BinTree Tree1, BinTree Tree2 )
{
	//首先检查本层节点
	if ( Tree1->Data != Tree2->Data ) return false;
	// 
	
	//检查下一层节点
	if( Tree1->Left && Tree1->Right && Tree2->Left && Tree2->Right ){
		if( Tree1->Left->Data == Tree2->Left->Data && Tree1->Right->Data == Tree2->Right->Data ){
			if( CompareBinTree( Tree1->Left, Tree2->Left ) && CompareBinTree( Tree1->Right, Tree2->Right )) {
				return true;
			} else {
				return false;
			}
		} else if ( Tree1->Left->Data == Tree2->Right->Data && Tree1->Right->Data == Tree2->Left->Data ) {
			if( CompareBinTree( Tree1->Left, Tree2->Right ) && CompareBinTree( Tree1->Right, Tree2->Left ) ) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}		
	}else if ( !Tree1->Left && Tree1->Right && !Tree2->Left && Tree2->Right ){
		if( Tree1->Right->Data == Tree2->Right->Data ){
			if( CompareBinTree( Tree1->Right, Tree2->Right ) ) {
				return true;
			} else {
				return false;
			}
		}
	}else if ( !Tree1->Left && Tree1->Right && Tree2->Left && !Tree2->Right ) {
		if( Tree1->Right->Data == Tree2->Left->Data ){
			if( CompareBinTree( Tree1->Right, Tree2->Left ) ) {
				return true;
			} else {
				return false;
			}
		}
	}else if ( Tree1->Left && !Tree1->Right && !Tree2->Left && Tree2->Right ) {
		if( Tree1->Left->Data == Tree2->Right->Data ){
			if( CompareBinTree( Tree1->Left, Tree2->Right ) ) {
				return true;
			} else {
				return false;
			}
		}
	}else if ( Tree1->Left && !Tree1->Right && Tree2->Left && !Tree2->Right ) {
		if( Tree1->Left->Data == Tree2->Left->Data ){
			if( CompareBinTree( Tree1->Left, Tree2->Left ) ) {
				return true;
			} else {
				return false;
			}
		}
	}else if ( !Tree1->Left && !Tree1->Right && !Tree2->Left && !Tree2->Right ) {
		if ( Tree1->Data == Tree2->Data ){
			return true;
		}
	}else if ( Tree1->Left && Tree1->Right && Tree2->Left && !Tree2->Right ) {
		return false;
	}else if ( Tree1->Left && Tree1->Right && !Tree2->Left && Tree2->Right ) {
		return false;
	}else if ( !Tree1->Left && Tree1->Right && Tree2->Left && Tree2->Right ) {
		return false;
	}else if ( Tree1->Left && !Tree1->Right && Tree2->Left && Tree2->Right ) {
		return false;
	}
	//
}
