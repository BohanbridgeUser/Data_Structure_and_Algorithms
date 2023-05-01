#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxVertexNum 105
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;

/* Edge */
typedef struct ENode* Edge;
struct ENode{
	Vertex V1,V2;
	WeightType Weight;
};
/* AdjVNode */
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode{
	Vertex V2;
	WeightType Weight;
	PtrToAdjVNode Next;
};
/* VNode */
typedef struct VNode* AdjList;
struct VNode{
	PtrToAdjVNode FirstEdge;
	int Latest;
	int Earliest;
};
/* GNode */
typedef struct GNode* LGraph;
struct GNode{
	int Nv;
	int Ne;
	AdjList G;
};
LGraph CreateLG( Vertex VertexNum )
{
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	Graph->G = (AdjList)malloc( Graph->Nv * sizeof(struct AdjVNode) );
	
	int i;
	for(i=0;i<Graph->Nv;i++){
		Graph->G[i].FirstEdge = NULL;
	}
	return Graph;
}
void EdgeInsert( LGraph Graph, Edge E, int* Indegree )
{
	PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->V2 = E->V2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	Indegree[E->V2]++;
}
LGraph BuildLG( int N, int M, int* Indegree )
{
	LGraph Graph = CreateLG( N );
	if( !M ) return Graph;
	else {
		Edge E = (Edge)malloc(sizeof(struct ENode));
		int i;
		for(i=0;i<M;i++){
			int v1, v2;
			scanf(" %d %d %d",&v1,&v2,&E->Weight);
			E->V1 = v1 - 1;
			E->V2 = v2 - 1;
			EdgeInsert( Graph, E, Indegree );
		}
	}
	return Graph;
}

/* Queue */
#define ElementTypeofQueue int
typedef struct QNode* PtrToQNode;
struct QNode{
	ElementTypeofQueue Data;
	PtrToQNode Next;
};
typedef struct Que* Queue;
struct Que{
	PtrToQNode Head;
	PtrToQNode Rear;
};
Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct Que));
	Q->Head = NULL;
	Q->Rear = NULL;
	return Q;
}
bool IsEmptyQ( Queue Q )
{
	if( !Q->Head ) return true;
	else return false;
}
Queue AddQ( Queue Q, ElementTypeofQueue X )
{
	PtrToQNode NewNode = (PtrToQNode)malloc(sizeof(struct QNode));
	NewNode->Data = X;
	if( IsEmptyQ( Q ) ){
		Q->Head = NewNode;
		Q->Rear = NewNode;
	}else{
		Q->Rear->Next = NewNode;
		Q->Rear = Q->Rear->Next;
	}
	return Q;
}
ElementTypeofQueue DeleteQ( Queue Q )
{
	ElementTypeofQueue RET;
	if( IsEmptyQ(Q) ){
		return -1;
	}else{
		if( !Q->Head->Next ){
			PtrToQNode TEMP;
			TEMP = Q->Head;
			Q->Head = NULL;
			Q->Rear = NULL;
			RET = TEMP->Data;
			free(TEMP);
		}else{
			PtrToQNode TEMP;
			TEMP = Q->Head;
			Q->Head = Q->Head->Next;
			RET = TEMP->Data;
			free(TEMP);
		}
		return RET;
	}	
}

/* Stack */
#define ElementTypeofStack int
typedef struct SNode* Stack;
struct SNode{
	ElementTypeofStack Data;
	Stack Next;
};
Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
bool IsEmptyS( Stack S )
{
	if( !S->Next ) return true;
	else return false;
}
Stack Push( Stack S, ElementTypeofStack X )
{
	Stack NewNode = (Stack)malloc(sizeof(struct SNode));
	NewNode->Data = X;
	NewNode->Next = S->Next;
	S->Next = NewNode;
	return S;
}
ElementTypeofStack Pop( Stack S )
{
	if( !IsEmptyS(S) ){
		ElementTypeofStack RET = S->Next->Data;
		Stack TEMP = S->Next;
		S->Next = S->Next->Next;
		free(TEMP);
		return RET;
	}else{
		return -1;
	}	
}
/* TopSort */
void TopSort( LGraph Graph, int* Indegree )
{
	Queue Q = CreateQ();
	int i;
	for(i=0;i<Graph->Nv;i++){
		if( !Indegree[i] ){
			Q = AddQ( Q, i);
		}
	}
	int cnt = 0;
	Stack S = CreateS();
	while( !IsEmptyQ(Q) ){
		Vertex V = DeleteQ( Q );
		S = Push( S, V );
		cnt++;
		PtrToAdjVNode TEMP;
		for(TEMP=Graph->G[V].FirstEdge;TEMP;TEMP=TEMP->Next){
			if( Graph->G[V].Earliest + TEMP->Weight > Graph->G[TEMP->V2].Earliest ){
				Graph->G[TEMP->V2].Earliest = Graph->G[V].Earliest + TEMP->Weight;
			}
			if( --Indegree[TEMP->V2] == 0){
				Q = AddQ( Q, TEMP->V2 );
			}	
		}	
	}
	int max=0,j;
	if( cnt != Graph->Nv )
		printf("0\n");
	else {
		for(i=0;i<Graph->Nv;i++){
			PtrToAdjVNode TEMP;
			if( max < Graph->G[i].Earliest ) max = Graph->G[i].Earliest,j=i;
		}
		printf("%d\n",max);
	}
	for(i=0;i<Graph->Nv;i++){	
		Graph->G[i].Latest=max;	
	}
	while( !IsEmptyS(S) ){
		int V = Pop(S);
		PtrToAdjVNode TEMP;
		for(TEMP=Graph->G[V].FirstEdge;TEMP;TEMP=TEMP->Next){
			if( Graph->G[V].Latest > Graph->G[TEMP->V2].Latest - TEMP->Weight){
				Graph->G[V].Latest = Graph->G[TEMP->V2].Latest - TEMP->Weight;
			}
		}
	}
	for(i=0;i<Graph->Nv;i++){
		PtrToAdjVNode TEMP;
		for(TEMP=Graph->G[i].FirstEdge;TEMP;TEMP=TEMP->Next){
			if( Graph->G[TEMP->V2].Earliest == Graph->G[TEMP->V2].Latest && Graph->G[i].Earliest == Graph->G[i].Latest && Graph->G[i].Earliest + TEMP->Weight == Graph->G[TEMP->V2].Earliest){
				printf("%d->%d\n",i+1,TEMP->V2+1);
			}	
		}
	}
}
int main(int agc,const char* agv[])
{
	int N, M;
	scanf("%d %d",&N,&M);
	int* Indegree = (int*)malloc(N*sizeof(int));
	LGraph Graph = BuildLG( N, M, Indegree );
 	TopSort( Graph, Indegree );
	return 0;
}

