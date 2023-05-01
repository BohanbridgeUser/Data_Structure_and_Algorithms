/* 
	1.建立带有平衡因子的二叉搜索树； 
	2.插入节点，计算二叉搜索树的平衡因子； 
	3.调整二叉搜索树。 
	如何寻找需要调整的节点——采用循环队列，每次保存插入节点和上两层的祖先节点，当插入完成后check平衡因子，根据相对关系判定旋转方式 
	已写完队列 
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 

//Tree 
typedef struct TNode* PtrToTree;
struct TNode{
	int Node;
	PtrToTree Left,Right;
	int BF;
};
typedef PtrToTree Tree; 
//

//Stack
typedef Tree ElementType;
typedef struct SNode* PtrToSNode;
struct SNode{
	ElementType Node;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;
Stack Create();
Stack Push( Stack S, ElementType  X );
ElementType Pop( Stack S );
bool IsEmptyStack( Stack S );
void DeleteStack( Stack S );
//

Tree Add( Tree T, int X );
Tree AdjustTree( Tree T, int X, Stack S );
PtrToTree Search( Tree T, int X, Stack S );
bool Check( Tree T );
Tree RRRotation( Tree R );
Tree LLRotation( Tree R );
Tree LRRotation( Tree R );
Tree RLRotation( Tree R );
int Height( Tree T );
void CalBF( Tree T );

void InorderTraversal(Tree T)
{
	if(T){
		printf("NODE=%d BF=%d\n",T->Node,T->BF);
		InorderTraversal(T->Left);
		InorderTraversal(T->Right);
	}
} 

int main(int agc,const char* agv[])
{
	int N,i;
	scanf("%d",&N);
	
	Tree T = NULL;
	for(i=0;i<N;i++){
		int j;
		Stack Q = Create();
		scanf(" %d",&j);
		T = Add( T, j );
		CalBF(T);
		T = AdjustTree( T, j, Q );
		DeleteStack(Q);
	}
	printf("%d",T->Node);
	
	
	return 0;
}

Tree Add( Tree T, int X )
{
	if ( !T ){
		T = (Tree)malloc(sizeof(struct TNode));
		T->Node = X;
		T->BF = 0;
		T->Left = NULL;
		T->Right = NULL;
	} else {
		if ( T->Node < X ){
			T->Right = Add( T->Right, X );
		} else if ( T->Node > X ){
			T->Left = Add( T->Left, X );
		}
	}
	return T;
}

Tree AdjustTree( Tree S, int X, Stack Q )
{
	Tree T;
	if ( Check(S) == false ) {
		T = Search( S, X, Q );
		Stack p = Q;
		Tree R = Pop(Q);
		//判断是哪一种旋转;
		if ( X > R->Node && X > R->Right->Node){
			R = RRRotation( R );
		}else if ( X < R->Node && X < R->Left->Node ){
			R = LLRotation( R );
		}else if ( X < R->Node && X > R->Left->Node ){
			R = LRRotation( R );
		}else if ( X > R->Node && X < R->Right->Node ){
			R = RLRotation( R );
		}
		CalBF(S);
	}
	return S;	 
}

Tree RRRotation( Tree R )
{
	int tmp;
	tmp = R->Node;
	R->Node = R->Right->Node;
	R->Right->Node = tmp;
	
	Tree temp = R->Left;
	R->Left = R->Right;
	R->Right = R->Right->Right;
	R->Left->Right = R->Left->Left;
	R->Left->Left = temp;
	return R;
}

Tree LLRotation( Tree R )
{
	int tmp;
	tmp = R->Node;
	R->Node = R->Left->Node;
	R->Left->Node = tmp;
	
	Tree temp = R->Right;
	R->Right = R->Left;
	R->Left = R->Left->Left;
	R->Right->Left = temp;
	return R;
}

Tree LRRotation( Tree R )
{
	int tmp;
	tmp = R->Node;
	R->Node = R->Left->Right->Node;
	R->Left->Right->Node = tmp;
	
	Tree temp = R->Right;
	R->Right = R->Left->Right;
	R->Left->Right = R->Left->Right->Left;
	R->Right->Left = R->Right->Right;
	R->Right->Right = temp;
	return R;
}

Tree RLRotation( Tree R )
{
	int tmp;
	tmp = R->Node;
	R->Node = R->Right->Left->Node;
	R->Right->Left->Node = tmp;
	
	Tree temp = R->Left;
	R->Left = R->Right->Left;
	R->Right->Left = R->Right->Left->Right;
	R->Left->Right = R->Left->Left;
	R->Left->Left = temp;
	return R;
}

PtrToTree Search( Tree T, int X, Stack Q )
{
	if ( !T ) {
		printf("FALL SEARCH\n");
		return T;
	}else{
		if ( T->BF > 1 || T->BF < -1 ){
			Q = Push( Q , T );	
		}	
	}
	if ( T->Node == X ){
		return T;
	} else {
		if ( X < T->Node ) {
			return Search( T->Left, X, Q );
		}else if ( X > T->Node ) {
			return Search( T->Right, X, Q );
		}
	}
}

bool Check( Tree T )
{
	bool ret1=true, ret2=true, ret3=true;
	if(T){
		if ( T->BF >= 2 || T->BF <= -2) ret1 = false;
		else ret1 = true;
		ret2 = Check(T->Left);
		ret3 = Check(T->Right);
	}
	return ret1&ret2&ret3;
}

int Height( Tree T )
{
	int hl,hr,h;
	if(T){
		hl = Height(T->Left);
		hr = Height(T->Right);
		if ( hl > hr ){
			h = hl + 1;
		}else {
			h = hr + 1;
		}
		return h;
	}else {
		return 0;
	}
}

void CalBF( Tree T )
{
	int hl,hr;
	if (T){
		hl = Height(T->Left);
		hr = Height(T->Right);
		T->BF = hl - hr;
		CalBF(T->Left);
		CalBF(T->Right);
	}else{
		return;
	}
}

Stack Create()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}

Stack Push( Stack S, ElementType X )
{
	PtrToSNode p = (PtrToSNode)malloc(sizeof(struct SNode));
	p->Node = X;
	p->Next = S->Next;
	S->Next = p;
	return S;
}

ElementType Pop( Stack S )
{
	if ( !IsEmptyStack(S) ){
		ElementType ret;
		ret = S->Next->Node;
		PtrToSNode temp;
		temp = S->Next;
		S->Next = S->Next->Next;
		free(temp);
		return ret;
	}else{
		printf("STACK EMPTY\n");
		return;
	}
}

bool IsEmptyStack( Stack S )
{
	if ( !S->Next ){
		return true;
	}else{
		return false;
	}
}

void DeleteStack( Stack S )
{
	if( S ){
		DeleteStack( S->Next );
		free(S);
		return;
	}else{
		return;
	}
}
