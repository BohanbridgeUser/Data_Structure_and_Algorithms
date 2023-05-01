#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define ERROR -1
typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node{
	ElementType Data;
	PtrToNode Next;
}; 
typedef PtrToNode List;

List Create();
ElementType Find( List L, ElementType m );
void Add( List L, ElementType X );

int main(int agc,const char* agv[])
{
	List L = Create();
	int i;
	if ( Find(L,233) != ERROR ) printf("%d\n",Find(L,233));
	else printf("ERROR");
	return 0;
}

List Create()
{
	List L = (List)malloc(sizeof(struct Node));
	L->Next = NULL;
	return L;
}

void Add( List L, ElementType X )
{
	PtrToNode p = (PtrToNode)malloc(sizeof(struct Node));
	p->Data = X;
	p->Next = L->Next;
	L->Next = p;
}

ElementType Find( List L, ElementType m)
{
	int cnt=0;
	List p = L;
	while ( cnt < m ){
		if ( p->Next ){
			p = p->Next;
			cnt++;
		}else{
			return ERROR;
		}
	}
	List q = L->Next;
	while( p->Next ){
		p=p->Next;
		q=q->Next;
	}
	return q->Data;
}
