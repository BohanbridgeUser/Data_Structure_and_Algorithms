#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//静态链表树 
#define MAXSIZE 10
#define Null -1
#define Tree int
struct BinTree{
	Tree Left;
	Tree Right;
}T[MAXSIZE];
//

//队列
#define MAXQUEUE 100
struct Queue{
	int Data[MAXQUEUE];
	int front;
	int rear;
}Que;

// 

//队列操作
void PushQueue( int N );
int PopQueue();
bool Isempty();
// 

//树操作 
Tree Input();
void Traversal();
//

int main(int agc,const char* agv[])
{
	Tree R1, R2;
	R1 = Input();
	PushQueue(R1);
	int Output[MAXSIZE];
	int i;
	for(i=0;i<MAXSIZE;i++) Output[i] = Null;
	Traversal(Output);
	for(i=0;i<MAXSIZE;i++){
		if ( Output[i] != Null && Output[i+1] != Null) printf("%d ",Output[i]);
		else if ( Output[i] != Null && Output[i+1] == Null) printf("%d",Output[i]);
		else break;
	}
	return 0;
}

void PushQueue( int N )
{
	if ( (Que.rear+1) % MAXQUEUE == Que.front ) {
		printf("队列满\n");
		return;
	} else {
		Que.Data[Que.rear] = N;
		Que.rear++;
		return;
	}
}

int PopQueue()
{
	if ( Que.front == Que.rear ){
		printf("队列空\n");
		return;
	} else {
		int i;
		i = Que.Data[Que.front];
		Que.front++;
		return i;
	}
}

bool Isempty()
{
	return (Que.front == Que.rear)? true:false;
}

Tree Input()
{
	int N;
	scanf("%d",&N);
	int i,Mark[N];
	for(i=0;i<N;i++) Mark[i]=0;
	for(i=0;i<N;i++){
		char cl,cr;
		scanf(" %c %c",&cl,&cr);
		if ( cl == '-' ) {
			T[i].Left = Null;
		}else {
			T[i].Left = cl - '0';
			Mark[T[i].Left] = 1;
		}
		if ( cr == '-' ) {
			T[i].Right = Null;
		}else {
			T[i].Right = cr - '0';
			Mark[T[i].Right] = 1;
		}
	}
	for(i=0;i<N;i++) if( !Mark[i] ) break;
	int root = i;
	return root;
}

void Traversal(int A[])
{
	int i = PopQueue();
	if ( T[i].Left != Null ){
		PushQueue(T[i].Left);
	}
	if ( T[i].Right != Null ){
		PushQueue(T[i].Right);
	}
	if ( T[i].Left == Null && T[i].Right == Null ){
		*A = i;
		A++;
	}
	if ( Isempty(Que) ){
		return;
	}else {
		Traversal(A);
		return;
	}
}

