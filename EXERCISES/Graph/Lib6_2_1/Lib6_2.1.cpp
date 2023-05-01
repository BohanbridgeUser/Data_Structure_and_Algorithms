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
void DFS(MGraph Graph, Vertex* visit, Vertex* out,int* i, Vertex V)
{
    Visit(visit, V);
    out[*i] = V;
    (*i)++;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity && visit[W] == -1) {
            DFS(Graph, visit, out, i, W);
        }
    }
}
int IsEmptyVisit(MGraph Graph,Vertex* visit)
{
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (visit[V] == -1) return 0;
    }
    return 1;
}
/* Queue */
typedef Vertex ElementofQueue;
typedef struct QNode* PtrToQNode;
struct QNode {
    ElementofQueue Data;
    PtrToQNode Next;
};
struct Que {
    PtrToQNode Head;
    PtrToQNode Rear;
};
typedef struct Que* Queue;

Queue CreateQ()
{
    Queue Q = (Queue)malloc(sizeof(struct Que));
    Q->Head = (PtrToQNode)malloc(sizeof(struct QNode));
    Q->Rear = Q->Head;
    Q->Head->Next = NULL;
    return Q;
}
int IsEmptyQ(Queue Q)
{
    if (!Q->Head->Next) return 1;
    else return 0;
}
Queue InQueue(Queue Q, ElementofQueue X)
{
    PtrToQNode NewNode = (PtrToQNode)malloc(sizeof(struct QNode));
    NewNode->Data = X;
    NewNode->Next = Q->Rear->Next;
    Q->Rear->Next = NewNode;
    Q->Rear = Q->Rear->Next;
    return Q;
}
ElementofQueue DeQueue(Queue Q)
{
    if (!IsEmptyQ(Q)) {
        ElementofQueue ret = Q->Head->Next->Data;
        PtrToQNode TEMP = Q->Head->Next;
        if (!Q->Head->Next->Next) {
            Q->Head->Next = NULL;
            Q->Rear = Q->Head;
            free(TEMP);
            return ret;
        }
        else {
            Q->Head->Next = Q->Head->Next->Next;
            free(TEMP);
            return ret;
        }
    }
}
void BFS(MGraph Graph, Vertex* visit, Vertex* out, int i, Vertex V) 
{
    Queue Q = CreateQ();
    Q = InQueue(Q, V);
    Visit(visit, V);
    while (!IsEmptyQ(Q)) {
        Vertex W = DeQueue(Q);
        out[i++] = W;
        for (Vertex X = 0; X < Graph->Nv; X++) {
            if (Graph->G[W][X] != Infinity && visit[X] == -1) {
                Q = InQueue(Q, X);
                Visit(visit, X);
            }
        }
    }
}
int main()
{
    MGraph Graph = BuildMG();
    Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) visit[V] = -1;
    Vertex* out = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    while(!IsEmptyVisit(Graph, visit)) {
        for (Vertex W = 0; W < Graph->Nv;W++) out[W] = -1;
        Vertex V = 0;
        while (visit[V] != -1) V++;
        int i = 0;
        DFS(Graph, visit, out, &i, V);
        cout << "{ ";
        for (Vertex W = 0; out[W] != -1 && W < Graph->Nv; W++) cout << out[W] << ' ';
        cout << '}'<< endl;
    }
    for (Vertex V = 0; V < Graph->Nv; V++) visit[V] = -1;
    while (!IsEmptyVisit(Graph, visit)) {
        for (Vertex W = 0; W < Graph->Nv; W++) out[W] = -1;
        Vertex V = 0;
        while (visit[V] != -1) V++;
        int i = 0;
        BFS(Graph, visit, out, i, V);
        cout << "{ ";
        for (Vertex W = 0; out[W] != -1 && W <Graph->Nv; W++) cout << out[W] << ' ';
        cout << "}" << endl;
    }
    return 0;
}

