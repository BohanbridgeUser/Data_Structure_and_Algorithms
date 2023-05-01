#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxVertexNum 1000
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

MGraph CreateMG( Vertex VertexNum )
{
	MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	int V;
	for(V=0;V<VertexNum;V++){
		int W;
		for(W=0;W<VertexNum;W++){
			if( V!= W ) Graph->G[V][W] = INFINITY;
			else Graph->G[V][W] = 1; 
		}
	}
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
	Vertex V, W;
	int Nv, Ne, i;
	
	scanf("%d",&Nv);
	Graph = CreateMG(Nv);
	scanf(" %d",&Graph->Ne);
	if( Graph->Ne ) {
		E = (Edge)malloc(sizeof(struct ENode));
		for(i=0;i<Graph->Ne;i++){
			scanf(" %d %d",&V,&W);
			E->v1 = V - 1;
			E->v2 = W - 1;
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
int CountNode( MGraph Graph, Vertex V )
{
	int i, cnt=0;
	for(i=0;i<Graph->Nv;i++){
		if ( visit[i] ) cnt++;
	}
	return cnt;
}
void DFS ( MGraph Graph, Vertex X, int Count )
{
	Count++;
	visit[X] = true;
	Vertex V, W;

	for(W=0;W<Graph->Nv;W++){
		if ( Count <= 6 && visit[W] == false && Graph->G[X][W] == 1 ){
			DFS ( Graph, W, Count );
		}
	}
}
void CalResult( MGraph Graph )
{
	Vertex V;
	for(V=0;V<Graph->Nv;V++){
		DFS( Graph, V, 0 );
		double Out = CountNode( Graph, V );
		printf("%d: %.2lf%\n",V+1,Out*1.0/Graph->Nv*100.0);
		InitialVisit();
	}
}

int main(int agc,const char* agv[])
{
	MGraph Graph = BuildMG();
	CalResult( Graph );
	return 0;
}

