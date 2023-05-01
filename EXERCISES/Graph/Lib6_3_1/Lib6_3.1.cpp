#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
            //cin >> E->Weight;
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
void DFS(MGraph Graph, Vertex* visit, Vertex V)
{
    Visit(visit, V);
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity && visit[W] == -1) {
            DFS(Graph, visit, W);
        }
    }
}
int JudgeConnected(MGraph Graph,Vertex* visit, Vertex V, Vertex W)
{
    for (Vertex X = 0; X < Graph->Nv; X++) {
        visit[X] = -1;
    }
    DFS(Graph, visit, V);
    if (visit[W] == 1) return 1;
    else return 0;
}
int CountJudge(MGraph Graph, Vertex* visit, Vertex* lost)
{
    for (Vertex X = 0; X < Graph->Nv; X++) {
        visit[X] = -1;
    }
    int crt = 0;
    int cnt = 0;
    Vertex V=0;
    while (lost[V] != 0) {
        V++;
    }
    while (crt == 0) {
        crt = 1;
        DFS(Graph, visit, V);
        for (V = 0; V < Graph->Nv; V++) {
            if (visit[V] == -1 && lost[V] == 0) {
                crt = 0;
                break;
            }
        }    
        cnt++;
    }
    return cnt;
}
int main()
{
    MGraph Graph = BuildMG();
    //Vertex** connected = (Vertex**)malloc(Graph->Nv * sizeof(Vertex*));
    //for (Vertex V = 0; V < Graph->Nv; V++) connected[V] = (Vertex*)malloc(Graph->Nv*sizeof(Vertex));
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    //for (Vertex V = 0; V < Graph->Nv; V++) {
    //    for (Vertex W = 0; W < Graph->Nv; W++) {
    //        if (JudgeConnected(Graph, visit, V, W) == 1) {
    //            connected[V][W] = 1;
    //        }
    //        else {
    //            connected[V][W] = 0;
    //        }
    //    }
    //}
    Vertex* lost = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++)lost[V] = 0;
    int cnt = CountJudge(Graph, visit,lost);
    int K;
    cin >> K;
    
    for (Vertex V = 0; V < K; V++) {
        Vertex W;
        cin >> W;
        lost[W] = 1;
        for (Vertex X = 0; X < Graph->Nv; X++) {
            Graph->G[W][X] = Infinity;
            Graph->G[X][W] = Infinity; 
        }
        
        int crt = 1;
        int cnt2 = CountJudge(Graph, visit,lost);
        if (cnt2 > cnt) crt = 0;
        cnt = cnt2;

        if (crt) cout << "City " << W << " is lost.\n";
        else cout << "Red Alert: City " << W << " is lost!\n";
        if (V == Graph->Nv - 1) cout << "Game Over.\n";
    }
    return 0;
}

