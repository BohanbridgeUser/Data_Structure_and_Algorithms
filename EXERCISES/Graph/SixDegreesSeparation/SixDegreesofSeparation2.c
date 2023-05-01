#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxVertexNum 1001
typedef int Vertex;
typedef int WeightType;
/* Edge */
typedef struct ENode* PtrToENode;
struct ENode{
	Vertex v1,v2;
	WeightType Weight;
};
typedef PtrToENode Edge;
/* AdjVNode */
typedef struct AVNode* PtrToAdjVNode;
struct AVNode{
	Vertex V;
	WeightType Weight;
	PtrToAdjVNode Next;
};
typedef PtrToAdjVNode VNode;
/* Head Node */
typedef struct VNode{
	PtrToAdjVNode FirstEdge;
}AdjVNode[MaxVertexNum]; 
/* LGraph */
typedef struct GNode* PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	AdjVNode G;
};
typedef PtrToGNode LGraph;

LGraph CreateLG( Vertex VertexNum )
{
	LGraph Graph = (LGraph)malloc(sizeof( struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	Vertex V;
	for(V=0;V<Graph->Nv;V++){
		Graph->G[V].FirstEdge = NULL;
	}
	return Graph;
}
void InsertEdge( LGraph Graph, Edge E )
{
	VNode NewNode = (VNode)malloc(sizeof( struct AVNode ));
	NewNode->V = E->v2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->v1].FirstEdge;
	Graph->G[E->v1].FirstEdge = NewNode;
	
	NewNode = (VNode)malloc(sizeof( struct AVNode ));
	NewNode->V = E->v1;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->v2].FirstEdge;
	Graph->G[E->v2].FirstEdge = NewNode;
}
LGraph BuildLG()
{
	LGraph Graph;
	Edge E;
	int Nv, i;
	
	scanf("%d",&Nv);
	Graph = CreateLG( Nv );
	scanf("%d",&Graph->Ne);
	if( Graph->Ne ){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i=0;i<Graph->Ne;i++){
			int V, W;
			scanf(" %d %d",&V,&W);
			E->v1 = V - 1;
			E->v2 = W - 1;
			E->Weight = 1;
			InsertEdge( Graph, E );
		}
	}
	return Graph;
}

/* Queue */
#define MAXQUEUE 1000
#define ElementType Vertex
typedef struct Node* PtrToNode;
struct Node{
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;
typedef struct QNode* Queue;
struct QNode{
	Position Head;
	Position Rear;
	int MAX;
};

Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Head = NULL;
	Q->Rear = NULL;
	Q->MAX = MAXQUEUE;
	return Q;
} 
bool IsFull( Queue Q )
{
	Position P = Q->Head;
	int cnt=0;
	for(P;P;P=P->Next) cnt++;
	if ( cnt == Q-> MAX ) return true;
	else return false;
}
Queue AddQ( Queue Q, ElementType X )
{
	if ( IsFull( Q ) ) return Q;
	PtrToNode NewNode = (PtrToNode)malloc(sizeof(struct Node));
	NewNode->Data = X;
	NewNode->Next = NULL;
	if( Q->Head == NULL ){
		Q->Head = NewNode;
		Q->Rear = NewNode;
	}else{
		Q->Rear->Next = NewNode;
		Q->Rear = Q->Rear->Next; 
	}
	return Q;
}
bool IsEmpty( Queue Q )
{
	if ( Q->Head == NULL ){
		return true;
	}else{
		return false;
	}
}
ElementType DeleteQ( Queue Q )
{
	if ( IsEmpty( Q ) ) {
		return ;
	}
	ElementType Ret = Q->Head->Data;
	PtrToNode temp = Q->Head;
	Q->Head = Q->Head->Next;
	if ( Q->Head == NULL ) Q->Rear = NULL;
	free( temp );
	return Ret;
}

/* BFS */
Vertex visit[MaxVertexNum];
void InitialVisit()
{
	int i;
	for(i=0;i<MaxVertexNum;i++){
		visit[i] = false;
	}
}
int BFS( LGraph Graph, Vertex S )
{
	int count=0, now = 0, last = S, level = 0 , tail;
	visit[S] = true;
	Queue Q = CreateQ();
	Q = AddQ( Q, S );
	count++;
	
	while( !IsEmpty( Q ) ){
		Vertex V = DeleteQ( Q );
		Vertex W;
		VNode Node = Graph->G[V].FirstEdge;
		for(Node;Node;Node=Node->Next){
			W = Node->V;
			if( visit[W] == false ){
				visit[W] = true;
				Q = AddQ( Q , W );
				count++;
				tail = W;
			}
		}
		if ( last == V ){
			level++; last = tail;
		}
		if ( level == 6 ) break;
	}
	return count;
}
void SDS( LGraph Graph )
{
	Vertex V;
	int count;
	for(V=0;V<Graph->Nv;V++){
		count = BFS( Graph, V );
		InitialVisit();
		printf("%d: %.2lf%%\n",V+1,count*1.0/Graph->Nv*100);
	}
}

int main(int agc,const char* agv[])
{
	LGraph Graph = BuildLG();
	SDS( Graph );
	return 0;
}

