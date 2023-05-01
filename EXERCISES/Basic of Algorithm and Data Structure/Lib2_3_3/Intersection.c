#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

typedef struct Node* PtrToNode;
struct Node{
	ElementType Data;
	PtrToNode Next;
};
typedef struct Node* List;

List Input();
List Intersection( List L1, List L2 );

int main(int agc,const char* agv[])
{
	//Input
	List L1,L2;
	L1 = Input();
	L2 = Input();	
	//
	
	//Intersection
	List L3 = Intersection( L1, L2 );
	//
	
	//Output
	if ( !L3->Next ){
		printf("NULL");
	}else{
		List q;
		for(q=L3->Next;q->Next;q=q->Next) printf("%d ",q->Data);
		printf("%d\n",q->Data);
	}	
	//
	return 0;
}

List Input()
{
	int i = 0;
	scanf(" %d",&i);
	
	List L, rear;
	L = (List)malloc(sizeof(struct Node));
	L->Next = NULL;
	rear = L;
	
	while ( i != -1 ){
		List p;
		p = (List)malloc(sizeof(struct Node));
		p->Data = i;
		rear->Next = p;
		rear = rear->Next;
		rear->Next = NULL;
		scanf(" %d",&i);
	}
	
	return L;
}

List Intersection( List L1, List L2 )
{
	List L3,rear;
	L3 = (List)malloc(sizeof(struct Node));
	L3->Next = NULL;
	rear = L3;
	
	if ( !L1->Next || !L2->Next ) return L3;
	
	PtrToNode p = L1, q = L2;
	while ( p->Next && q->Next ){
		if ( p->Next->Data == q->Next->Data ) {
				List L;
				L = (List)malloc(sizeof(struct Node));
				L->Data = p->Next->Data;
				rear->Next = L;
				rear = rear->Next;
				rear->Next = NULL;
				p = p->Next;
				q = q->Next;
		} else if ( p->Next->Data < q->Next->Data ) {
			p = p->Next;
		} else if ( p->Next->Data > q->Next->Data ) {
			q = q->Next;
		}
	}
	
	return L3;
}
