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
    int Longest;
    int Delay;
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
        Graph->G[V].Longest = Infinity;
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
    Graph = CreateLG(Nv + 2);

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
int ShortestTime(LGraph Graph, Vertex* Indegree ,Stack S)
{
    Queue Q = CreateQ();
    for (Vertex V = 0; V < Graph->Nv; V++) {
        if (Indegree[V] == 0) {
            Q = InQueue(Q, V);
            S = Push(S, V);
            Indegree[V] = -1;
        }
    }
    while (!IsEmptyQ(Q)) {
        Vertex V = DeQueue(Q);
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Indegree[P->V2]--;
            if (Indegree[P->V2] == 0) {
                Q = InQueue(Q, P->V2);
                S = Push(S, P->V2);
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
void LongestTime(LGraph Graph,Stack S,Vertex* Outdegree,int i)
{
    int time = i;
    while (!IsEmptyS(S)) {
        Vertex V = Pop(S);
        if (Outdegree[V] == 0) {
            Graph->G[V].Longest = time;
        }
        else {
            for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
                if (Graph->G[V].Longest > Graph->G[P->V2].Longest - P->Weight) {
                    Graph->G[V].Longest = Graph->G[P->V2].Longest - P->Weight;
                }
            }
        }
    }

}
int main()
{
    LGraph Graph = BuildLG();
    Vertex* Indegree = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 1; V < Graph->Nv; V++) Indegree[V] = 0;
    Vertex* Outdegree = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 1; V < Graph->Nv; V++) Outdegree[V] = 0;
    for (Vertex V = 1; V < Graph->Nv - 1; V++) {
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Outdegree[V]++;
        }
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Indegree[P->V2]++;
        }
    }
    for (Vertex V = 1; V < Graph->Nv - 1; V++) {
        if (Indegree[V] == 0) {
            Edge E = (Edge)malloc(sizeof(struct ENode));
            E->V1 = 0;
            E->V2 = V;
            E->Weight = 0;
            InsertEdgeLG(Graph, E);
        }
    }
    for (Vertex V = 1; V < Graph->Nv - 1; V++) {
        if (Outdegree[V] == 0) {
            Edge E = (Edge)malloc(sizeof(struct ENode));
            E->V1 = V;
            E->V2 = Graph->Nv - 1;
            E->Weight = 0;
            InsertEdgeLG(Graph, E);
        }
    }
    for (Vertex V = 0; V < Graph->Nv; V++) Indegree[V] = 0;
    for (Vertex V = 0; V < Graph->Nv; V++) Outdegree[V] = 0;
    for (Vertex V = 0; V < Graph->Nv; V++) {
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Outdegree[V]++;
        }
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Indegree[P->V2]++;
        }
    }

    Stack S = CreateS();
    int r = ShortestTime(Graph, Indegree, S);
    for (Vertex V = 0; V < Graph->Nv; V++) Indegree[V] = 0;
    for (Vertex V = 0; V < Graph->Nv; V++) { 
        for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
            Indegree[P->V2]++;
        }
    }
    if (r == 1) {
        int shortest = 0;
        for (Vertex V = 0; V < Graph->Nv; V++) {
            if (Graph->G[V].Shortest > shortest) {
                shortest = Graph->G[V].Shortest;
            }
        }
        cout << shortest << endl;
    }
    LongestTime(Graph, S, Outdegree, Graph->G[Graph->Nv - 1].Shortest);
    if (r == 0) cout << 0 << endl;
    else {
        for (Vertex V = 0; V < Graph->Nv - 1; V++) {
            for (PtrToAdjVNode P = Graph->G[V].FirstEdge; P; P = P->Next) {
                if (Graph->G[P->V2].Shortest - Graph->G[P->V2].Longest == 0 && Graph->G[V].Shortest - Graph->G[V].Longest == 0 && Outdegree[P->V2] != 0 && Indegree[V] != 0
                    && Graph->G[P->V2].Shortest - Graph->G[V].Shortest == P->Weight) {
                    cout << V << "->" << P->V2 << endl;
                }
            }
        }
    }
    
    return 0;
}

