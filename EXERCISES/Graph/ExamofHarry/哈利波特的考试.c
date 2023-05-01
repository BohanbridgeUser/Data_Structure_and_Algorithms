#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INFINITY 65535
#define MaxVertexNum 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/* MGraph */
typedef struct MGNode* MGraph;
struct MGNode{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
};
/* Edge */
typedef struct ENode* Edge;
struct ENode{
	Vertex V1,V2;
	WeightType Weight;
};

MGraph CreateMG( Vertex VertexNum )
{
	MGraph Graph = (MGraph)malloc(sizeof(struct MGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	Vertex V;
	for(V=0;V<VertexNum;V++){
		Vertex W;
		for(W=0;W<VertexNum;W++) {
			if ( V != W ) Graph->G[V][W] = INFINITY;
			else Graph->G[V][W] = 0;
		}
	}
	return Graph;
}
void InsertEdge( MGraph Graph, Edge E )
{
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight;
}

///* LGraph */
///* Edge */
//typedef struct ENode* Edge;
//struct ENode{
//	Vertex V1,V2;
//	WeightType Weight;
//};
//
///* LGraph */
//typedef struct AdjNode* PtrToAdjNode;
//struct AdjNode{
//	Vertex AdjV;
//	WeightType Weight;
//	PtrToAdjNode Next;
//}; 
//
//typedef struct VNode* AdjList;
//struct VNode{
//	PtrToAdjNode FirstEdge;
//};
//
//typedef struct GNode* LGraph;
//struct GNode{
//	int Nv;
//	int Ne;
//	AdjList G;
//};
//
//LGraph CreateLG( Vertex VertexNum )
//{
//	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
//	Graph->Nv = VertexNum;
//	Graph->G = (AdjList)malloc(MaxVertexNum*sizeof(struct VNode));
//	
//	int i;
//	for(i=0;i<MaxVertexNum;i++) Graph->G[i].FirstEdge = NULL;
//	return Graph;
//}
//void InsertEdge( LGraph Graph, Edge E )
//{
//	PtrToAdjNode NewNode = (PtrToAdjNode)malloc(sizeof(struct VNode));
//	NewNode->AdjV = E->V2;
//	NewNode->Weight = E->Weight;
//	NewNode->Next = NULL;
//	NewNode->Next = Graph->G[E->V1].FirstEdge;
//	Graph->G[E->V1].FirstEdge = NewNode;
//	
//	NewNode = (PtrToAdjNode)malloc(sizeof(struct VNode));
//	NewNode->AdjV = E->V1;
//	NewNode->Weight = E->Weight;
//	NewNode->Next = NULL;
//	NewNode->Next = Graph->G[E->V2].FirstEdge;
//	Graph->G[E->V2].FirstEdge = NewNode; 
//}

MGraph BuildMGraph()
{
	int N, M;
	scanf("%d %d",&N,&M);
	MGraph Graph = CreateMG( N );
	
	if( !M ) return Graph;
	Graph->Ne = M;
	int i;
	for(i=0;i<M;i++){
		Vertex V1,V2,Weight;
		Edge E = (Edge)malloc(sizeof(struct ENode));
		scanf(" %d %d %d",&V1,&V2,&Weight);
		E->V1 = V1-1;
		E->V2 = V2-1;
		E->Weight = Weight;
		InsertEdge ( Graph, E );
	}
	return Graph;
}

typedef int Distance;
Distance* InitialDist( MGraph Graph, Vertex V, Distance* dist )
{
	int W;
	for(W=0;W<Graph->Nv;W++){
		if ( Graph->G[V][W] < INFINITY  ) dist[W] = Graph->G[V][W]; 
		else dist[W] = INFINITY;
	}
	return dist;
}

Vertex* InitialPath( MGraph Graph, Vertex V, Vertex* path )
{
	int W;
	for(W=0;W<Graph->Nv;W++){
		if( Graph->G[V][W] < INFINITY ) path[W] = V;
		else path[W] = -1;
	}
	return path;
}

Vertex Alternative( MGraph Graph, Distance* dist, bool* collected )
{
	Distance MinDist = INFINITY;
	Vertex MinV, V;
	
	for(V=0;V<Graph->Nv;V++){
		if( collected[V] == false && dist[V] < MinDist ) {
			MinDist = dist[V];
			MinV = V;
		}
	}
	if ( MinDist < INFINITY ){
		return MinV;
	}else{
		return -1;
	}
}

int SingleSource( MGraph Graph, Distance* dist, Vertex* path, Vertex V )
{
	bool collected[Graph->Nv];
	dist = InitialDist( Graph, V, dist );
	path = InitialPath( Graph, V, path );
	collected[V] = true;
	int i;
	for(i=0;i<Graph->Nv;i++) if( i!= V )collected[i] = false;
	while( 1 ){
		Vertex W = Alternative( Graph, dist, collected );
		if ( W == -1 )
			break;
		collected[W] = true;
		Vertex S;
		for(S=0;S<Graph->Nv;S++){
			if( collected[S] == false && Graph->G[W][S] <INFINITY ){
				if( Graph->G[W][S] < 0)
				 	return false;
				if( dist[W] + Graph->G[W][S] < dist[S] ){
					dist[S] = dist[W] + Graph->G[W][S];
					path[S] = W;
				}
			}
		}
	}
	Distance MaxDist=0;
	for(V=0;V<Graph->Nv;V++){
		if( dist[V] > dist[MaxDist] && dist[V] != INFINITY ) MaxDist = V;
		else if( dist[V] == INFINITY ) return -1;
	}
	return dist[MaxDist];
}

int main(int agc,const char* agv[])
{
	MGraph Graph = BuildMGraph();
	Vertex path[MaxVertexNum];
	Distance dist[MaxVertexNum];
	Distance MaxDistance=INFINITY, MaxDNv;
	int i,TEMP;
	for(i=0;i<Graph->Nv;i++){
		TEMP = SingleSource( Graph, dist, path, i);
		if ( TEMP < MaxDistance ){
			MaxDistance = TEMP;
			MaxDNv = i;
			
		}else if( TEMP == -1 ){
			printf("0");
			return 0;
		}
	}
	printf("%d %d",MaxDNv+1, MaxDistance);
	return 0;
}

