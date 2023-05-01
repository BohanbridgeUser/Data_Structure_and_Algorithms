#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MaxVertex 1000;
#define INFINITY 65535;

typedef int Vertex;
typedef int WeightType;

/* GNode */
typedef struct GNode* PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    WeightType** G;
};
typedef PtrToGNode MGraph;
/* Edge */
typedef struct ENode* PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

MGraph  CreateMG(Vertex VertexNum)
{
    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    Graph->G = (WeightType**)malloc(VertexNum * sizeof(WeightType*));
    for (Vertex V = 0; V < VertexNum; V++) {
        Graph->G[V] = (WeightType*)malloc(VertexNum * sizeof(WeightType));
    }

    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (Vertex W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = 0;
    }
    return Graph;
}
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}
MGraph BuildMGraph()
{
    int Nv;
    Vertex V, W;
    MGraph Graph;
    Edge E;

    cin >> Nv;
    Graph = CreateMG(Nv);

    cin >> Graph->Ne;
    if (Graph->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (V = 0; V < Graph->Ne; V++) {
            Vertex v1, v2;
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
struct Que {
    PtrToQNode Head;
    PtrToQNode Rear;
};
typedef struct Que* Queue;

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
        PtrToQNode TEMP =Q->Head->Next;
        if (!Q->Head->Next->Next) {
            Q->Head->Next = NULL;
            Q->Rear = Q->Head;
            free(TEMP);
            return ret;
        }
        else {
            Q->Head->Next = Q->Head->Next->Next;
            free(TEMP);
            return ret;
        }
    }
}

void Visit(Vertex* visit, Vertex V)
{
    visit[V] = 1;
    cout << V << endl;
}
void BFS(MGraph Graph, Vertex* visit, Vertex V)
{
    Queue Q = CreateQ();
    Q = InQueue(Q, V);
    while (!IsEmptyQ(Q)) {
        Vertex W = DeQueue(Q);
        if(visit[W] == -1) Visit(visit, W);
        for (Vertex X = W + 1; X < Graph->Nv; X++) {
            if (Graph->G[W][X] != 0 && visit[X] == -1) {
                Q = InQueue(Q, X);
            }
        }
    }
}
int main()
{
    MGraph Graph = BuildMGraph();
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));

    for (Vertex V = 0; V < Graph->Nv; V++)
        visit[V] = -1;

    BFS(Graph, visit, 0);
    return 0;
}
