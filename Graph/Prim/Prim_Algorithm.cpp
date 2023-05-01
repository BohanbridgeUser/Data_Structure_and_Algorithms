#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MaxVertex 500
#define Infinity 65535

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

/* GNode */
typedef struct MGNode* PtrToMGNode;
struct MGNode {
    int Nv;
    int Ne;
    Vertex G[MaxVertex][MaxVertex];
    DataType Data[MaxVertex];
};
typedef PtrToMGNode MGraph;
/* ENode */
typedef struct ENode* PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

MGraph CreateMG(Vertex VertexNum)
{
    MGraph Graph = (MGraph)malloc(sizeof(struct MGNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (Vertex V = 0; V < VertexNum; V++) {
        for (Vertex W = 0; W < VertexNum; W++) {
            Graph->G[V][W] = Infinity;
        }
    }
    return Graph;
}
void InsertEdgeMG(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}
MGraph BuildMG()
{
    MGraph Graph;
    Vertex V=0, W=0;
    Edge E;

    int Nv;
    cin >> Nv;

    Graph = CreateMG(Nv);

    cin >> Graph->Ne;

    if (Graph->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; i++) {
            int v1, v2;
            cin >> v1;
            cin >> v2;
            E->V1 = v1 - 1;
            E->V2 = v2 - 1;
            cin >> E->Weight;
            InsertEdgeMG(Graph, E);
        }
    }

    return Graph;
}

/* AdjVNode */
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode {
    Vertex V2;
    WeightType Weight;
    PtrToAdjVNode Next;
};
/* Head List */
typedef struct VNode* AdjList;
struct VNode {
    PtrToAdjVNode FirstEdge;
    DataType Data;
};
/* LGraph */
typedef struct LGNode* LGraph;
struct LGNode {
    int Nv;
    int Ne;
    AdjList G;
};

LGraph CreateLG(Vertex VertexNum)
{
    LGraph Graph = (LGraph)malloc(sizeof(struct LGNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    Graph->G = (AdjList)malloc(VertexNum * sizeof(struct VNode));

    for (Vertex V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}
void InsertEdgeLG(LGraph Graph, Edge E)
{
    if (E->V1 == -1) E->V1 = 0;
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

Vertex FindMinDist(MGraph Graph, int* dist)
{
    int MinDist = Infinity;
    int ret = -1;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (dist[V] != 0 && dist[V] < MinDist) {
            ret = V;
            MinDist = dist[V];
        }
    }
    return ret;
}
int Prim(MGraph MGGraph, LGraph LGGraph,int* dist,Vertex* parent)
{
    int TotalWeight = 0, Count = 0;
    parent[0] = -1;
    dist[0] = 0;

    for (Vertex V = 0; V < MGGraph->Nv; V++) {
        if (MGGraph->G[0][V] != Infinity) {
            dist[V] = MGGraph->G[0][V];
        }
    }
    Count++;

    while (1) {
        Vertex V = FindMinDist(MGGraph, dist);
        if (V == -1)break;

        Edge E = (Edge)malloc(sizeof(struct ENode));
        E->V1 = parent[V];
        E->V2 = V;
        E->Weight = dist[V];
        TotalWeight += E->Weight;
        dist[V] = 0;
        InsertEdgeLG(LGGraph, E);
        Count++;

        for (Vertex W = 0; W < MGGraph->Nv; W++) {
            if (MGGraph->G[V][W] != Infinity && dist[W] > MGGraph->G[V][W]) {
                dist[W] = MGGraph->G[V][W];
                parent[W] = V;
            }
        }
    }
    cout << Count << endl;
    if (Count == MGGraph->Nv) return TotalWeight;
    else return -1;
}


int main()
{
    MGraph Graph = BuildMG();
    int* dist = (int*)malloc(Graph->Nv * sizeof(int));
    for (Vertex V = 0; V < Graph->Nv; V++) dist[V] = Infinity;
    Vertex* parent = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) parent[V] = 0;
    LGraph LGGraph = CreateLG(Graph->Nv);

    int TotalWeight = Prim(Graph, LGGraph, dist, parent);
    cout << TotalWeight << endl;
    return 0;
}
