#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>

using namespace std;

#define MaxVertex 100
#define Infinity 65535

typedef int Vertex;
typedef int WeightType;
typedef struct Data DataType;
struct Data {
    char* City;
    int Num;
};

/* GNode */
typedef struct MGNode* PtrToMGNode;
struct MGNode {
    int Nv;
    int Ne;
    Vertex** G;
    DataType* Data;
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
    Graph->G = (Vertex**)malloc(Graph->Nv * sizeof(int*));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        Graph->G[V] = (int*)malloc(Graph->Nv * sizeof(int));
    }

    for (Vertex V = 0; V < VertexNum; V++) {
        for (Vertex W = 0; W < VertexNum; W++) {
            Graph->G[V][W] = Infinity;
        }
    }

    Graph->Data = (DataType*)malloc(Graph->Nv * sizeof(DataType));

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMG(int Nv, int Ne,int* homei,int* targeti, char* home, char* target)
{
    MGraph Graph;
    Vertex V, W;
    Edge E;

    Graph = CreateMG(Nv);
    for (V = 1; V < Graph->Nv; V++) {
        char* name = (char*)malloc(4 * sizeof(char));
        memset(name, '\0', 4);
        int Num = 0;
        scanf("%s %d\n", name, &Num);
        DataType x = { name,Num };
        Graph->Data[V] = x;
        if (strcmp(name, target) == 0) *targeti = V;
    }
    Graph->Data[0] = { home,0 };
    *homei = 0;
    Graph->Ne = Ne;
    if (Graph->Ne) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->Ne; i++) {
            char* name1, * name2;
            name1 = (char*)malloc(4 * sizeof(char));
            memset(name1, '\0', 4);
            name2 = (char*)malloc(4 * sizeof(char));
            memset(name2, '\0', 4);
            scanf("%s %s %d", name1, name2, &E->Weight);
            getchar();
            int v1, v2;
            int j = 0, crt = 0;;
            for (; j < Graph->Nv; j++) {
                if (strcmp(name1, Graph->Data[j].City) == 0) {
                    v1 = j;
                    crt++;
                }
                else if (strcmp(name2, Graph->Data[j].City) == 0) {
                    v2 = j;
                    crt++;
                }
                if (crt == 2) break;
            }
            E->V1 = v1;
            E->V2 = v2;
            InsertEdge(Graph, E);
            free(name1);
            free(name2);
        }
    }
    
    return Graph;
}
int FindMinDist(MGraph Graph, Vertex* dist, Vertex* collected,Vertex* cityn,Vertex* enermy)
{
    int MinDist = Infinity;
    int MaxCity = 0;
    int MaxEnermy = 0;
    int MinV = -1;
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (dist[W] < MinDist && dist[W] != 0 && collected[W] == -1) {
            MinDist = dist[W];
            MaxCity = cityn[W];
            MaxEnermy = enermy[W];
            MinV = W;
        }
        else if (dist[W] == MinDist && dist[W] != 0 && collected[W] == -1) {
            if (cityn[W] > MaxCity) {
                MinDist = dist[W];
                MaxCity = cityn[W];
                MaxEnermy = enermy[W];
                MinV = W;
            }
            else if (cityn[W] == MaxCity) {
                if (enermy[W] > MaxEnermy) {
                    MinDist = dist[W];
                    MaxCity = cityn[W];
                    MaxEnermy = enermy[W];
                    MinV = W;
                }
            }
        }
    }
    return MinV;
}
void Dijkstra(MGraph Graph, Vertex* path, Vertex* dist, Vertex* collected,Vertex* cityn, Vertex* enermy,Vertex* count, Vertex V)
{
    for (Vertex W = 0; W < Graph->Nv; W++) {
        if (Graph->G[V][W] != Infinity) {
            dist[W] = Graph->G[V][W];
            cityn[W] = cityn[V] + 1;
            enermy[W] = enermy[V] + Graph->Data[W].Num;
            count[W] = 1;
        }
    }
    dist[V] = 0;
    path[V] = -1;
    collected[V] = 1;
    while (1) {
        Vertex P = FindMinDist(Graph, dist, collected, cityn,enermy);
        //printf("p = %d\n", P);
        if (P == -1) break;
        collected[P] = 1;
        for (Vertex W = 0; W < Graph->Nv; W++) {
            if (Graph->G[P][W] + dist[P] < dist[W] && collected[W] == -1) {
                dist[W] = Graph->G[P][W] + dist[P];
                path[W] = P;
                cityn[W] = cityn[P] + 1;
                enermy[W] = enermy[P] + Graph->Data[W].Num;
                count[W] = count[P];
            }
            else if (Graph->G[P][W] + dist[P] == dist[W] && collected[W] == -1) {
                count[W] += count[P];
                if (cityn[W] < cityn[P] + 1) {
                    dist[W] = Graph->G[P][W] + dist[P];
                    path[W] = P;
                    cityn[W] = cityn[P] + 1;
                    enermy[W] = enermy[P] + Graph->Data[W].Num;
                }
                else if (cityn[W] == cityn[P] + 1) {
                    if (enermy[W] < enermy[P] + Graph->Data[W].Num) {
                        dist[W] = Graph->G[P][W] + dist[P];
                        path[W] = P;
                        cityn[W] = cityn[P] + 1;
                        enermy[W] = enermy[P] + Graph->Data[W].Num;
                    }
                }
            }
        }
    }
}
int main()
{
    int N, K;
    char* home, *target;
    home = (char*)malloc(4 * sizeof(char));
    memset(home, '\0', 4);
    target = (char*)malloc(4 * sizeof(char));
    memset(target, '\0', 4);
    scanf("%d %d %s %s\n", &N, &K, home, target);
    int homei, targeti;
    MGraph Graph = BuildMG(N,K,&homei,&targeti,home,target);
    Vertex* dist = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* path = (Vertex*)malloc(Graph->Nv * (sizeof(Vertex)));
    Vertex* collected = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* cityn = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* enermy = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    Vertex* count = (Vertex*)malloc(Graph->Nv * sizeof(Vertex));
    for (Vertex V = 0; V < Graph->Nv; V++) {
        collected[V] = -1;
        dist[V] = Infinity;
        path[V] = 0;
        cityn[V] = 0;
        enermy[V] = 0;
        count[V] = 0;
    }

    Dijkstra(Graph, path, dist, collected,cityn,enermy,count ,0);
    int j = targeti;
    int* tmp = (int*)malloc(Graph->Nv * sizeof(int));
    int i = 0;
    while (path[j] != -1) {
        tmp[i++] = path[j];
        j = path[j];
    }
    for (i = i - 1; i > -1; i--) {
        printf("%s->", Graph->Data[tmp[i]].City);
    }
    printf("%s\n", Graph->Data[targeti].City);
    printf("%d %d %d", count[targeti], dist[targeti], enermy[targeti]);
    return 0;
}
