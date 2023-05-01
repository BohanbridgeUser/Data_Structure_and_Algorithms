#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


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
void Visit(Vertex* visit, Vertex V)
{
    visit[V] = 1;
}
void DFS(MGraph Graph, Vertex* visit,Vertex V)
{
    Visit(visit, V);
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if ( Graph->G[V][W] == 1 && visit[W] == 0) {
            DFS(Graph, visit, W);
        }
    }
}
int main()
{
    MGraph Graph = BuildMGraph();
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) visit[V] = 0;

    DFS(Graph, visit,0);

    Vertex* degree = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) degree[V] = 0;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (Graph->G[V][W] == 1) degree[V]++;
        }
    }
    int j = 1;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (visit[V] == 0) {
            j = 0;
            break;
        }
    }
    
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (degree[V] % 2 != 0) {
            j = 0;
            break;
        }
    }
    if (j == 0) cout << 0 << endl;
    else cout << 1 << endl;
    return 0;
}

