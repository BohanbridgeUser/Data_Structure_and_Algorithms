#include<stdio.h>
#include<stdlib.h> 
#include<stdbool.h>

/* Queue Define */
typedef int ElementType;

typedef struct QNode* PtrToQNode;
struct QNode{
	ElementType Data;
	PtrToQNode Next;
};
typedef struct Que* Queue;
struct Que{
	PtrToQNode Head;
	PtrToQNode Rear;
	int Size;
};

Queue CreateQ()
{
	Queue Q = (Queue)malloc(sizeof(struct Que));
	Q->Head = (PtrToQNode)malloc(sizeof(struct QNode));
	Q->Head->Next = NULL;
	Q->Rear = Q->Head;
	Q->Size = 0;
	return Q;
}
void InQueue( Queue Q, ElementType X )
{
	PtrToQNode NewNode  = (PtrToQNode)malloc(sizeof(struct QNode));
	NewNode->Data = X;
	NewNode->Next = NULL;
	Q->Rear->Next = NewNode;
	Q->Rear = Q->Rear->Next;
	Q->Size++;
}
bool IsEmptyQ( Queue Q )
{
	if( Q->Head == Q->Rear ){
		return true;
	}else{
		return false;
	}
}
ElementType DeQueue( Queue Q )
{
	if( IsEmptyQ( Q ) ) return -1;
	else{
		ElementType RET = Q->Head->Next->Data;
		PtrToQNode TEMP = Q->Head->Next;
		if(Q->Head->Next->Next){
			Q->Head->Next = Q->Head->Next->Next;
		}else{
			Q->Head->Next = NULL;
			Q->Rear = Q->Head;
		}
		free(TEMP);
		Q->Size--;
		return RET;
	}
}
/* Queue Define End */

/* MFun Define */
void MFun()
{
	int x = 0, N;
	int* In = (int*)malloc(1001*sizeof(int));
	int F, j = 0, M, gc;
	while( (F=scanf("%d", &M)) == 1 ) { 
		if ( x == 0 ) N = M, x++;
		else{
			In[j++] = M;
		}
		if( (gc=getchar()) == '\n' ) break;
	}
	
	Queue QA = CreateQ();
	Queue QB = CreateQ();
	int i;
	for(i=0;i<N;i++){
		if( In[i] == 1 ){
			InQueue( QA, In[i] );
		}else if( In[i] % 2 !=0 ){
			InQueue( QA, In[i] );
		}else if( In[i] % 2 == 0 ){
			InQueue( QB, In[i] );
		}
	}
	
	int CNTA = 0;
	if( !IsEmptyQ( QA ) ){
		printf("%d",DeQueue(QA));
		CNTA++;
	}
	if( IsEmptyQ(QA) && !IsEmptyQ(QB) ){
		printf("%d",DeQueue(QB));
	}
	while( !IsEmptyQ(QA) && !IsEmptyQ(QB) ){
		printf(" %d",DeQueue(QA));
		printf(" %d",DeQueue(QB));
		if( !IsEmptyQ(QA) ) printf(" %d",DeQueue(QA));
	}
	while( !IsEmptyQ(QB) ) printf(" %d",DeQueue(QB));
	while( !IsEmptyQ(QA) ) printf(" %d",DeQueue(QA));
	return;
}

int main(int agc,const char* agv[])
{
	MFun();
	return 0;
}

