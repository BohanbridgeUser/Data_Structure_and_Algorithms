#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MaxVertex 100
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

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMG()
{
    MGraph Graph;
    Vertex V, W;
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
            E->V1 = --v1;
            E->V2 = --v2;
            cin >> E->Weight;
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}
void Floyd(MGraph Graph,Vertex** FloydGraph,Vertex ** path)
{
    for (Vertex X = 0; X < Graph->Nv; X++) {
        for (Vertex V = 0; V < Graph->Nv; V++) {
            for (Vertex W = 0; W < Graph->Nv; W++) {
                if (FloydGraph[V][X] + FloydGraph[X][W] < FloydGraph[V][W]){
                    FloydGraph[V][W] = FloydGraph[V][X] + FloydGraph[X][W];
                    path[V][W] = X;
                }
            }
        }
    }
        
}
int main()
{
    MGraph Graph = BuildMG();
    Vertex** FloydGraph = (Vertex**)malloc(Graph->Nv * sizeof(Vertex*));
    for (Vertex V = 0; V < Graph->Nv; V++) FloydGraph[V] = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (Vertex W = 0; W < Graph->Nv; W++) {
            FloydGraph[V][W] = Graph->G[V][W];
        }
    }
    Vertex** FloydPath = (Vertex**)malloc(Graph->Nv * sizeof(Vertex*));
    for (Vertex V = 0; V < Graph->Nv; V++) FloydPath[V] = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (Vertex W = 0; W < Graph->Nv; W++) {
            FloydPath[V][W] = -1;
        }
    }
    Floyd(Graph, FloydGraph, FloydPath);
    return 0;
}
