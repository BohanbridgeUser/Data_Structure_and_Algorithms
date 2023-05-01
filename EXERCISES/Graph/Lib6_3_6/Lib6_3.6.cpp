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
    int Use;
    int Use2;
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
    H->Data = new ElementofHeap[10000000];
    H->Size = 0;
    H->MaxSize = 10000000;
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
    if (X) {
        int i = ++H->Size;
        for (; i / 2 > 0 && H->Data[i / 2]->Weight > X->Weight; i /= 2) {
            H->Data[i] = H->Data[i / 2];
        }
        H->Data[i] = X;
        return H;
    }
    else {
        return H;
    }
       
}
ElementofHeap Pop(Heap H)
{
    if (!IsEmptyH(H)) {
        ElementofHeap RET = H->Data[1];
        ElementofHeap X = H->Data[H->Size--];
        int Parent = 1, Child;
        for (Parent; Parent * 2 <= H->Size; Parent = Child) {
            Child = Parent * 2;
            if (Child + 1 <= H->Size && H->Data[Child]->Weight > H->Data[Child + 1]->Weight)
                Child += 1;
            if (X->Weight < H->Data[Child]->Weight) break;
            else H->Data[Parent] = H->Data[Child];
        }
        H->Data[Parent] = X;
        return RET;
    }
    else {
        return NULL;
    }
}
ElementofHeap Peap(Heap H)
{
    return !IsEmptyH(H) ? H->Data[1] : NULL;
}
MGraph BuildLG(Heap H)
{
    Vertex V, W;
    MGraph Graph;
    Edge E;

    int Nv;
    cin >> Nv;
    Graph = CreateMG(Nv);

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
            E->Use = 0;
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
    if (i != V && set[i] < 0) {
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
int CheckSet(Vertex* set,int N)
{
    int beg = FindSet(set, 0);
    int i;
    for (i = 0; i < N; i++) {
        if (FindSet(set, i) != beg) break;
    }
    if (i == N)return 1;
    else return 0;
}
int Kruskal(MGraph MST, Vertex* set, Heap H,Heap H2)
{
    int Total = 0, Count = 0;
    while (!IsEmptyH(H)) {
        Edge E = Pop(H);
        H2 = Push(H2, E);
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

/* Queue */
typedef Edge ElementofQueue;
typedef struct QNode* PtrToQNode;
struct QNode {
    ElementofQueue Data;
    PtrToQNode Next;
};
struct Que {
    PtrToQNode Head;
    PtrToQNode Rear;
    PtrToQNode View;
};
typedef struct Que* Queue;

Queue CreateQ()
{
    Queue Q = (Queue)malloc(sizeof(struct Que));
    Q->Head = (PtrToQNode)malloc(sizeof(struct QNode));
    Q->Rear = Q->Head;
    Q->Head->Next = NULL;
    Q->View = Q->Head;
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
ElementofQueue ViewQ(Queue Q)
{
    ElementofQueue ret;
    if (Q->View->Next) {
        ret = Q->View->Next->Data;
        Q->View = Q->View->Next;
        return ret;
    }
    else {
        return NULL;
    }
}
void InitialView(Queue Q)
{
    Q->View = Q->Head;
}
int Kruskal2(MGraph Graph, Vertex* set,Vertex* cset, Heap H ,int N,int min,int total,int* p)
{
    if (!N) {
        if (total == min && CheckSet(set,Graph->Nv) == 1) {
            *p += 1;
            return 1;
        }
        else return -1;
    }
    else {
        Queue Q = CreateQ();
        Edge E;
        if (!IsEmptyH(H)) {
            E = Pop(H);
            Q = InQueue(Q, E);
        }
        else {
            return -1;
        }

        int crt = -1;
        while(!IsEmptyH(H) && Peap(H)->Weight == E->Weight) {
            for (Vertex i = 0; i < Graph->Nv; i++) cset[i] = set[i];
            if (!CheckCircle(set, E->V1, E->V2)) {
                Union(set, E->V1, E->V2);
                crt = Kruskal2(Graph, set,cset ,H, N - 1, min, total + E->Weight, p);
                for (Vertex i = 0; i < Graph->Nv; i++) set[i] = cset[i];
                if (crt == 1 && *p == 2) return 1;
            }
            E = Pop(H);
            Q = InQueue(Q, E);
        }
        
        if (crt == 1 && *p == 2) return 1;
        for (Vertex i = 0; i < Graph->Nv; i++) cset[i] = set[i];
        if (!CheckCircle(set, E->V1, E->V2)) {
            Union(set, E->V1, E->V2);
            int crt = Kruskal2(Graph, set,cset, H, N - 1, min, total + E->Weight, p);
            for (Vertex i = 0; i < Graph->Nv; i++) set[i] = cset[i];
            if (crt == 1 && *p == 2) return 1;
        }
        E = Pop(H);
        Q = InQueue(Q, E);

        while (!IsEmptyQ(Q)) {
            H = Push(H, DeQueue(Q));
        }
        return -1;
    }
}
/* DFS */
void Visit(Vertex* visit, Vertex V)
{
    visit[V] = 1;
}
void DFS_Recursion(MGraph Graph, Vertex* visit, Vertex V)
{
    Visit(visit, V);
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity && visit[W] == -1) {
            DFS_Recursion(Graph, visit, W);
        }
    }
}

int main()
{
    Heap H = CreateH();
    Heap H2 = CreateH();
    MGraph Graph = BuildLG(H);
    MGraph MST = CreateMG(Graph->Nv);
    Vertex* set = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) set[V] = -1;
    int K = Kruskal(MST, set, H , H2);
    if (K == -1) {
        int crt = 1,cnt = 0;
        Vertex* visit = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
        for (Vertex W = 0; W < Graph->Nv; W++) visit[W] = -1;
        int W = 0;
        while (crt == 1) {
            while (W < Graph->Nv && visit[W] != -1) {
                W++;
            }
            if (W == Graph->Nv) {
                crt = 0;
            }
            else {
                DFS_Recursion(Graph, visit, W);
                cnt++;
            }
        }
        cout << "No MST\n";
        cout << cnt;
    }
    else {
        cout << K << endl;
        int total = 0;
        if (Graph ->Nv == 1) {
            cout << "Yes\n";
            return 0;
        }
        for (Vertex V = 0; V < Graph->Nv; V++) set[V] = -1;
        int p = 0;
        Vertex* cset = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
        for (Vertex V = 0; V < Graph->Nv; V++) cset[V] = -1;
        if (Kruskal2(Graph, set,cset, H2, Graph->Nv - 1, K, total,&p) == -1) cout << "Yes\n";
        else cout << "No\n";
    }
     return 0;
}




//#include<iostream>
//#include<algorithm>
//#include<unordered_map>
//#include<cstring>
//
//using namespace std;
//
//const int N = 510;
//unordered_map<int, int> fa;
//int n, m;
//int p[N];
//
//struct Edge
//{
//    int a, b, c;
//    bool operator < (const Edge& w) const
//    {
//        return c < w.c;
//    }
//}edge[N * N];
//
//bool st[N]; //判断边是否被用到了
//int g[N];
//
//int find(int x)//并查集+路径压缩
//{
//    if (p[x] != x) p[x] = find(p[x]);
//    return p[x];
//}
//
//int main()
//{
//    cin >> n >> m;
//    if (n == 1) {
//        cout << 0 << endl;
//        cout << "Yes\n";
//        return 0;
//    }
//    for (int i = 0; i < m; i++)
//    {
//        int a, b, c;
//        cin >> a >> b >> c;
//        edge[i] = { a, b, c };
//    }
//    sort(edge, edge + m);
//    int cnt = 0; //记录合并次数
//    long long res = 0; //记录结果
//    for (int i = 1; i <= n; i++) p[i] = i; //并查集初始化
//
//    for (int i = 0; i < m; i++)
//    {
//        auto t = edge[i];
//        int x = find(t.a), y = find(t.b);
//        if (x != y) //集合不一样就合并
//        {
//            cnt++; //合并次数++
//            st[i] = true; //边被使用了
//            p[x] = y; //合并集合
//            res += t.c;
//            g[t.a] = g[t.b] = t.c; //记录边长，为后面判断生成树是否唯一服务
//        }
//    }
//
//    if (cnt < n - 1) //合并次数 < n - 1说明不连通。（一开始1个点，一直加入加入...到n个点需要n - 1次）
//    {
//        for (int i = 1; i <= n; i++)
//        {
//            int t = find(i);
//            if (!fa[t]) fa[t] = 1; //统计祖宗，放入map
//        }
//        cout << "No MST" << endl;
//        cout << fa.size() << endl;//祖宗个数
//        return 0;
//    }
//    cout << res << endl;
//
//    for (int i = 0; i < n; i++)
//    {
//        if (!st[i]) // 边没用过
//        {
//            auto t = edge[i];
//            int a = t.a, b = t.b; //边连的两个点
//            if (res - g[a] + t.c == res) //结果相同则生成树不唯一
//            {
//                puts("No");
//                return 0;
//            }
//        }
//    }
//    cout << "Yes" << endl;
//    return 0;
//}