#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MaxVertex 100
#define Infinity 65535

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
void InsertEdge(LGraph Graph, Edge E)
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

/* Heap */
typedef Edge ElementofHeap;
typedef struct HNode* Heap;
struct HNode {
    ElementofHeap* Data;
    int Size;
    int MaxSize;
};
Heap CreateH()
{
    Heap H = new HNode;
    H->Data = new ElementofHeap[10001];
    H->Size = 0;
    H->MaxSize = 10000;
    return H;
}
int IsEmptyH(Heap H)
{
    if (H->Size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
Heap Push(Heap H, ElementofHeap X)
{
    H->Data[++H->Size] = X;
    int Child = H->Size;
    while (Child / 2 != 0 && H->Data[Child]->Weight < H->Data[Child / 2]->Weight) {
        ElementofHeap TEMP = H->Data[Child];
        H->Data[Child] = H->Data[Child / 2];
        H->Data[Child / 2] = TEMP;
        Child /= 2;
    }
    return H;
}
ElementofHeap Pop(Heap H)
{
    if (!IsEmptyH(H)) {
        ElementofHeap RET = H->Data[1];
        H->Data[1] = H->Data[H->Size--];
        int Parent = 1, Child;
        for (Parent; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && H->Data[Child]->Weight > H->Data[Child + 1]->Weight)
                Child += 1;
            if (H->Data[Parent]->Weight > H->Data[Child]->Weight) {
                ElementofHeap TEMP = H->Data[Parent];
                H->Data[Parent] = H->Data[Child];
                H->Data[Child] = TEMP;
            }
        }
        return RET;
    }
    else {
        return NULL;
    }
}
ElementofHeap Peap(Heap H)
{  
    return !IsEmptyH(H)? H->Data[1] : NULL;
}
LGraph BuildLG(Heap H)
{
    Vertex V, W;
    LGraph Graph;
    Edge E;

    int Nv;
    cin >> Nv;
    Graph = CreateLG(Nv);

    cin >> Graph->Ne;
    if (Graph->Ne) {
        for (V = 0; V < Graph->Ne; V++) {
            E = (Edge)malloc(sizeof(struct ENode));
            Vertex v1, v2;
            cin >> v1;
            cin >> v2;
            E->V1 = v1 - 1;
            E->V2 = v2 - 1;
            cin >> E->Weight;
            InsertEdge(Graph, E);
            H = Push(H, E);
        }
    }
    return Graph;
}
int FindSet(Vertex* set, Vertex V)
{
    int i = V;
    while (set[i] >= 0) {
        i = set[i];
    }
    if (i != V) {
        set[V] = i;
        set[i]--;
    }
    return i;
}
void Union(Vertex* set, Vertex V, Vertex W)
{
    int X = FindSet(set, V);
    int Y = FindSet(set, W);
    if (set[X] < set[Y]) {
        set[X] += set[Y];
        set[Y] = X;
    }
    else {
        set[Y] = set[X];
        set[X] = Y;
    }
}
int CheckCircle(Vertex* set, Vertex V, Vertex W)
{
    if (FindSet(set, V) == FindSet(set, W)) return 1;
    else return 0;
}
int Kruskal(LGraph MST, Vertex* set, Heap H)
{
    int Total = 0, Count = 0;
    while (!IsEmptyH(H)) {
        Edge E = Pop(H);
        if (!CheckCircle(set, E->V1, E->V2)) {
            InsertEdge(MST, E);
            Union(set, E->V1, E->V2);
            Total += E->Weight;
            Count++;
        }
    }
    if (Count == MST->Nv - 1) return Total;
    else return -1;
}

int main()
{   
    Heap H = CreateH();
    LGraph Graph = BuildLG(H);
    LGraph MST = CreateLG(Graph->Nv);
    Vertex* set = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) set[V] = -1;
    int K = Kruskal(MST, set, H);
    cout << K;
    return 0;
}

