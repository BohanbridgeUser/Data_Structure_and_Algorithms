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

/* DFS */
void Visit(Vertex* visit, Vertex V)
{
    visit[V] = 1;
    cout << V << endl;
}
void DFS_Recursion(MGraph Graph, Vertex* visit, Vertex V)
{
    Visit(visit, V);
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != 0 && visit[W] == -1) {
            DFS_Recursion(Graph, visit, W);
        }
    }
}

/* Stack */
typedef Vertex ElementofStack;

typedef struct SNode* PtrToSNode;
struct SNode {
    ElementofStack Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
int IsEmptyS(Stack S)
{
    if (!S->Next) {
        return 1;
    }
    else {
        return 0;
    }
}
Stack Push(Stack S, ElementofStack X)
{
    PtrToSNode NewNode = (PtrToSNode)malloc(sizeof(struct SNode));
    NewNode->Data = X;
    NewNode->Next = S->Next;
    S->Next = NewNode;
    return S;
}
ElementofStack Pop(Stack S)
{
    if (!IsEmptyS(S)) {
        ElementofStack ret = S->Next->Data;
        PtrToSNode TEMP = S->Next;
        if (S->Next->Next) {
            S->Next = S->Next->Next;
            free(TEMP);
            return ret;
        }
        else {
            S->Next = NULL;
            free(TEMP);
            return ret;
        }
    }
}
void DFS_Nonrecursion(MGraph Graph, Vertex* visit, Vertex V)
{
    Visit(visit, V);

    Vertex W = V;
    Stack S = CreateS();
    S = Push(S, V);
    int cnt = 0;
    while (!IsEmptyS(S)) {
        Vertex X = W + 1;
        for (X; (Graph->G[W][X] == 0 || visit[X] != -1) && X < Graph->Nv; X++);
        if (X < Graph->Nv) {
            Visit(visit, X);
            S = Push(S, X);
            W = X;
        }
        else {
            if (W != V) {
                W = Pop(S);
            }
            else {
                break;
            }
        }
    }
}
int main()
{
    MGraph Graph = BuildMGraph();
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex W = 0; W < Graph->Nv; W++) visit[W] = -1;

    //DFS_Recursion(Graph, visit, 0);
    DFS_Nonrecursion(Graph, visit, 0);
    return 0;
}

