#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrToNode;
struct Node{
	int c;
	int e;
	PtrToNode Next;
};
typedef struct Node* List;

List Input();
List Multiply( List L1, List L2 );
List Add( List L1, List L2 );
int Compare( PtrToNode p, PtrToNode q );
void Insert( List L, PtrToNode p );
void Output( List L );

int main(int agc,const char* agv[])
{
	List L1,L2,L3,L4;
	L1 = Input();
	L2 = Input();
	L3 = Multiply( L1, L2 );
	L4 = Add( L1, L2 );
	Output(L3);
	printf("\n");
	Output(L4);
	
	return 0;
}

List Input() //已经测试过 
{
	int N;
	scanf("%d",&N);
	
	//如果N=0
	if ( N == 0 ) {
		List temp;
		temp = NULL;
		return temp;
	}
	// 
	
	//建立一个带头结点的链表，并接收数据 
	List head,rear,temp;
	temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->Next = NULL;
	head = temp;
	rear = temp;
	int i;
	for(i=0;i<N;i++) {
		List p;
		p = (PtrToNode)malloc(sizeof(struct Node));
		scanf(" %d %d",&p->c,&p->e);
		rear->Next = p;
		p->Next = NULL;
		rear = p;
	}
	//
	
	//删除头结点 
	head = head->Next;
	free(temp);
	// 
	
	//返回头结点
	return head; 
	//
}

int Compare( PtrToNode p, PtrToNode q )
{
	int ret;
	if ( p->e > q->e ) ret = 1;
	else if ( p->e < q->e ) ret = -1;
	else ret =0;
	return ret;
}

void Insert( List L, PtrToNode p )
{
	List s,temp;
	temp = (List)malloc(sizeof (struct Node));
	temp->Next = L;
	L = temp;
	s = L;
	int ctr=1;
	while( ctr ) {
		if ( !s->Next ) {
			s->Next = p, p->Next = NULL;
			ctr = 0;
		}else {	
		switch ( Compare (s->Next,p) ) {
			case 0:
				if ( s->Next->c + p->c != 0 ) {
					s->Next->c += p->c;
				} else {
					List t;
					t = s->Next;
					s->Next = s->Next->Next;
					free(t);
				}
				ctr = 0;
				break;
			case 1:
				s = s->Next;
				break;
			case -1:
				p->Next = s->Next;
				s->Next = p;
				ctr = 0;
				break;
		}
		}			
	}
	L = L->Next;
	free(temp);
}

List Multiply( List L1, List L2 )
{
	List L3;
	List p,q,temp,head,rear;
	p = L1;
	q = L2;
	if ( q==NULL || p==NULL ) return NULL;
	temp = (PtrToNode)malloc(sizeof(struct Node)); 
	head = temp;
	rear = temp;
	while( q ) {
		if ( p->e + q->e != 0 ) {
			List r;
			r = (PtrToNode)malloc(sizeof(struct Node));
			r->c = p->c * q->c;
			r->e = p->e + q->e;
			rear->Next = r;
			rear = r;
			r->Next = NULL;
		} else if ( p->e == 0 && q->e == 0 ){
			List r;
			r = (PtrToNode)malloc(sizeof(struct Node));
			r->c = p->c * q->c;
			r->e = p->e + q->e;
			rear->Next = r;
			rear = r;
			r->Next = NULL;
		}
		q = q->Next;	
	}
	head = head->Next;
	free(temp);
	L3 = head;
//	List s;
//	s = L3;
//	for(s;s->Next;s=s->Next) printf("%d %d ",s->c,s->e);
//	printf("%d %d ",s->c,s->e);

	q = L2;
	p = p->Next;
	while( p ) {
		q = L2;
		while ( q ) {
			if ( p->e + q->e != 0 ) {
				List t;
				t = (PtrToNode)malloc(sizeof(struct Node));
				t->c = p->c * q->c;
				t->e = p->e + q->e;
				Insert (L3,t);	
			} else if ( p->e == 0 && q->e == 0 ){
				List t;
				t = (PtrToNode)malloc(sizeof(struct Node));
				t->c = p->c * q->c;
				t->e = p->e + q->e;
				Insert (L3,t);	
			}
			q=q->Next;
		}
		p=p->Next;
	}
	return L3;
}

List Add( List L1, List L2 )
{
	List L4;
	List p,q;
	p = L1;
	q = L2;
	
	List temp,rear;
	temp = (PtrToNode)malloc(sizeof(struct Node));
	L4 = temp;
	rear = temp;
	while ( p && q ) {
		PtrToNode t,z,y;
		t = (PtrToNode)malloc(sizeof(struct Node));
		switch ( Compare( p, q ) ){
			case 1: rear->Next = t, t->c = p->c, t->e = p->e, rear = t, z=p, p=p->Next, free(z);
					break;
			case -1: rear->Next = t, t->c = q->c, t->e = q->e, rear = t, y=q, q=q->Next, free(y);
					break;
			case 0: if ( q->c + p->c != 0 ) {
						rear->Next = t, t->c = q->c + p->c, t->e = q->e ,rear = t;
						z=p, p=p->Next, y=q, q=q->Next, free(z), free(y);
						break;
					}
					z=p, p=p->Next, y=q, q=q->Next, free(z), free(y);
					break;
		}	      
	}
	if ( !q ) rear->Next = p;
	if ( !p ) rear->Next = q;
	L4 = L4->Next;
	free(temp);
	return L4;
}

void Output( List L )
{
	List p=L;
	if ( !p ) {
		printf("0 0");
	}
	else{
		for(p=L;p->Next;p=p->Next) {
			printf("%d %d ",p->c,p->e);
		}
		printf("%d %d",p->c,p->e);
	}	
}
