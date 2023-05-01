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
    Vertex G2[MaxVertex][MaxVertex];
    DataType Data[MaxVertex];
};
typedef PtrToMGNode MGraph;

/* ENode */
typedef struct ENode* PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
    WeightType Toll;
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
            Graph->G2[V][W] = Infinity;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G2[E->V1][E->V2] = E->Toll;
    Graph->G[E->V2][E->V1] = E->Weight;
    Graph->G2[E->V2][E->V1] = E->Toll;
}

MGraph BuildMG(int *Beg, int* End)
{
    MGraph Graph;
    Vertex V, W;
    Edge E;

    int Nv;
    scanf("%d", &Nv);
    Graph = CreateMG(Nv);

    scanf("%d", &Graph->Ne);
    scanf("%d", Beg);
    scanf("%d", End);
    if (Graph->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; i++) {
            int v1, v2;
            cin >> v1;
            cin >> v2;
            E->V1 = v1;
            E->V2 = v2;
            cin >> E->Weight;
            cin >> E->Toll;
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}
int FindMinDist(MGraph Graph, Vertex* dist, Vertex* collected, int* cost)
{
    int MinDist = Infinity;
    int MinCost = Infinity;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (dist[W] < MinDist && dist[W] != 0 && collected[W] == -1) {
            MinDist = dist[W];
            MinCost = cost[W];
            MinV = W;
        }
        else if (dist[W] == MinDist && MinDist != Infinity && collected[W] == -1)
        {
            MinDist = dist[W];
            MinCost = cost[W];
            MinV = W;
        }
    }
    return MinV;
}
void Dijkstra(MGraph Graph, Vertex* path, Vertex* dist, Vertex* collected,int* cost, Vertex V)
{
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity) dist[W] = Graph->G[V][W];
    }
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G2[V][W] != Infinity) cost[W] = Graph->G2[V][W];
    }
    dist[V] = 0;
    path[V] = -1;
    cost[V] = 0;
    collected[V] = 1;

    while (1) {
        Vertex P = FindMinDist(Graph, dist, collected, cost);
        if (P == -1) break;
        collected[P] = 1;
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (collected[W] == -1 && Graph->G[V][W] != Infinity) {
                if (Graph->G[P][W] + dist[P] < dist[W]) {
                    dist[W] = Graph->G[P][W] + dist[P];
                    path[W] = P;
                    cost[W] = Graph->G2[P][W] + cost[P];
                }
                else if (Graph->G[P][W] + dist[P] == dist[W] && Graph->G2[P][W] + cost[P] < cost[W]) {
                    dist[W] = Graph->G[P][W] + dist[P];
                    path[W] = P;
                    cost[W] = Graph->G2[P][W] + cost[P];
                }
            }   
        }
    }
}
int main()
{
    int Beg, End;
    MGraph Graph = BuildMG(&Beg,&End);
    Vertex* dist = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) dist[V] = Infinity;
    Vertex* path = (Vertex*)malloc(Graph->Nv * (sizeof(Vertex)));
    for (Vertex V = 0; V < Graph->Nv; V++) path[V] = 0;
    Vertex* collected = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) collected[V] = -1;
    int* cost = (int*)malloc(Graph->Nv * sizeof(int));
    for (int V = 0; V < Graph->Nv; V++) cost[V] = Infinity;
    Dijkstra(Graph, path, dist, collected, cost, Beg);
    
    cout << dist[End] << ' ';
    cout << cost[End];
    return 0;
}
