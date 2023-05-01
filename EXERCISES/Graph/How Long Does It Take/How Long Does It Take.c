#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MavVertexNum 100
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
};
/* LGraph */
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
	Graph->G = (AdjList)malloc(Graph->Nv*sizeof(struct VNode));
	int i;
	for(i=0;i<Graph->Nv;i++) Graph->G[i].FirstEdge =NULL;
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
	LGraph Graph = CreateLG(N);
	if( !M ) return Graph;
	else{
		Edge E = (Edge)malloc(sizeof(struct ENode));
		int i;
		for(i=0;i<M;i++){
			scanf(" %d %d %d",&E->V1,&E->V2,&E->Weight);
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
		NewNode->Next = NULL;
		Q->Rear->Next = NewNode;
		Q->Rear = Q->Rear->Next;
	}
	return Q;
}
ElementTypeofQueue DeleteQ( Queue Q )
{
	if( IsEmptyQ(Q) ){
		return -10;
	}else{
		PtrToQNode TEMP;
		ElementTypeofQueue RET;
		if( !Q->Head->Next ){
			TEMP = Q->Head;
			Q->Head = NULL;
			Q->Rear = NULL;
			RET = TEMP->Data;
			free(TEMP);
			return RET;
		}else{
			TEMP = Q->Head;
			Q->Head = Q->Head->Next;
			RET = TEMP->Data;
			free(TEMP);
			return RET;
		}
	}
}
void TopSort( LGraph Graph, int* Indegree )
{
	Queue Q = CreateQ();
	int i;
	int* Time = (int*)malloc(Graph->Nv*sizeof(int));
	for(i=0;i<Graph->Nv;i++){
		if( !Indegree[i] ){
			Q = AddQ( Q, i);
		}
	}
	int cnt = 0;
	while( !IsEmptyQ(Q) ){
		Vertex V = DeleteQ( Q );
		cnt++;
		PtrToAdjVNode TEMP;
		for(TEMP=Graph->G[V].FirstEdge;TEMP;TEMP=TEMP->Next){
			if( Time[V] + TEMP->Weight > Time[TEMP->V2] ){
				Time[TEMP->V2] = Time[V] + TEMP->Weight;
			}
			if( --Indegree[TEMP->V2] == 0){
				Q = AddQ( Q, TEMP->V2 );
			}	
		}	
	}
	int max=0;
	if( cnt != Graph->Nv )
		printf("Impossible\n");
	else {
		for(i=0;i<Graph->Nv;i++){
			if( Time[i] > max )
				max = Time[i];
		}
		printf("%d\n",max);
	}
}
int main(int agc,const char* agv[])
{
	int N, M, i;
	scanf("%d %d", &N, &M);
	int Indegree[N];
	for(i=0;i<N;i++) Indegree[i]=0;
	LGraph Graph = BuildLG( N, M, Indegree );
	TopSort( Graph, Indegree );
	return 0;
}

