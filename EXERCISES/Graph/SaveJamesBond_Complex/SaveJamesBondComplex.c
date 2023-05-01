#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define MaxVertexNum 100

typedef int Vertex;
typedef double WeightType;

/* Input */
typedef struct Input* In;
struct Input{
	int X;
	int Y;
};

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
/* Head VNode */
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

LGraph CreateLG( Vertex VertexNum )
{
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	Graph->G = (AdjList)malloc(MaxVertexNum*sizeof(struct VNode));
	
	Vertex V;
	for(V=0;V<MaxVertexNum;V++) Graph->G[V].FirstEdge = NULL;
	return Graph;
}
void EdgeInsert( LGraph Graph, Edge E )
{
	PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->V2 = E->V2;
	NewNode->Weight = E->Weight;
	PtrToAdjVNode TEMP = Graph->G[E->V1].FirstEdge;
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->V2 = E->V1;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
	Graph->Ne++;
}

double CalculateD( struct Input InputNode1, struct Input InputNode2 )
{
	double D = sqrt(pow( InputNode1.X - InputNode2.X, 2 )+pow( InputNode1.Y - InputNode2.Y, 2 ) );
	return D;
}

LGraph BuildLG( Vertex N, double D, In InputNode )
{
	LGraph Graph = CreateLG( N );
	int i;
	for(i=0;i<N;i++){
		int j;
		for(j=i+1;j<N;j++){
			double TEMPD = CalculateD( InputNode[i], InputNode[j] );
			if ( TEMPD <= D ){
				Edge E = (Edge)malloc(sizeof(struct ENode));
				E->V1 = i;
				E->V2 = j;
				E->Weight = TEMPD;
				EdgeInsert( Graph, E );
			}
		}
	}
	return Graph;
}

/* Queue */
typedef int ElementTypeofQueue;
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
	Queue Q = (Queue)malloc( sizeof( struct Que ) );
	Q->Head = NULL;
	Q->Rear = NULL;
	return Q;
}
bool IsEmpty( Queue Q )
{
	if ( !Q->Head ) return true;
	else return false;
}
Queue AddQ( Queue Q, ElementTypeofQueue X )
{
	if ( IsEmpty( Q ) ){
		Q->Head = (PtrToQNode)malloc( sizeof ( struct QNode ) );
		Q->Head->Data = X;
		Q->Rear = Q->Head;
	}else{
		PtrToQNode TEMP = (PtrToQNode)malloc( sizeof ( struct QNode ) );
		TEMP->Data = X;
		TEMP->Next = NULL;
		Q->Rear->Next = TEMP;
		Q->Rear = Q->Rear->Next;
	}
	return Q;
}
ElementTypeofQueue DeleteQ( Queue Q )
{
	ElementTypeofQueue TEMP = -1;
	if ( IsEmpty( Q ) ){
		printf("EMPTY\n");
		return -1;
	} else {
		TEMP = Q->Head->Data;
		PtrToQNode TMP = Q->Head;
		Q->Head = Q->Head->Next;
		if ( !Q->Head ) Q->Rear = NULL;
		return TEMP;
	}
}

/* Stack */
typedef int ElementTypeofStack;
typedef struct SNode* PtrToSNode;
struct SNode{
	ElementTypeofStack Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
bool IsEmptyS( Stack S )
{
	if ( !S->Next ) return true;
	else return false;
}
Stack Push( Stack S, ElementTypeofStack X )
{
	PtrToSNode NewSNode = (PtrToSNode)malloc(sizeof( struct SNode));
	NewSNode->Data = X;
	NewSNode->Next = S->Next;
	S->Next = NewSNode;
	return S;
}
ElementTypeofStack Pop( Stack S )
{
	if ( IsEmptyS(S) ){
		return;
	}else{
		ElementTypeofStack RET = S->Next->Data;
		PtrToSNode TEMP = S->Next;
		S->Next= S->Next->Next;
		free(TEMP);
		return RET;
	}
}
/* Shortest Path */
bool OriginJudge( In InputNode, Vertex S )
{
	struct Input Origin;
	Origin.X = 0;
	Origin.Y = 0;
	double TEMPD = CalculateD( InputNode[S], Origin );
	if ( TEMPD < 15 ) return true;
	else return false;
}
bool BankJudge( In InputNode, Vertex S, double D)
{
	if ( 50 - abs(InputNode[S].X) <= D || 50 - abs( InputNode[S].Y ) <= D ){
		return true;
	} else {
		return false;
	}
}
void InitialDist( LGraph Graph, In InputNode, double D, int* dist )
{
	int i;
	for(i=0;i<Graph->Nv;i++) dist[i] = -1;
}
void InitialPath( LGraph Graph, In InputNode, double D, int* path )
{
	int i;
	for(i=0;i<Graph->Nv;i++) path[i] = -1;
}
int SinglePath( LGraph Graph, In InputNode, double D, Vertex S, int* dist, int* path )
{
	InitialDist( Graph, InputNode, D, dist );
	InitialPath( Graph, InputNode, D, path );
	
	dist[S] = 0;
	path[S] = -2;
	Queue Q = CreateQ();
	Q = AddQ( Q, S );
	
	Vertex V;
	while( !IsEmpty( Q ) ){
		V = DeleteQ( Q );
		PtrToAdjVNode TEMP = Graph->G[V].FirstEdge;
		for(;TEMP;TEMP=TEMP->Next){
			if( dist[TEMP->V2] == -1 ){
				dist[TEMP->V2] = dist[V] + 1;
				path[TEMP->V2] = V;
				Q = AddQ( Q, TEMP->V2 );
			}
		}
	}
}
int FindMinDist( LGraph Graph, int* dist, In InputNode, double D )
{
	int min = 100;
	int i;
	for(i=0;i<Graph->Nv;i++){
		if ( BankJudge( InputNode, i, D ) && dist[i] < min && dist[i] > -1 ){
			min = dist[i];
		}
	}
	return min;
}
int FindMinP( LGraph Graph, int* dist, In InputNode, double D )
{
	int min = 100,ret;
	int i;
	for(i=0;i<Graph->Nv;i++){
		if ( BankJudge( InputNode, i, D ) && dist[i] < min && dist[i] > -1 ){
			min = dist[i];
			ret = i;
		}
	}
	return ret;
}
void ShortestPath( LGraph Graph, In InputNode, double D )
{
	int* dist[Graph->Nv];
	int* path[Graph->Nv];
	struct Input Ori;
	Ori.X = 0;
	Ori.Y = 0;
	int i, j, Beg[Graph->Nv];
	for(i=0;i<Graph->Nv;i++){
		int Dist = CalculateD( InputNode[i], Ori );
		Beg[i] = -1;
		if ( Dist < 7.5 + D ){
			dist[i] = (int*)malloc(Graph->Nv*sizeof(int));
			path[i] = (int*)malloc(Graph->Nv*sizeof(int));
			Beg[i] = Dist;
			SinglePath(Graph, InputNode, D, i, dist[i], path[i] );
			int* temp = dist[i];
		}
	}
	
	int FirstP[Graph->Nv];
	j = 0;
	for(i=0;i<Graph->Nv;i++){
		if ( Beg[i] > 0 ){
			FirstP[j++] = i;
		}
	}
	int MinDist = -1;
	for(i=0;i<j;i++){
		if( FindMinDist( Graph, dist[FirstP[i]], InputNode, D) == 100 ){
			Beg[FirstP[i]] = -1;
		}else{
			MinDist = FindMinDist( Graph, dist[FirstP[i]], InputNode, D);
		}
	}
	if ( MinDist == -1 ) {
		printf("0");
		return;
	}else if ( MinDist == 100 ){
		printf("0");
		return;
	}
	double MinD = 100;
	int index;
	for(i=0;i<j;i++){
		if( Beg[FirstP[i]] > 0 && MinD > Beg[FirstP[i]] ){
			MinD = Beg[FirstP[i]];
			index = FirstP[i];
		}
	}
	Vertex EndV = FindMinP( Graph, dist[index], InputNode, D);
	int* temp = path[index];
	Stack S = CreateS();
	int cnt=0;
	while( EndV != -2 ){
		S = Push( S, EndV );
		EndV = temp[EndV];
	}
	if( MinDist == 0 ) {
		printf("%d\n",MinDist+1);
	}else{
		printf("%d\n",MinDist+2);
		while( !IsEmptyS(S) ){
			int temp = Pop(S);
			printf("%d %d\n",InputNode[temp].X,InputNode[temp].Y);
		}
	}	
}

int main( int agc, const char* agv[] )
{
	int N;
	double D;
	scanf("%d %lf",&N,&D);
	In InputNode = ( In )malloc( N * sizeof( struct Input ) );
	int i;
	for(i=0;i<N;i++) {
		int a,b;
		scanf(" %d %d", &a, &b );
		if( abs(a) > 50 || abs(b) > 50 || sqrt( pow(a,2) + pow(b,2) ) < 7.5 ) {
			i--;
			N--;
		}else {
			InputNode[i].X = a, InputNode[i].Y = b;
		}
	}
	LGraph Graph = BuildLG( N, D, InputNode );
	ShortestPath( Graph, InputNode, D );
	
	return 0;
}

