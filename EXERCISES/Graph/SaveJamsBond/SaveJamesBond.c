#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define MaxVertexNum 101
typedef int Vertex;
typedef double WeightType;

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
	Vertex G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

/* MGraph Operation */
MGraph CreateMG( Vertex VertexNum )
{
	MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	Vertex V, W;
	for(V=0;V<VertexNum;V++){
		for(W=0;W<VertexNum;W++){
			if ( V != W ) Graph->G[V][W] = 0;
			else Graph->G[V][W] = 1; 
		}
	}
	return Graph;
}
void InsertEdge( MGraph Graph, Edge E )
{
	Graph->G[E->v1][E->v2] = E->Weight;
	Graph->G[E->v2][E->v1] = E->Weight;
	Graph->Ne++;
}

/* Input Data */
typedef struct LocNode* Loc; 
struct LocNode{
	int X;
	int Y;
};
Loc Input( int N )
{
	Loc input = (Loc)malloc(N*sizeof(struct LocNode));
	int i;
	for(i=0;i<N;i++){
		scanf(" %d %d",&input[i].X,&input[i].Y);
	}
	return input;
}

/* Build Edge */
bool IsInR( struct LocNode i, struct LocNode j, double D )
{
	double Dis;
	Dis = sqrt( pow(i.X-j.X,2) + pow(i.Y-j.Y,2) );
	if ( Dis <= D ) return true;
	else return false;
}
MGraph BuildGraph( MGraph Graph, Loc L, double D )
{
	int i,j;
	Edge E = (Edge)malloc(sizeof(struct ENode));
	for(i=0;i<Graph->Nv;i++){
		for(j=i+1;j<Graph->Nv;j++){
			if ( IsInR( L[i], L[j], D ) ) {
				E->v1 = i;
				E->v2 = j;
				E->Weight = 1;
				InsertEdge( Graph, E );
			}
		}
	}
	return Graph;
}

/* DFS Operation Check Path */
bool IsInO( struct LocNode i, double D )
{
	double Dis;
	Dis = sqrt( pow(i.X,2) + pow(i.Y,2) );
	if ( Dis <= D + 15.0 / 2 ) return true;
	else return false;
}
bool IsInE( struct LocNode i, double D )
{
	if ( 50 - fabs(i.X) <= D ) return true;
	else if ( 50 - fabs(i.Y) <= D ) return true;
	else return false;
}
Vertex visit[MaxVertexNum];
void Initialvisit()
{
	int i;
	for(i=0;i<MaxVertexNum;i++){
		visit[i] = false;
	}
}
bool DFS( MGraph Graph, Loc L, Vertex V, double D )
{
	visit[V] = true;
	if ( IsInE( L[V], D ) ) return true;
	else {
		int W;
		for(W=0;W<Graph->Nv;W++){
			if ( Graph->G[V][W] == 1 && visit[W] == false ){
				bool ret;
				ret = DFS( Graph, L, W, D );
				if ( ret ) return true;
			}
		}
		return false;
	}
}
bool Check( MGraph Graph, Loc L, double D )
{
	int i;
	for(i=0;i<Graph->Nv;i++){
		if( IsInO( L[i], D ) && visit[i] == false ){
			if( DFS( Graph, L, i, D ) ) return true;
		}
	}
	return false;
}

int main(int agc,const char* agv[])
{
	int N;
	double D;
	scanf("%d %lf",&N,&D);
	Loc L = Input( N );
	MGraph Graph = CreateMG( N );
	Graph = BuildGraph( Graph, L, D );
	if( Check( Graph, L, D) ) printf("Yes\n");
	else printf("No\n");
	return 0;
}

