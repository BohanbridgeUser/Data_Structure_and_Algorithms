#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

PtrToNode Suffix( List L1, List L2 )
{
	PtrToNode* P1 = (PtrToNode*)malloc(100000*sizeof(PtrToNode));
	PtrToNode* P2 = (PtrToNode*)malloc(100000*sizeof(PtrToNode));
	PtrToNode Q1 = L1;
	PtrToNode Q2 = L2;
	int p1 = 0, p2 = 0;
	while( Q1->Next ) {
		P1[p1++] = Q1->Next;
		Q1 = Q1->Next;
	}
	while( Q2->Next ) {
		P2[p2++] = Q2->Next;
		Q2 = Q2->Next;
	}
	for(;P1[p1] == P2[p2] && p1>-1 && p2 > -1;p1--,p2--);
	PtrToNode RET;
	p1 += 1;
	RET = P1[p1];
	free(P1);
	free(P2);
	return RET;
}

int main(int agc,const char* agv[])
{

	return 0;
}

