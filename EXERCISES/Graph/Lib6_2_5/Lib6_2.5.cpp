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

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMG(int Nv, int Ne, int* teams)
{
    MGraph Graph;
    Vertex V, W;
    Edge E;
    Graph = CreateMG(Nv);
    Graph->Ne = Ne;
    cin.get();
    for (int i = 0; i < Nv; i++) cin >> teams[i];

    if (Graph->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; i++) {
            int v1, v2;
            cin >> v1;
            cin >> v2;
            E->V1 = v1;
            E->V2 = v2;
            cin >> E->Weight;
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}
int FindMinDist(MGraph Graph, Vertex* dist, Vertex* collected,int* teams,Vertex* toll)
{
    int MinDist = Infinity;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (dist[W] < MinDist && dist[W] != 0 && collected[W] == -1) {
            MinDist = dist[W];
            MinV = W;
        }
        else if (dist[W] == MinDist && dist[W] != 0 && collected[W] == -1 && toll[W] > toll[MinV]) {
            MinDist = dist[W];
            MinV = W;
        }
    }
    return MinV;
}
void Dijkstra(MGraph Graph, Vertex* path, Vertex* dist, Vertex* collected,int* teams,Vertex* toll,Vertex* count,Vertex V)
{
    toll[V] = teams[V];
    count[V] = 1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity) {
            dist[W] = Graph->G[V][W];
            path[W] = V;
            count[W] = count[V];
            if (toll[W] < toll[V] + teams[W]) toll[W] = toll[V] + teams[W];
        }
    }

    dist[V] = 0; 
    path[V] = -1;
    collected[V] = 1;
    int cnt = 1;
    while (1) {
        Vertex P = FindMinDist(Graph, dist, collected,teams,toll);
        if (P == -1) break;
        collected[P] = 1;
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (Graph->G[P][W] + dist[P] < dist[W] && collected[W] == -1) {
                count[W] = count[P];
                dist[W] = Graph->G[P][W] + dist[P];
                path[W] = P;
                toll[W] = toll[P] + teams[W];
            }
            else if (Graph->G[P][W] + dist[P] == dist[W] && collected[W] == -1) {
                count[W] = count[P] + count[W];
                cnt++;
                if (toll[W] < toll[P] + teams[W]) {
                    dist[W] = Graph->G[P][W] + dist[P];
                    path[W] = P;
                    toll[W] = toll[P] + teams[W];
                }
            }
        }
    }
}
int main()
{
    int Nv, Ne, beg, end;
    cin >> Nv;
    cin >> Ne;
    cin >> beg;
    cin >> end;
    int* teams = (int*)malloc(Nv * sizeof(int));
    MGraph Graph = BuildMG(Nv, Ne, teams);
    Vertex* dist = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) dist[V] = Infinity;
    Vertex* path = (Vertex*)malloc(Graph->Nv * (sizeof(Vertex)));
    for (Vertex V = 0; V < Graph->Nv; V++) path[V] = 0;
    Vertex* collected = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) collected[V] = -1;
    Vertex* toll = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) toll[V] = 0;
    Vertex* count = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) count[V] = 0;
    Dijkstra(Graph, path, dist, collected,teams,toll,count, beg);


    int team = 0;
    Vertex* out = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) out[V] = -1;

    Vertex i = end;
    int j = 0,cnt = 0;
    while (path[i] != -1) {
        out[j++] = path[i];
        i = path[i];
        cnt += 1;
    }
    cout << count[end] << ' ' << toll[end] << endl;
    for (int i = cnt-1; i > -1; i--) {
        cout << out[i] << ' ';
    }
    cout << end;
    return 0;
}
