#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxVertexNum 11 
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;

/* Edge */
typedef struct ENode* PtrToENode;
struct ENode{
	Vertex v1,v2;
	WeightType Weight;
};
typedef PtrToENode Edge;

/* MGraph */
typedef struct GNode* PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

/* Graph Operation */
MGraph CreateMG( int Vertex );
void InsertEdge( MGraph Graph, Edge E );
MGraph BuildMG();

MGraph CreateMG( int VertexNum )
{
	MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	Vertex V, W;
	for(V=0;V<VertexNum;V++)
		for(W=0;W<VertexNum;W++)
			if( V == W ) Graph->G[V][W] = 1;
			else Graph->G[V][W] = INFINITY;
	return Graph;
}
void InsertEdge( MGraph Graph, Edge E )
{
	Graph->G[E->v1][E->v2] = E->Weight;
	Graph->G[E->v2][E->v1] = E->Weight;
}
MGraph BuildMG()
{
	MGraph Graph;
	Edge E;
	int Nv, Ne, i;
	
	scanf("%d %d",&Nv,&Ne);
	if( Nv ){
		Graph = CreateMG( Nv );
		Graph->Ne = Ne;
		E = (Edge)malloc(sizeof( struct ENode));
		for(i=0;i<Graph->Ne;i++){
			scanf(" %d %d",&E->v1,&E->v2);
			E->Weight = 1;
			InsertEdge( Graph, E );
		}		
	}
	return Graph;
}

/* DFS Operation */
bool visit[MaxVertexNum];
void InitialVisit()
{
	int i;
	for(i=0;i<MaxVertexNum;i++){
		visit[i] = false;
	}
}

void DFS( MGraph Graph, Vertex V )
{
	visit[V] = true;
	printf("%d ",V);
	int i;
	for(i=0;i<Graph->Nv;i++){
		if ( Graph->G[V][i] == 1 && visit[i] == false ){
			DFS( Graph, i );
		}
	}
}

void DFSTraversal( MGraph Graph )
{
	int j;
	for(j=0;j<Graph->Nv;j++){
		if( visit[j] == false ){
			printf("{ ");
			DFS( Graph, j );
			printf("}\n");
		}
	}
}

/* BFS Operation 
   1.Queue
   2.BFS
   3.Travelsal
*/
// 1.Queue
#define MAXSIZE 11
typedef struct QNode* PtrToQNode;
struct QNode{
	Vertex V;
	PtrToQNode Next;
};
typedef struct Que* Queue;
struct Que{
	PtrToQNode Head;
	PtrToQNode Rear;
	int MAX;
};

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
bool IsFull( Queue Q )
{
	PtrToQNode P = Q->Head;
	int cnt=0;
	for(;P;P=P->Next) cnt++;
	return cnt == Q->MAX? true:false;
}
Queue AddQ( Queue Q, Vertex V )
{
	if ( !IsFull(Q) ){
		PtrToQNode P = (PtrToQNode)malloc(sizeof(struct QNode));
		P->V = V;
		Q->Rear->Next = P;
		Q->Rear = Q->Rear->Next;
		return Q;
	}else{
		return NULL;
	}
}
bool IsEmpty( Queue Q )
{
	if( Q->Head == Q->Rear ){
		return true;
	}else{
		return false;
	}
}
int DeleteQ( Queue Q )
{
	int RET;
	if ( !IsEmpty( Q ) ){
		RET = Q->Head->Next->V;
		PtrToQNode p = Q->Head->Next;
		Q->Head->Next = Q->Head->Next->Next;
		if( Q->Rear == p ){
			Q->Rear = Q->Head;
		}
		free(p);
		return RET;
	}else{
		return;
	}
}
// 2.BFS
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
	return Graph->G[V][W] == 1? true:false;
}
void BFS( MGraph Graph, Vertex S )
{
	Vertex V, W;
	Queue Q = CreateQ();
	visit[S] = true;
	printf("%d ",S);
	AddQ( Q, S );
	
	while( !IsEmpty(Q) ){
		V = DeleteQ( Q );
		for(W=0;W<Graph->Nv;W++){
			if( visit[W] == false && IsEdge( Graph, V, W ) == true ){
				visit[W] = true;
				printf("%d ",W);
				AddQ( Q, W );
			}
		}
	}
}
void BFSTraversal( MGraph Graph )
{
	Vertex V;
	for(V=0;V<Graph->Nv;V++){
		if ( !visit[V] ){
			printf("{ ");
			BFS( Graph, V );
			printf("}\n");
		}
	}
}


int main(int agc,const char* agv[])
{
	MGraph Graph = BuildMG();
	DFSTraversal( Graph );
	InitialVisit();
	BFSTraversal( Graph );
	return 0;
}
