#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

#define MaxVertex 200
#define Infinity 65534

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

/* Edge */
typedef struct ENode* Edge;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};

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
PtrToINode In(MGraph Graph, PtrToINode Input)
{
    for (Vertex V = 1; V < Graph->Nv - 1; V++) {
        cin >> Input[V].X;
        cin >> Input[V].Y;
    }
    Input[0].X = 0;
    Input[0].Y = 0;
    return Input;
}
MGraph BuildLG(PtrToINode Input,int* First, int Nv, double D)
{
    MGraph Graph;
    Edge E;

    Graph = CreateMG(Nv + 2);
    Input = In(Graph, Input);
    int i = 0;
    for (Vertex V = 1; V < Graph->Nv - 1; V++) {
        if (CalD(Input[0], Input[V]) <= D + 15.0/2 && CalD(Input[V], Input[0]) > 15.0 / 2) {
            E = (Edge)malloc(sizeof(struct ENode));
            First[i++] = V;
            E->V1 = 0;
            E->V2 = V; 
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }

    for (Vertex V = 1; V < Graph->Nv - 1; V++) {
        for (Vertex W = 1; W < Graph->Nv - 1; W++) {
            if (V != W && CalD(Input[V], Input[W]) <= D && CalD(Input[V], Input[W]) > 0) {
                E = (Edge)malloc(sizeof(struct ENode));
                E->V1 = V;
                E->V2 = W;
                E->Weight = 1;
                InsertEdge(Graph, E);
            }
        }
    }

    for (Vertex V = 0; V < Graph->Nv; V++) {
        if ((50 - fabs(Input[V].X) <= D && fabs(Input[V].X) <= 50) || (50 - fabs(Input[V].Y) <= D && fabs(Input[V].Y) <= 50)) {
            E = (Edge)malloc(sizeof(struct ENode));
            E->V1 = V;
            E->V2 = Graph->Nv - 1;
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
int FindMinDist(MGraph Graph, Vertex* dist,double* FirstStep, Vertex* collected)
{
    int MinDist = Infinity;
    int firsts = Infinity;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (dist[W] < MinDist && dist[W] != 0 && collected[W] == -1) {
            MinDist = dist[W];
            MinV = W;
            firsts = FirstStep[W];
        }
    }
    return MinV;
}
void Dijkstra(MGraph Graph,PtrToINode Input, Vertex* path, Vertex* dist, Vertex* collected,double* FirstStep,double D, Vertex V)
{
    dist[V] = 0;
    path[V] = -1;
    collected[V] = 1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity) {
            dist[W] = Graph->G[V][W];
            path[W] = V;
        }
    }
    
    int cnt = 0;
    while (1) {
        Vertex P = FindMinDist(Graph, dist,FirstStep, collected);
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
void Floyd(MGraph Graph, Vertex** FloydGraph, Vertex** path)
{
    for (Vertex X = 0; X < Graph->Nv; X++) {
        for (Vertex V = 0; V < Graph->Nv; V++) {
            for (Vertex W = 0; W < Graph->Nv; W++) {
                if (FloydGraph[V][X] + FloydGraph[X][W] < FloydGraph[V][W] && V != W) {
                    FloydGraph[V][W] = FloydGraph[V][X] + FloydGraph[X][W];
                    path[V][W] = X;
                }
            }
        }
    }

}
/* Stack */
typedef int ElementofStack;
typedef struct SNode* PtrToSNode;
struct SNode {
    ElementofStack Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
    Stack S = new SNode;
    S->Next = NULL;
    return S;
}
Stack Push(Stack S, ElementofStack X)
{
    PtrToSNode NewNode = new SNode;
    NewNode->Data = X;
    NewNode->Next = S->Next;
    S->Next = NewNode;
    return S;
}
int IsEmptyS(Stack S)
{
    if (!S->Next) return 1;
    else return 0;
}
ElementofStack Pop(Stack S)
{
    ElementofStack ret = NULL;
    if (!IsEmptyS(S)) {
        ret = S->Next->Data;
        if (S->Next->Next) {
            PtrToSNode TEMP = S->Next;
            S->Next = S->Next->Next;
            free(TEMP);
            return ret;
        }
        else {
            PtrToSNode TEMP = S->Next;
            S->Next = NULL;
            free(TEMP);
            return ret;
        }
    }
    else {
        return NULL;
    }
}
int main()
{
    int Nv;
    cin >> Nv;
    double D;
    cin >> D;
    PtrToINode Input = (PtrToINode)malloc((Nv + 1) * sizeof(struct INode));
    int* First = (int*)malloc((Nv + 1) * sizeof(int));
    for (int i = 0; i < Nv + 1; i++) First[i] = Infinity;
    MGraph Graph = BuildLG(Input,First, Nv, D);

    Vertex** path = (Vertex**)malloc(Graph->Nv * sizeof(Vertex*));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        path[V] = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    }
    Vertex** FloydGraph = (Vertex**)malloc(Graph->Nv * sizeof(Vertex*));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        FloydGraph[V] = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    }
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (Vertex W = 0; W < Graph->Nv; W++) {
            FloydGraph[V][W] = Graph->G[V][W];
        }
    }
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (Vertex W = 0; W < Graph->Nv; W++) {
            path[V][W] = -1;
        }
    }
    Floyd(Graph, FloydGraph, path);
    int i = 0; 
    int MinStep = Infinity;
    int MinP = -1;
    double f = Infinity;
    while (First[i] != Infinity) {
        if (FloydGraph[First[i]][Graph->Nv - 1] < MinStep) {
            MinStep = FloydGraph[First[i]][Graph->Nv - 1];
            MinP = First[i];
            f = CalD(Input[0], Input[First[i]]);
        }
        else if (FloydGraph[First[i]][Graph->Nv - 1] == MinStep && CalD(Input[0],Input[First[i]]) < f) {
            MinStep = FloydGraph[First[i]][Graph->Nv - 1];
            MinP = First[i];
            f = CalD(Input[0], Input[First[i]]);
        }
        i++;
    }
    int crt = 1;
    if (First[0] == -1 || FloydGraph[Graph->Nv-1][0] == Infinity) crt = 0;
    if (FloydGraph[Graph->Nv - 1][0] == 1) {
        cout << 1 << endl;
        return 0;
    }
    if (crt) {
        cout << MinStep + 1 << endl;
        i = Graph->Nv - 1;

        Stack S = CreateS();
        while (path[MinP][i] != -1) {
            S = Push(S, path[MinP][i]);
            i = path[MinP][i];
        }
        cout << Input[MinP].X << ' ' << Input[MinP].Y << endl;
        while (!IsEmptyS(S)) {
            int tmp = Pop(S);
            cout << Input[tmp].X << ' ' << Input[tmp].Y << endl;
        }
    }
    else {
        cout << 0 << endl;
    }
    /*for (int i = 0; i < Graph->Nv; i++) {
        for (int j = 0; j < Graph->Nv; j++) {
            cout << path[i][j] << '\t';
        }
        cout << endl;
    }*/



    /*Vertex* dist = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* path = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* collected = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    double* FirstStep = (double*)malloc(Graph->Nv * sizeof(double));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        dist[V] = Infinity;
        path[V] = -1;
        collected[V] = -1;
        FirstStep[V] = Infinity;
    }
    Vertex* dist2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* path2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* collected2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    double* FirstStep2 = (double*)malloc(Graph->Nv * sizeof(double));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        dist2[V] = Infinity;
        path2[V] = -1;
        collected2[V] = -1;
        FirstStep2[V] = Infinity;
    }*/



    /*int MinStep = Infinity;
    int MinP = -1;
    for (int i = 0; i < Graph->Nv; i++) {
        for (Vertex V = 0; V < Graph->Nv; V++) {
            dist[V] = Infinity;
            path[V] = -1;
            collected[V] = -1;
            FirstStep[V] = Infinity;
        }
        if ((50 - fabs(Input[i].X) <= D || 50 - fabs(Input[i].Y) <= D)) {
            Dijkstra(Graph, Input, path, dist, collected, FirstStep, D, i);
            if (dist[0] < MinStep) {
                MinStep = dist[0];
                MinP = i;
                for (Vertex V = 0; V < Graph->Nv; V++) {
                    dist2[V] = dist[V];
                    path2[V] = path[V];
                    collected2[V] = collected[V]; 
                }
            }
            else if (dist[0] == MinStep && CalD(Input[0],Input[path2[0]]) > CalD(Input[0],Input[path[0]])) {
                MinStep = dist[0];
                MinP = i;
                for (Vertex V = 0; V < Graph->Nv; V++) {
                    dist2[V] = dist[V];
                    path2[V] = path[V];
                    collected2[V] = collected[V];
                } 
            }
        }
    }
    if (MinStep != Infinity) {
        cout << MinStep + 1 << endl;
        int j = 0;
        while (path2[j] != -1) {
            cout << Input[path2[j]].X << ' ' << Input[path2[j]].Y << endl;
            j = path2[j];
        }
    }
    else {
        cout << 0 << endl;
    }*/
    
    return 0;
}

