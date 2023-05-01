#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100000

typedef int ElementType;
typedef int Position;
typedef struct LNode* List;
struct LNode{
	ElementType Data[MAXSIZE];
	Position Last;
};

List Delete ( List L, ElementType minD, ElementType maxD );
List Create();
List Input( List L, ElementType X );
List Delete2( List L, ElementType minD, ElementType maxD );

int main(int agc,const char* agv[])
{
	List L = Create();
	L = Input( L, 1 );
	L = Input( L, 2 );
	L = Input( L, 3 );
	L = Input( L, 4 );
	L = Input( L, 5 );
	L = Input( L, 6 );
//	L = Input( L, 9 );
//	L = Input( L, 3 );
//	L = Input( L, 3 );
//	L = Input( L, 10 );
	int i;
	int minD = 0, maxD = 100;
	//method 1
//	L = Delete( L, minD, maxD );
	//
	
	//method 2
	L = Delete2( L, minD, maxD );
	//
	
	for(i=0;i<=L->Last;i++) printf("%d ",L->Data[i]);
		
	return 0;
}

List Create()
{
	List L = (List)malloc(sizeof( struct LNode));
	L->Last = -1 ;
	return L;
}

List Input( List L, ElementType X )
{
	if ( L->Last == MAXSIZE - 1 ){
		printf("FULL LIST\n");
		return NULL;
	}else if( L->Last == -1){
		L->Data[0] = X;
		L->Last++;
	}else {
		L->Data[++L->Last] = X;
		return L;
	}
}

void Remove( List L, Position i )
{
	int j=i;
	for(j;j<L->Last;j++){
		L->Data[j] = L->Data[j+1];
	}
	L->Last--;
}

List Delete ( List L, ElementType minD, ElementType maxD )
{
	int i;
	for(i=0;i<=L->Last;i++){
		if( L->Data[i] > minD && L->Data[i] < maxD ){
			Remove( L, i );
			i--;
		}
	}
	return L;
}

List Delete2( List L, ElementType minD, ElementType maxD )
{
	//Find first number
	int i=0;
	while( i <= L->Last ){
		if ( L->Data[i] > minD && L->Data[i] < maxD ) break;
		else i++;
	}
	// 
	int temp = i++;
	while( i <= L->Last ) {
		if ( L->Data[i] <= minD || L->Data[i] >= maxD ) {
			L->Data[temp] = L->Data[i++];
			temp++;
		} else {
			i++;
		}
	}
	L->Last = --temp;
	return L;
}

