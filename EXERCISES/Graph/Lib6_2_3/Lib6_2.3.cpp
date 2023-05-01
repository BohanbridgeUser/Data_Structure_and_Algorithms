#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

#define MaxVertex 1000
#define Infinity 65534

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

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

/* Edge */
typedef struct ENode* Edge;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
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
typedef struct INode* PtrToINode;
struct INode {
    double X;
    double Y;
};
double CalD(struct INode V, struct INode W)
{
    double ret = sqrt(pow(V.X - W.X, 2) + pow(V.Y - W.Y, 2));
    return ret;
}
PtrToINode In(LGraph Graph,PtrToINode Input) 
{
    for (Vertex V = 1; V < Graph->Nv; V++) {
        cin >> Input[V].X;
        cin >> Input[V].Y;
    }
    Input[0].X = 0;
    Input[0].Y = 0;
    return Input;
}
LGraph BuildLG(PtrToINode Input,int Nv, double D)
{
    LGraph Graph;
    Edge E;

    Graph = CreateLG(Nv + 1);
    Input = In(Graph,Input);

    for (Vertex V = 1; V < Graph->Nv; V++) {
        if (CalD(Input[0], Input[V]) <= D + 15) {
            E = (Edge)malloc(sizeof(struct ENode));
            E->V1 = 0;
            E->V2 = V;
            E->Weight = 1;
            InsertEdgeLG(Graph, E);
        }
    }

    for (Vertex V = 1; V < Graph->Nv; V++) {
        for (Vertex W = 1; W < Graph->Nv; W++) {
            if (V != W && CalD(Input[V], Input[W]) <= D) {
                E = (Edge)malloc(sizeof(struct ENode));
                E->V1 = V;
                E->V2 = W;
                E->Weight = 1;
                InsertEdgeLG(Graph, E);
            }
        }
    }
    return Graph;
}
int Visit(Vertex* visit,PtrToINode Input, Vertex V,double D)
{
    visit[V] = 1;
    if (V == 0 && 50 - 15 <= D) return 1;
    if (50 - fabs(Input[V].X) <= D || 50 - fabs(Input[V].Y) <= D) return 1;
    else return 0;
}
int Judge(LGraph Graph,PtrToINode Input, Vertex* visit,Vertex V,double D)
{
    if(Visit(visit,Input, V, D) == 1 ) return 1;
    for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
        if (visit[P->V2] == -1) {
            if (Judge(Graph, Input, visit, P->V2,D) == 1) return 1;
        }
    }
    return 0;
}

int main()
{
    int Nv;
    cin >> Nv;
    double D;
    cin >> D;
    PtrToINode Input = (PtrToINode)malloc((Nv+1)*sizeof(struct INode));
    LGraph Graph = BuildLG(Input,Nv,D);
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) visit[V] = -1;

    if (Judge(Graph, Input, visit, 0,D) == 1) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}

