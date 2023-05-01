#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxVertexNum 500
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;

/* Edge */
typedef struct ENode* Edge;
struct ENode{
	Vertex V1, V2;
	WeightType Length, Toll;
};

/* AdjVNode */
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode{
	Vertex V2;
	WeightType Length, Toll;
	PtrToAdjVNode Next;
};
/* FirstEdge */
typedef struct VNode* AdjList;
struct VNode{
	PtrToAdjVNode FirstEdge;
};
/* LGNode */
typedef struct GNode* LGraph;
struct GNode{
	int Nv;
	int Ne;
	AdjList G;
};
/* LGFunction */
LGraph CreateLG( Vertex VertexNum )
{
	LGraph Graph = (LGraph)malloc(sizeof( struct GNode ) );
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	Graph->G = (AdjList)malloc( Graph->Nv * sizeof( struct VNode ) );
	
	Vertex V;
	for(V=0;V<Graph->Nv;V++) Graph->G[V].FirstEdge = NULL;
	return Graph;
}
void EdgeInsert( LGraph Graph, Edge E )
{
	PtrToAdjVNode NewNode = ( PtrToAdjVNode )malloc(sizeof( struct AdjVNode ) );
	NewNode->V2 = E->V2;
	NewNode->Length = E->Length;
	NewNode->Toll = E->Toll;
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	
	NewNode = ( PtrToAdjVNode )malloc(sizeof( struct AdjVNode ) );
	NewNode->V2 = E->V1;
	NewNode->Length = E->Length;
	NewNode->Toll = E->Toll;
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}
LGraph BuildLG( Vertex N, int M )
{
	if ( !M ) {
		printf("NO Edge\n");
		return NULL;
	}else{
		LGraph Graph = CreateLG( N );
		Edge E = (Edge)malloc(sizeof( struct ENode ) );
		int i;
		for(i=0;i<M;i++){
			scanf(" %d %d %d %d", &E->V1, &E->V2, &E->Length, &E->Toll);
			EdgeInsert( Graph, E );
		}
		return Graph;	
	}
}

/* Distance */
void InitialDist( LGraph Graph, int* Dist, Vertex S )
{
	int i;
	for(i=0;i<Graph->Nv;i++) Dist[i] = INFINITY;
	PtrToAdjVNode TEMP;
	TEMP = Graph->G[S].FirstEdge;
	Dist[S] = 0;
	for(TEMP;TEMP;TEMP = TEMP->Next ){
		Dist[TEMP->V2] = TEMP->Length;
	}
}
/* Path */
void InitialPath( LGraph Graph, int* Path )
{
	int i;
	for(i=0;i<Graph->Nv;i++){
		Path[i] = -1;
	} 
}
/* Cost */
void InitialCost( LGraph Graph, int* Cost, Vertex S )
{
	int i;
	for(i=0;i<Graph->Nv;i++) Cost[i] = INFINITY;
	PtrToAdjVNode TEMP;
	TEMP = Graph->G[S].FirstEdge;
	Cost[S] = 0;
	for(TEMP;TEMP;TEMP = TEMP->Next ){
		Cost[TEMP->V2] = TEMP->Toll;
	}
}

Vertex FindMinDist( LGraph Graph, int* Dist, bool* Collect )
{
	Vertex MinV;
	int MinDist = INFINITY;
	int i;
	for(i=0;i<Graph->Nv;i++){
		if ( Collect[i] == false && Dist[i] < MinDist ){
			MinDist = Dist[i];
			MinV = i;
		}
	}
	if ( MinDist == INFINITY ) return -1;
	else return MinV;
}
void Dijkstra( LGraph Graph, int* Dist, int* Cost, int* Path, Vertex S )
{	
	bool Collect[MaxVertexNum];
	int i;
	for(i=0;i<Graph->Nv;i++) Collect[i] = false;
	InitialDist( Graph, Dist, S );
	InitialPath( Graph, Path );
	InitialCost( Graph, Cost, S );
	Collect[S] = true;
	int cnt =0;
	while(1){
		Vertex V = FindMinDist( Graph, Dist, Collect );
		Collect[V] = true;
		if ( V == -1 ) break;
		PtrToAdjVNode TEMP = Graph->G[V].FirstEdge;
		for(TEMP;TEMP;TEMP=TEMP->Next){
			if( Collect[TEMP->V2] == false && Dist[V] + TEMP->Length < Dist[TEMP->V2]){
				Dist[TEMP->V2] = Dist[V] + TEMP->Length;
				Path[TEMP->V2] = V;
				Cost[TEMP->V2] = Cost[V] + TEMP->Toll;
			}else if ( Collect[TEMP->V2] == false && Dist[V] + TEMP->Length == Dist[TEMP->V2] ){
				if ( Cost[V] + TEMP->Toll < Cost[TEMP->V2] ){
					Path[TEMP->V2] = V;
					Cost[TEMP->V2] = Cost[V] + TEMP->Toll;
				}
			}
		}
		
	}
	
}
int main(int agc,const char* agv[])
{
	int N, M, S, D;
	scanf("%d %d %d %d", &N, &M, &S, &D);
	LGraph Graph = BuildLG( N, M );
	int Dist[Graph->Nv], Cost[Graph->Nv], Path[Graph->Nv];
	Dijkstra( Graph, Dist, Cost, Path, S );
	printf("%d %d",Dist[D],Cost[D]);
	return 0;
}

