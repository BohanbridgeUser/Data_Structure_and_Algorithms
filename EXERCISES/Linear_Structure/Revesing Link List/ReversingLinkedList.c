#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node* PtrToNode;
struct Node{
	PtrToNode Before;
	char Address[6];
	int Data;
	char NextAd[6];
	PtrToNode Next;
};
typedef struct Node* List;

List Input( int N );
List Sort( List L, char* Head, int* N );
void KSort( List L, int K, int N );

int main(int agc,const char* agv[])
{
	//Input
	int N,K;
	char Head[6];
	scanf("%s %d %d",&Head,&N,&K);
	List L = Input( N );
	//
	
	//Sort 按地址排序 
	L = Sort( L, Head, &N );
//	List q;
//	for(q=L;q->Next!=L;q=q->Next) printf("%s %d %s\n",q->Next->Address,q->Next->Data,q->Next->NextAd);
//	for(q=L;q->Before!=L;q=q->Before) printf("%s %d %s\n",q->Before->Address,q->Before->Data,q->Before->NextAd);
	//
	
	//按K反序输出 
	KSort( L, K ,N );
	//
	return 0;
}

List Input( int N )
{
	PtrToNode head,rear,temp;
	temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->Next = NULL;
	head = temp;
	rear = temp;
	int i;
	for(i=0;i<N;i++) {
		List p;
		p = (PtrToNode)malloc(sizeof(struct Node));
		scanf(" %s %d %s",&p->Address,&p->Data,&p->NextAd);
		rear->Next = p;
		p->Before = rear;
		p->Next=NULL;
		rear = p;
	}
	rear->Next = head;
	head->Before = rear;
	return head;
}

List Sort( List L, char* Head, int *N )
{
	//找到首节点并复制,同时删除被复制节点 
	List p = L;
	List tHead,empty;
	while ( strcmp( p->Next->Address, Head ) != 0 ){
		p = p->Next;
	}
	tHead = (List)malloc(sizeof(struct Node));
	memcpy( tHead->Address, p->Next->Address, 5 );
	tHead->Data = p->Next->Data;
	memcpy( tHead->NextAd , p->Next->NextAd, 5 );
	tHead->Next = NULL;
	empty = (List)malloc(sizeof(struct Node));
	empty->Next = tHead;
	tHead->Before = empty;
	 
	List temp;
	temp = p->Next;
	p->Next = p->Next->Next;
	p->Next->Before = p;
	free(temp);
	p = p ->Next;
	//
	
	//Sort
	List rear;
	rear = p;
	List t = tHead;
	while ( rear->Next != rear ) {
		if ( rear->Next->Next == rear && strcmp(t->NextAd,"-1") == 0 ) {
			*N = *N-1;
			break;
		}
		if ( strcmp( rear->Next->Address, t->NextAd ) == 0 ) {
			t->Next = rear->Next;
			t->Next->Before = t;
			rear->Next = rear->Next->Next;
			rear->Next->Before = rear;
			t = t->Next;
			t->Next = NULL;
		} else {
			rear = rear->Next;
		}	
	}
	temp = L->Next;
	L = empty;
	empty->Before = t;
	t->Next =empty;
	free(temp);
	//
	return L;
}

void KSort( List L, int K, int N )
{
	if ( K==1 ) {
		List x;
		for(x=L;x->Next!=L;x=x->Next){
			printf("%s %d %s\n",x->Next->Address,x->Next->Data,x->Next->NextAd);
		}	
		return;
	}
	List q = L;
	PtrToNode temp;
	temp = L->Next;
	int i,cnt=0;
	while ( cnt % K == 0 && cnt != N ){
		for(i=0;i<K;i++) {
			temp = temp->Next;
			cnt++;
			if ( temp == q && cnt % K != 0 ) {
				break;
			}
		}
		if ( temp == q && cnt % K != 0 ) {
			break;
		} else if ( temp == q && cnt % K == 0 ) {
			List p;
			p = temp->Before;
			for(i=0;i<K;i++){
			memcpy(p->NextAd,p->Before->Address,6);
			p = p->Before;
			}
			memcpy(p->Next->NextAd,"-1",6);
			break;
		}
		List p;
		p = temp->Before;
		for(i=0;i<K;i++){
			memcpy(p->NextAd,p->Before->Address,6);
			p = p->Before;
		}
		memcpy(p->Next->NextAd,temp->Address,6);
	}
	
	cnt = 0;
	temp = L->Next;
	while ( cnt % K == 0 && cnt != N ){
		for(i=0;i<K;i++) {
			temp = temp->Next;
			cnt++;
			if ( temp == q && cnt % K != 0 ) {
				break;
			}
		}
		if ( temp == q && cnt % K != 0 ) {
			break;
		} else if ( temp == q && cnt % K == 0 ) {
			List p;
			p = temp->Before;
			for(i=0;i<K;i++){
				printf("%s %d %s\n",p->Address,p->Data,p->NextAd);
				p = p->Before;
			}
			break;	
		}
		List p;
		p = temp->Before;
		for(i=0;i<K;i++){
			printf("%s %d %s\n",p->Address,p->Data,p->NextAd);
			p = p->Before;
		}	
	}
	if ( N%K !=0 ){
		for(i=0;i<N%K+1;i++) temp = temp->Before;
		for(temp;temp->Next!=L;temp = temp->Next) 	
			printf("%s %d %s\n",temp->Next->Address,temp->Next->Data,temp->Next->NextAd);	
	}
}
