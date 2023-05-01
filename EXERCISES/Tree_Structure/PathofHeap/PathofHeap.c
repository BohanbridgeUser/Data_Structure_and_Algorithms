#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 1001
#define SENTRY -10001

typedef struct HNode* Heap;
struct HNode{
	int* Data;
	int Size;
	int Capacity;
};
typedef Heap MinHeap;

bool IsFull( Heap H ); 
Heap AddH( Heap H, int X );
int DeleteH( Heap H );
bool IsEmpty( Heap H );

int main(int agc,const char* agv[])
{
	int N, M;
	scanf(" %d %d",&N,&M);
	
	Heap H = NULL;
	int i;
	for(i=1;i<=N;i++){
		int temp;
		scanf(" %d",&temp);
		H = AddH( H, temp );
	}
	for(i=0;i<M;i++){
		int temp;
		scanf(" %d",&temp);
		int j;
		for(j=temp;j>1;j/=2){
			printf("%d ",H->Data[j]);
		}
		printf("%d\n",H->Data[1]);
	}
	return 0;
}

Heap AddH( Heap H, int X )
{
	if ( IsFull( H ) ) {
		printf("FULL HEAP\n");
		return H;
	}
	if ( !H ){
		H = (Heap)malloc(sizeof(struct HNode));
		H->Data = (int*)malloc(MAXSIZE*sizeof(int));
		H->Data[1] = X;
		H->Size = 1;
		H->Capacity = MAXSIZE - 1;
		H->Data[0] = SENTRY; 
	}else{
		int i = ++H->Size;
		for(; X < H->Data[i/2];i/=2){
			H->Data[i] = H->Data[i/2];
		}
		H->Data[i] = X;
	}
	return H;
}

bool IsFull( Heap H )
{
	if ( H && H->Size + 1 == MAXSIZE ){
		return true;
	}else{
		return false;
	}
}

bool IsEmpty( Heap H )
{
	if ( !H ) {
		printf("NO HEAP\n");
		return false;
	}else{
		if ( H->Size == 0 ) return true;
		else return false;
	}
}

int DeleteH( Heap H )
{
	if( IsEmpty(H) ){
		printf("FULL\n");
		return 0;
	}
	int ret = H->Data[1];
	int Parent = 1, Child;
	for(;Parent*2 <= H->Size;Parent = Child){
		Child = Parent * 2;
		if ( Child != H->Size && H->Data[Child] > H->Data[Child+1]){
			Child++;
		}
		H->Data[Parent] = H->Data[Child];
	} 
	H->Data[Child] = H->Data[H->Size--];
	return ret;
}
