#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

#define MaxVertex 10000
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
            //cin >> E->Weight;
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}
/* DFS */
void Visit(Vertex* visit, Vertex V)
{
    visit[V] = 1;
}
void DFS(MGraph Graph, Vertex* visit, Vertex V)
{
    Visit(visit, V);
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != 0 && visit[W] == -1) {
            DFS(Graph, visit, W);
        }
    }
}

int FindMinDist(MGraph Graph, Vertex* dist, Vertex* collected)
{
    int MinDist = Infinity;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (dist[W] < MinDist && dist[W] != 0 && collected[W] == -1) {
            MinDist = dist[W];
            MinV = W;
        }
    }
    return MinV;
}
void Dijkstra(MGraph Graph, Vertex* path, Vertex* dist, Vertex* collected, Vertex V)
{
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity) dist[W] = Graph->G[V][W];
    }
    dist[V] = 0;
    path[V] = -1;
    collected[V] = 1;

    int cnt = 0;
    while (1) {
        Vertex P = FindMinDist(Graph, dist, collected);
        if (P == -1) break;
        collected[P] = 1;
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (Graph->G[P][W] + dist[P] < dist[W] && collected[W] == -1) {
                dist[W] = Graph->G[P][W] + dist[P];
                path[W] = P;
            }
        }
        cnt++;
    }
}
int main()
{
    MGraph Graph = BuildMG();
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) visit[V] = -1;
    DFS(Graph, visit, 0);
    int crt = 1;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (visit[V] == -1) {
            crt = 0;
            break;
        }
    }
    
    Vertex* dist = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* path = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* collected = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));

    int K;
    cin >> K;
    for (Vertex V = 0; V < K; V++) {
        int i;
        cin >> i;
        double ret = 0.00;
        cout.setf(ios::fixed);
        if (crt == 0) cout << "Cc(" << i << ")="<< setprecision(2) <<  ret << endl;
        else {
            for (Vertex W = 0; W < Graph->Nv; W++) {
                dist[W] = Infinity;
                path[W] = i-1;
                collected[W] = -1;
            }
            Dijkstra(Graph, path, dist, collected, i-1);
            Vertex sum = 0;
            for (int j = 0; j < Graph->Nv; j++) {
                sum += dist[j];
            }
            ret = (Graph->Nv-1) * 1.0 / sum * 1.0;
            cout << "Cc(" << i << ")=" << setprecision(2) << ret << endl;
        }
    }
    return 0;
}

