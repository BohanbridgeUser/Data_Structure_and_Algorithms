#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* �洢������� */
    PtrToNode   Next; /* ָ����һ������ָ�� */
};
typedef PtrToNode List; /* ���嵥�������� */

void K_Reverse( List L, int K )
{
	PtrToNode Head, Rear;
	Head = L;
	Rear = L->Next;
	while( Rear ){
		PtrToNode* P = (PtrToNode*)malloc(K*sizeof(PtrToNode));
		int cnt,i = 0;
		for( cnt=0; cnt<K && Rear; cnt++ ){
			P[i++] = Rear;
			Rear = Rear->Next;
		}
		if ( cnt == K ){
			Head->Next = P[i-1];
			Head = P[0];
			P[i-K]->Next = Rear->Next;
			for(cnt-=1;cnt>0;cnt--){
				P[i-cnt]->Next = P[i-cnt-1];
			}
		}
		free(P);
	}
}

int main(int agc,const char* agv[])
{

	return 0;
}

