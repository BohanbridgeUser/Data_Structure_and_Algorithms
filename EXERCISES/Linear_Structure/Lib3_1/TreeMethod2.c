/*
	1.静态链表接收数据
	2.在静态链表中进行遍历 
	3.对比同构 
*/ 


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXTree 10
#define ElementType char
#define Tree int
//静态链表接收input
#define Null -1
typedef struct SL* PtrToSL;
struct SL{
	ElementType Node;
	Tree Left;
	Tree Right;
} T1[MAXTree],T2[MAXTree]; 
//

Tree BuildTree( struct SL* );
bool Isomorphic( Tree R1, Tree R2);


int main(int agc,const char* agv[])
{
	Tree R1, R2;
	R1 = BuildTree(T1);
	R2 = BuildTree(T2);
	if ( Isomorphic( R1, R2 ) ) printf("Yes");
	else printf("No");
	return 0;
}

Tree BuildTree( struct SL T[])
{
	int N,i;
	scanf("%d",&N);
	int Mark[N];
	for(i=0;i<N;i++) Mark[i] = 0;
	int root;
	if ( N ) {
		char cl, cr;
		for(i=0;i<N;i++){
			scanf(" %c %c %c",&T[i].Node,&cl,&cr);
			if ( cl == '-' ) T[i].Left = Null;
			else T[i].Left = cl - '0', Mark[T[i].Left] = 1;
			if ( cr == '-' ) T[i].Right = Null;
			else T[i].Right = cr - '0', Mark[T[i].Right] = 1;	
		}
		for(i=0;i<N;i++) {
			if ( !Mark[i] ) {
				root = i;
				break;
			}
		}	
	} else {
		root = -1;
	}
	return root;
}

bool Isomorphic( Tree R1, Tree R2 )
{
	if ( R1 == Null && R2 == Null) return true;
	if ( R1 == Null && R2 != Null || R1 != Null && R2 == Null ) return false;
	if ( T1[R1].Node != T2[R2].Node ) return false;
	if ( T1[R1].Left == Null && T2[R2].Left == Null ) return Isomorphic( T1[R1].Right, T2[R2].Right );
	if ( T1[R1].Left != Null && T2[R2].Left != Null && T1[T1[R1].Left].Node == T2[T2[R2].Left].Node) 
		return Isomorphic( T1[R1].Left, T2[R2].Left )
				&& Isomorphic( T1[R1].Right, T2[R2].Right );
	else return Isomorphic( T1[R1].Left, T2[R2].Right )
				&& Isomorphic( T1[R1].Right, T2[R2].Left );
}
