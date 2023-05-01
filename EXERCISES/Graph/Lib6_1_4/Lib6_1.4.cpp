#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MaxVertex 1000;
//#define INFINITY 65535;

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
MGraph BuildMGraph(Vertex* X)
{
    int Nv;
    Vertex V, W;
    MGraph Graph;
    Edge E;

    cin >> Nv;
    Graph = CreateMG(Nv);

    cin >> Graph->Ne;
    Vertex Y;
    cin >> Y;
    *X = Y;
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
void Visit(Vertex* visit,Vertex* sequence, Vertex V)
{
    visit[V] = 1;
}
void DFS_Recursion(MGraph Graph, Vertex* visit,Vertex* sequence, Vertex V,int* n)
{
    Visit(visit,sequence, V);
    sequence[(*n)++] = V;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != 0 && visit[W] == -1) {
            DFS_Recursion(Graph, visit, sequence,W,n);
            sequence[(*n)++] = V;
        }
    }
}

int main()
{
    Vertex X;
    MGraph Graph = BuildMGraph(&X);
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) visit[V] = -1;
    Vertex* sequence = (Vertex*)malloc(3000*sizeof(Vertex));
    for (Vertex V = 0; V < 3000; V++) sequence[V] = -1;
    int n = 0;
    DFS_Recursion(Graph, visit, sequence, X-1,&n);
    int judge = 1;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (visit[V] == -1) {
            judge = 0;
        }
    }
    int j = 1;
    cout << sequence[0]+1;
    while (sequence[j] != -1) {
        cout << ' ' << sequence[j++]+1;
    }
    if (judge == 0) cout <<' '<< 0 << endl;
    return 0;
}

