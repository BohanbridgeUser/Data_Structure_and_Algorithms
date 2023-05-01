#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INFINITY 65535
#define MavVertexNum 1000

typedef int Vertex;
typedef int WeightType;

/* Edge */
typedef struct ENode* Edge;
struct ENode{
	Vertex V1, V2;
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
	Graph->G = (AdjList)malloc( Graph->Nv * sizeof(struct VNode) );
	
	int i;
	for(i=0;i<Graph->Nv;i++) Graph->G[i].FirstEdge = NULL;
	
	return Graph;
}
void EdgeInsert( LGraph Graph, Edge E )
{
	PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->V2 = E->V2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->V2 = E->V1;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}
LGraph BuildLG( int N, int M )
{
	LGraph Graph = CreateLG( N );
	if( !M ) return Graph;
	else{
		int i;
		Edge E = (Edge)malloc(sizeof(struct ENode));
		for(i=0;i<M;i++){
			int v1, v2;
			scanf(" %d %d %d", &v1, &v2, &E->Weight);
			E->V1 = v1 - 1;
			E->V2 = v2 - 1;
			EdgeInsert( Graph, E );
			Graph->Ne++;
		}
		return Graph;
	}
}
Vertex* InitialMST( Vertex* MST, Vertex S, int Len )
{
	int i;
	for(i=0;i<Len;i++) {
		if( i != S ) MST[i] = -2;
		else MST[i] = -1;
	}
	return MST;
}
int* InitialDist( LGraph Graph, Vertex S, int* Dist )
{
	int i;
	for(i=0;i<Graph->Nv;i++) {
		if ( i!= S ) Dist[i] = INFINITY;
		else Dist[i] = 0;
	}
	PtrToAdjVNode TEMP;
	for(TEMP = Graph->G[S].FirstEdge;TEMP;TEMP=TEMP->Next){
		Dist[TEMP->V2] = TEMP->Weight;
	}	
	return Dist;
}
int FindV( int* Dist, LGraph Graph )
{
	int i, Min = INFINITY, RET = -1;
	for(i=0;i<Graph->Nv;i++){
		if ( Dist[i] < Min && Dist[i] > 0 ){
			Min = Dist[i];
			RET = i;
		}
	}
	return RET;
}
void Prim( LGraph Graph , Vertex S ) 
{
	Vertex* MST = ( Vertex* )malloc( Graph->Nv * sizeof( Vertex ) );
	MST = InitialMST( MST, S, Graph->Nv );
	int* Dist = ( int* )malloc( Graph->Nv * sizeof(int) );
	Dist = InitialDist( Graph, S, Dist);
	int Parent[Graph->Nv];
	Parent[S] = -1;
	int MinValue = 0, cnt = 0 ;
	while(1){
		Vertex V = FindV( Dist, Graph );
		if ( V == -1 ) break;
		else cnt++;
		MinValue += Dist[V];
		Dist[V] = 0;
		PtrToAdjVNode TEMP;
		for(TEMP=Graph->G[V].FirstEdge;TEMP;TEMP=TEMP->Next){
			if( Dist[TEMP->V2] != 0 ){
				if( TEMP->Weight < Dist[TEMP->V2] ){
					Dist[TEMP->V2] = TEMP->Weight;
					MST[TEMP->V2] = V;
				}
			}	
		}
	}
	if( cnt != Graph->Nv - 1  ) printf("-1\n");
	printf("%d",MinValue);
}

int main(int agc,const char* agv[])
{
	int N, M;
	scanf("%d %d",&N,&M);
	LGraph Graph = BuildLG( N, M );
	Prim( Graph, 0 );
	return 0;
}

