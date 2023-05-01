#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
    int Shortest;
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

    for (Vertex V = 0; V < Graph->Nv; V++) {
        Graph->G[V].FirstEdge = NULL;
        Graph->G[V].Shortest = 0;
    }
    return Graph;
}

void InsertEdgeLG(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->V2 = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    /*NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->V2 = E->V1;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;*/
}

LGraph BuildLG()
{
    Vertex V, W;
    LGraph Graph;
    Edge E;

    int Nv;
    cin >> Nv;
    Graph = CreateLG(Nv);

    cin >> Graph->Ne;
    if (Graph->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (V = 0; V < Graph->Ne; V++) {
            int v1, v2;
            cin >> v1;
            cin >> v2;
            cin >> E->Weight;
            E->V1 = v1;
            E->V2 = v2;
            InsertEdgeLG(Graph, E);
        }
    }

    return Graph;
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
int ShortestTime(LGraph Graph, Vertex* Indegree)
{
    Queue Q = CreateQ();
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (Indegree[V] == 0) {
            Q = InQueue(Q, V);
            Indegree[V] = -1;
        }
    }
    while (!IsEmptyQ(Q)) {
        Vertex V = DeQueue(Q);
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Indegree[P->V2]--;
            if (Indegree[P->V2] == 0) {
                Q = InQueue(Q, P->V2);
                Indegree[P->V2] = -1;
            }
            if (Graph->G[P->V2].Shortest < Graph->G[V].Shortest + P->Weight) {
                Graph->G[P->V2].Shortest = Graph->G[V].Shortest + P->Weight;
            }
        }
    }
    int crt = 1;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (Indegree[V] != -1) {
            crt = 0;
            break;
        }
    }
    return crt;
}
int main()
{
    LGraph Graph = BuildLG();
    Vertex* Indegree = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) Indegree[V] = 0;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P;P=P->Next) {
            Indegree[P->V2]++;
        }
    }
    if (ShortestTime(Graph, Indegree) == 1) {
        int shortest = 0;
        for (Vertex V = 0; V < Graph->Nv; V++) {
            if (Graph->G[V].Shortest > shortest) {
                shortest = Graph->G[V].Shortest;
            }
        }
        cout << shortest << endl;
    }
    else cout << "Impossible" << endl;
    return 0;
}

