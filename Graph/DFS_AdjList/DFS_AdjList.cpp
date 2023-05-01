#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MaxVertex 1000;

typedef int Vertex;
typedef int WeightType;

/* AdjVNode*/
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode {
	Vertex V2;
	WeightType Weight;
	PtrToAdjVNode Next;
};
/* AdjList */
typedef struct VNode* PtrToVNode;
struct VNode {
	PtrToAdjVNode FirstEdge;
};
typedef PtrToVNode AdjList;
/* GNode */
typedef struct GNode* PtrToGNode;
struct GNode {
	int Nv;
	int Ne;
	AdjList* G;
};
typedef PtrToGNode LGraph;
/*Edge */
typedef struct ENode* PtrToENode;
struct ENode {
	Vertex V1, V2;
	WeightType Weight;
};
typedef PtrToENode Edge;

LGraph CreateLG(Vertex VertexNum)
{
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	Graph->G = (AdjList*)malloc(VertexNum * sizeof(PtrToVNode));

	for (Vertex V = 0; V < Graph->Nv; V++) {
		Graph->G[V] = (AdjList)malloc(sizeof(struct VNode));
		Graph->G[V]->FirstEdge = NULL;
	}
	return Graph;
}
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct ENode));
	NewNode->V2 = E->V2;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V1]->FirstEdge;
	Graph->G[E->V1]->FirstEdge = NewNode;

	PtrToAdjVNode NewNode2 = (PtrToAdjVNode)malloc(sizeof(struct ENode));
	NewNode2->V2 = E->V1;
	NewNode2->Weight = E->Weight;
	NewNode2->Next = Graph->G[E->V2]->FirstEdge;
	Graph->G[E->V2]->FirstEdge = NewNode2;
}
LGraph BuildLG()
{
	int Nv;
	Vertex V, W;
	LGraph Graph;
	Edge E;

	cin >> Nv;
	Graph = CreateLG(Nv);
	cin >> Graph->Ne;

	if (Graph->Ne) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (V = 0; V < Graph->Ne; V++) {
			int v1, v2;
				scanf_s("%d %d", &v1, &v2);
			E->V1 = v1 - 1;
			E->V2 = v2 - 1;
			E->Weight = 1;
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}

/* Queue */
typedef Vertex ElementofQueue;
typedef struct QNode* PtrToQNode;
struct QNode {
	ElementofQueue Data;
	PtrToQNode Next;
};
typedef struct Que* Queue;
struct Que {
	PtrToQNode Head;
	PtrToQNode Rear;
};

Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct Que));
	Q->Head = (PtrToQNode)malloc(sizeof(struct QNode));
	Q->Rear = Q->Head;
	Q->Head->Next = NULL;
	return Q;
}
int IsEmptyQ(Queue Q)
{
	if (!Q->Head->Next) return 1;
	else return 0;
}
Queue InQueue(Queue Q, ElementofQueue X)
{
	PtrToQNode NewNode = (PtrToQNode)malloc(sizeof(struct QNode));
	NewNode->Data = X;
	NewNode->Next = Q->Rear->Next;
	Q->Rear->Next = NewNode;
	Q->Rear = Q->Rear->Next;
	return Q;
}
ElementofQueue DeQueue(Queue Q)
{
	if (!IsEmptyQ(Q)) {
		ElementofQueue ret = Q->Head->Next->Data;
		if (Q->Head->Next->Next) {
			PtrToQNode TEMP = Q->Head->Next;
			Q->Head->Next = Q->Head->Next->Next;
			free(TEMP);
			return ret;
		}
		else {
			PtrToQNode TEMP = Q->Head->Next;
			Q->Head->Next = NULL;
			Q->Rear = Q->Head;
			free(TEMP);
			return ret;
		}
	}
	else {
		return -1;
	}
}

/* DFS */
void Visit(Vertex* visit, Vertex V)
{
	visit[V] = 1;
	cout << V << endl;
}
void DFS_Recursion(LGraph Graph, Vertex* visit, Vertex V)
{
	Visit(visit, V);

	for (PtrToAdjVNode P = Graph->G[V]->FirstEdge;P; P = P->Next) {
		if (visit[P->V2] == -1) {
			DFS_Recursion(Graph, visit, P->V2);
		}
	}
}

/* Stack */
typedef Vertex ElementofStack;

typedef struct SNode* PtrToSNode;
struct SNode {
	ElementofStack Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
int IsEmptyS(Stack S)
{
	if (!S->Next) {
		return 1;
	}
	else {
		return 0;
	}
}
Stack Push(Stack S, ElementofStack X)
{
	PtrToSNode NewNode = (PtrToSNode)malloc(sizeof(struct SNode));
	NewNode->Data = X;
	NewNode->Next = S->Next;
	S->Next = NewNode;
	return S;
}
ElementofStack Pop(Stack S)
{
	if (!IsEmptyS(S)) {
		ElementofStack ret = S->Next->Data;
		PtrToSNode TEMP = S->Next;
		if (S->Next->Next) {
			S->Next = S->Next->Next;
			free(TEMP);
			return ret;
		}
		else {
			S->Next = NULL;
			free(TEMP);
			return ret;
		}
	}
}
void DFS_NonRecursion(LGraph Graph, Vertex* visit, Vertex V)
{
	Visit(visit, V);

	Stack S = CreateS();
	S = Push(S, V);
	while (!IsEmptyS(S)) {
		Vertex W = Pop(S);
		for (PtrToAdjVNode P = Graph->G[W]->FirstEdge; P; P = P->Next) {
			if (visit[P->V2] == -1) {
				Visit(visit, P->V2);
				S = Push(S, P->V2);
			}
		}
	}
}
int main()
{
	LGraph Graph = BuildLG();
	Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
	for (Vertex V = 0; V < Graph->Nv; V++) {
		cout << V << " ";
		for (PtrToAdjVNode P = Graph->G[V]->FirstEdge; P; P = P->Next) {
			cout << P->V2 <<' ';
		}
		cout << endl;
	}
	
	for (Vertex W = 0; W < Graph->Nv; W++)
		visit[W] = -1;
	//DFS_Recursion(Graph, visit, 0);
	DFS_NonRecursion(Graph, visit, 0);
	return 0;
}