#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrToNode;
struct Node{
	int Coe;
	int Exp;
	PtrToNode Next;
};
typedef PtrToNode List;

List Input();
List Multiply( List L1, List L2 );

int main(int agc,const char* agv[])
{
	List L1 = Input();
	List L2 = Input();
	
	return 0;
}

List Input()
{
	List L = (List)malloc(sizeof(struct Node));
	L->Next = NULL;
	List rear = L;
	int N;
	scanf("%d",&N);
	int i;
	for(i=0;i<N;i++){
		int coe,exp;
		scanf(" %d %d",&coe,&exp);
		List p = (List)malloc(sizeof(struct Node));
		p->Coe = coe;
		p->Exp = exp;
		rear->Next = p;
		p->Next = NULL;
		rear=rear->Next;
	}
	return L;
}

List Multiply( List L1, List L2 )
{
	PtrToNode p=L1->Next,q=L2->Next;
	List L3 = (List)malloc(sizeof(struct Node));
	L3->Next = NULL;
	List m = L3;
	for(p;p;p=p->Next) {
		for(q;q;q=q->Next) {
			if ( p->Exp + q->Exp == 0){
				
			}
		}
	}
}
