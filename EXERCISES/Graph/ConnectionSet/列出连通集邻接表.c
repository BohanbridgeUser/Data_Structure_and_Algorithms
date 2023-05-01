#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>

#define MaxVertexNum 11
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
/* Edge */
typedef struct ENode* PtrToENode;
typedef PtrToENode Edge;
struct ENode{
	Vertex v1,v2;
	WeightType Weight;
};
/* AdjVNode */
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV;
	WeightType Weight;
	PtrToAdjVNode Next;
};
/* LGraph */
typedef struct VNode{
	PtrToAdjVNode FirstEdge;
}AdjList[MaxVertexNum];
typedef struct GNode* PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateLG( int VertexNum )
{
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	int i;
	for(i=0;i<Graph->Nv;i++) Graph->G[i].FirstEdge = NULL;
	return Graph;
}
void InsertEdge( LGraph Graph, Edge E )
{
	PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->v2;
	NewNode->Weight = E->Weight;
	PtrToAdjVNode P = Graph->G[E->v1].FirstEdge;
	if ( P ){
		if ( P->AdjV > NewNode->AdjV ){
			NewNode->Next = P;
			Graph->G[E->v1].FirstEdge = NewNode;
		}else{
			while( P->Next && P->Next->AdjV < NewNode->AdjV ){
				P = P->Next;
			}
			NewNode->Next = P->Next;
			P->Next = NewNode;
		}	
	}else{
		NewNode->Next = Graph->G[E->v1].FirstEdge;
		Graph->G[E->v1].FirstEdge = NewNode;
	}
	
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->v1;
	NewNode->Weight = E->Weight;
	P = Graph->G[E->v2].FirstEdge;
	if ( P ){
		if ( P->AdjV > NewNode->AdjV ){
			NewNode->Next = P;
			Graph->G[E->v2].FirstEdge = NewNode;
		}else{
			while( P->Next && P->Next->AdjV < NewNode->AdjV ){
				P = P->Next;
			}
			NewNode->Next = P->Next;
			P->Next = NewNode;
		}	
	}else{
		NewNode->Next = Graph->G[E->v2].FirstEdge;
		Graph->G[E->v2].FirstEdge = NewNode;
	}
}
LGraph BuildLG()
{
	Vertex V;
	LGraph Graph;
	Edge E;
	int Nv, Ne, i;
	
	scanf("%d %d",&Nv,&Ne);
	Graph = CreateLG( Nv );
	Graph->Ne = Ne;
	if( Graph->Ne ){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i=0;i<Graph->Ne;i++){
			scanf(" %d %d",&E->v1,&E->v2);
			E->Weight = 1;
			InsertEdge( Graph, E );
		}
	}
	return Graph;
}

/* DFS Operation */
Vertex visit[MaxVertexNum];
void InitialVisit()
{
	int i;
	for(i=0;i<MaxVertexNum;i++){
		visit[i] = false;
	}
}
void DFS( LGraph Graph, Vertex V )
{
	printf("%d ",V);
	visit[V] = true;
	PtrToAdjVNode P = Graph->G[V].FirstEdge;
	for(P;P;P=P->Next){
		if ( visit[P->AdjV] == false ){
			DFS( Graph, P->AdjV );
		}
	}
}
void DFSTraversal( LGraph Graph )
{
	Vertex V;
	for(V=0;V<Graph->Nv;V++){
		if ( visit[V] == false ){
			printf("{ ");
			DFS( Graph, V );
			printf("}\n");
		}
	}
}

/* BFS Operation */
#define MAXSIZE 100
typedef struct QNode* PtrToQNode;
struct QNode{
	PtrToAdjVNode AdjV;
	PtrToQNode Next;
};
struct Que{
	PtrToQNode Head;
	PtrToQNode Rear;
	int MAX;
};
typedef struct Que* Queue;

Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct Que));
	PtrToQNode P = (PtrToQNode)malloc(sizeof(struct QNode));
	P->Next = NULL;
	Q->Head = P;
	Q->Rear = P;
	Q->MAX = MAXSIZE;
	return Q;
}
bool IsEmpty( Queue Q )
{
	if ( Q->Head == Q->Rear ){
		return true;
	}else{
		return false;
	}
}
bool IsFull( Queue Q )
{
	PtrToQNode P = Q->Head;
	int cnt=0;
	for(P;P;P=P->Next) cnt++;
	if ( cnt == Q->MAX ) return true;
	else return false;
}
void AddQ( Queue Q, PtrToAdjVNode V )
{
	if ( !IsFull(Q) ){
		PtrToQNode P = (PtrToQNode)malloc(sizeof(struct QNode));
		P->AdjV = V;
		P->Next = NULL;
		Q->Rear->Next = P;
		Q->Rear = Q->Rear->Next; 
	}else{
		return;
	}
}
PtrToAdjVNode DeleteQ( Queue Q )
{
	PtrToAdjVNode RET;
	if ( !IsEmpty( Q ) ){
		RET = Q->Head->Next->AdjV;
		Q->Head->Next = Q->Head->Next->Next;
		if ( Q->Head->Next == NULL ){
			Q->Rear = Q->Head;
		}
		return RET;
	}else{
		return NULL;
	}
}
void BFS( LGraph Graph, Vertex S )
{
	printf("%d ",S);
	visit[S] = true;
	Queue Q = CreateQ();
	AddQ( Q, Graph->G[S].FirstEdge );
	
	while( !IsEmpty( Q ) ){
		PtrToAdjVNode V = DeleteQ( Q );
		Vertex W;
		for(V;V;V=V->Next){
			if ( visit[V->AdjV] == false ){
				visit[V->AdjV] = true;
				printf("%d ",V->AdjV);
				AddQ(Q, Graph->G[V->AdjV].FirstEdge);
			}
		}	
	}
}
void BFSTraversal( LGraph Graph )
{
	Vertex W;
	for(W=0;W<Graph->Nv;W++){
		if ( visit[W] == false ){
			printf("{ ");
			BFS(Graph,W);
			printf("}\n");
		}
	}
}

int main(int agc,const char* agv[])
{
	LGraph Graph = BuildLG();
	DFSTraversal( Graph );
	InitialVisit();
	BFSTraversal( Graph );
	return 0;
}

