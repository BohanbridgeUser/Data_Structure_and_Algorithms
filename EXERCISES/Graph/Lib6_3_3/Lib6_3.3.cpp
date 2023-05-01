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
    Vertex GL[MaxVertex][MaxVertex];
    Vertex GT[MaxVertex][MaxVertex];
    DataType Data[MaxVertex];
};
typedef PtrToMGNode MGraph;

/* ENode */
typedef struct ENode* PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType WLen;
    WeightType WTime;
};
typedef PtrToENode Edge;

MGraph CreateMG(Vertex VertexNum)
{
    MGraph Graph = (MGraph)malloc(sizeof(struct MGNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (Vertex V = 0; V < VertexNum; V++) {
        for (Vertex W = 0; W < VertexNum; W++) {
            Graph->GL[V][W] = Infinity;
            Graph->GT[V][W] = Infinity;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->GL[E->V1][E->V2] = E->WLen;
    Graph->GT[E->V1][E->V2] = E->WTime;
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
            int dir;
            cin >> dir;
            cin >> E->WLen;
            cin >> E->WTime;
            if(dir == 1) InsertEdge(Graph, E);
            else {
                InsertEdge(Graph, E);
                WeightType tmp = E->V1;
                E->V1 = E->V2;
                E->V2 = tmp;
                InsertEdge(Graph, E);
            }
        }
    }
    return Graph;
}
int FindMinDist(MGraph Graph, Vertex* time, Vertex* dist, Vertex* count, Vertex* collected)
{
    int MinTime = Infinity;
    int MinDist = Infinity;
    int cnt = Infinity;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (time[W] < MinTime && time[W] != 0 && dist[W] != 0 && collected[W] == -1) {
            MinTime = time[W];
            MinDist = dist[W];
            cnt = count[W];
            MinV = W;
        }
        else if (time[W] == MinTime && time[W] != 0 && dist[W] != 0 && collected[W] == -1 && dist[W] < MinDist ) {
            MinTime = time[W];
            MinDist = dist[W];
            cnt = count[W];
            MinV = W;
        }
        else if (time[W] == MinTime && time[W] != 0 && dist[W] != 0 && collected[W] == -1 && dist[W] == MinDist && count[W] < cnt) {
            MinTime = time[W];
            MinDist = dist[W];
            cnt = count[W];
            MinV = W;
        }
    }
    return MinV;
}
void Dijkstra_Time(MGraph Graph, Vertex* path, Vertex* time, Vertex* collected,Vertex* dist,Vertex* count, Vertex V)
{
    time[V] = 0;
    dist[V] = 0;
    count[V] = 1;

    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->GT[V][W] != Infinity) {
            time[W] = Graph->GT[V][W];
            dist[W] = Graph->GL[V][W];
            count[W] = count[V] + 1;
        }
    }
    
    path[V] = -1;
    collected[V] = 1;

    int cnt = 0;
    while (1) {
        Vertex P = FindMinDist(Graph, time,dist,count, collected);
        if (P == -1) break;
        collected[P] = 1;
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (Graph->GT[P][W] + time[P] < time[W] && collected[W] == -1) {
                time[W] = Graph->GT[P][W] + time[P];
                dist[W] = Graph->GL[P][W] + dist[P];
                count[W] = count[P] + 1;
                path[W] = P;
            }
            else if (Graph->GT[P][W] + time[P] == time[W] && collected[W] == -1 && Graph->GL[P][W]+dist[P] < dist[W]) {
                time[W] = Graph->GT[P][W] + time[P];
                dist[W] = Graph->GL[P][W] + dist[P];
                count[W] = count[P] + 1;
                path[W] = P;
            }
            else if (Graph->GT[P][W] + time[P] == time[W] && collected[W] == -1 && Graph->GL[P][W] + dist[P] == dist[W] && count[W] > count[P] + 1) {
                time[W] = Graph->GT[P][W] + time[P];
                dist[W] = Graph->GL[P][W] + dist[P];
                count[W] = count[P] + 1;
                path[W] = P;
            }
        }
        cnt++;
    }
}
int FindMinDist2(MGraph Graph, Vertex* dist, Vertex* count, Vertex* collected)
{
    int MinDist = Infinity;
    int cnt = Infinity;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (dist[W] < MinDist && dist[W] != 0 && collected[W] == -1) {
            MinDist = dist[W];
            cnt = count[W];
            MinV = W;
        }
        else if (dist[W] == MinDist && dist[W] != 0 && collected[W] == -1 &&count[W] < cnt) {
            MinDist = dist[W];
            cnt = count[W];
            MinV = W;
        }
    }
    return MinV;
}
void Dijkstra_Length(MGraph Graph, Vertex* path, Vertex* collected, Vertex* dist, Vertex* count, Vertex V)
{
    dist[V] = 0;
    count[V] = 1;
    path[V] = -1;
    collected[V] = 1;
    
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->GL[V][W] != Infinity) {
            dist[W] = Graph->GL[V][W];
            count[W] = count[V] + 1;
        }
    }
    
    int cnt = 0;
    while (1) {
        Vertex P = FindMinDist2(Graph, dist, count, collected);
        if (P == -1) break;
        collected[P] = 1;
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (Graph->GL[P][W] + dist[P] < dist[W] && collected[W] == -1) {
                dist[W] = Graph->GL[P][W] + dist[P];
                count[W] = count[P] + 1;
                path[W] = P;
            }
            else if (Graph->GL[P][W] + dist[P] == dist[W] && collected[W] == -1 && count[W] > count[P] + 1) {
                dist[W] = Graph->GL[P][W] + dist[P];
                count[W] = count[P] + 1;
                path[W] = P;
            }
        }
        cnt++;
    }
}
int main()
{
    MGraph Graph = BuildMG();
    Vertex* time = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* path = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* collected = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* dist = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* count = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        time[V] = Infinity;
        path[V] = -1;
        collected[V] = -1;
        dist[V] = Infinity;
        count[V] = 0;
    }

    int beg, end;
    cin >> beg;
    cin >> end;
    Dijkstra_Time(Graph, path, time, collected, dist, count, beg);

    Vertex* path2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* collected2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* dist2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* count2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        path2[V] = -1;
        collected2[V] = -1;
        dist2[V] = Infinity;
        count2[V] = 0;
    }
    Dijkstra_Length(Graph, path2, collected2, dist2, count2, beg);
    int same = 1;
    int i = end;
    while (path2[i] != -1) {
        if (path[i] != path2[i]) {
            same = 0;
            break;
        }
        i = path2[i];
    }

    if (same == 0) {
        cout << "Time = " << time[end] << ": ";
        cout << beg;
        i = end;
        int j = 0, cnt = 0;
        Vertex* out = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
        while (path[i] != -1) {
            out[j++] = path[i];
            i = path[i];
            cnt++;
        }
        for (int k = cnt - 1; k > -1; k--) cout << " => " << out[k];
        cout << " => " << end << endl;

        cout << "Distance = " << dist2[end] << ": ";
        cout << beg;
        i = end;
        j = 0, cnt = 0;
        Vertex* out2 = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
        while (path2[i] != -1) {
            out2[j++] = path2[i];
            i = path2[i];
            cnt++;
        }
        for (int k = cnt - 1; k > -1; k--) cout << " => " << out2[k];
        cout << " => " << end << endl;
    }
    else {
        cout << "Time = " << time[end] << "; ";
        cout << "Distance = " << dist2[end] << ": ";
        cout << beg;
        i = end;
        int j = 0, cnt = 0;
        Vertex* out = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
        while (path[i] != -1) {
            out[j++] = path[i];
            i = path[i];
            cnt++;
        }
        for (int k = cnt - 1; k > -1; k--) cout << " => " << out[k];
        cout << " => " << end << endl;
    }
    
    return 0;
}
