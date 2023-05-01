#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

#define MaxVertex 1000
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
            E->V1 = v1;
            E->V2 = v2;
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
int main()
{
    MGraph Graph = BuildMG();
    int K;
    cin >> K;
    cin.get();
    for (int i = 0; i < K; i++) {
        int J;
        cin>>J;
        if (J != Graph->Nv + 1) {
            cout << "NO\n";
            int x;
            for (int i = 0; i < J; i++)
                cin >> x;
        }
        else {
            int y = -1, crt = 1;
            int beg;
            Vertex* collected = (Vertex*)malloc((Graph->Nv + 1) * sizeof(Vertex));
            for (Vertex V = 0; V < Graph->Nv; V++) collected[V] = -1;
            for (int i = 0; i < J; i++) {
                int x;
                cin >> x;
                if (collected[x] == -1) collected[x] = 1;
                else if(collected[x] == 1 && i<J-1) crt = 0;
                if (y == -1) {
                    y = x;
                    beg = x;
                    continue;
                }
                if (Graph->G[y][x] == Infinity) {
                    crt = 0;
                }
                if (i == J - 1 && x!= beg) {
                    crt = 0;
                }
                y = x;
            }
            crt == 0 ? cout << "NO\n" : cout << "YES\n";
        }
    }
    return 0;
}


