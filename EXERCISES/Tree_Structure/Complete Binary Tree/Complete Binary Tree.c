/*
	���ȷ������ȫ�������������ṹ�ص㣺1.������������2.��ȫ��������
	˼·��ƽ�����������ȫ������������ʲô��ϵ��
	ƽ��������������һ��֮���Ƿ��ܱ�ɶ����������� 
	����֮���У�
	˼·2�����ݽڵ��������Է��ƿ��γ���༸���������������Ӷ��ҵ���ʱ��Root;
			�ݹ�Ѱ����������Root����������Rootֱ��û��������
			��β��������=>���� 
*/
#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
#include<stdbool.h>

#define MAXSIZE 1000

typedef struct D* Data;
struct D{
	int Left;
	int Right;
};
Data CreateData( int left, int right );
//Queue
typedef struct QNode* PtrToQNode;
struct QNode{
	Data Node;
	PtrToQNode Next;
}; 
struct HR{
	PtrToQNode Front;
	PtrToQNode Rear;
}; 
typedef struct HR* Queue;
Queue CreateQue();
Queue InsertQue( Queue Q, Data X );
int IsEmpty( Queue Q );
PtrToQNode DeleteQue( Queue Q );
//

int NumofHeight( int X ); // ����N���ڵ�����γɼ������������� 
void SequenceTravel( int Input[], Queue Q, int Output[] );



int main(int agc,const char* agv[])
{
	//Input
	int N;
	scanf("%d",&N);
	
	int Input[MAXSIZE] = {0};
	int i;
	for(i=0;i<N;i++){
		scanf(" %d",&Input[i]);
	}
	//
	
	//sort
	int j;
	for(j=0;j<N-1;j++){
		int min = j;
		for(i=j;i<N;i++){
			if ( Input[i] < Input[min] ) {
				min = i;
			}
		}
		int tmp = Input[j];
		Input[j] = Input[min];
		Input[min] = tmp;	
	}
	//
	
	//
	int Output[N];
	Queue Q = CreateQue();
	Data D = CreateData( 0, N-1 );
	Q = InsertQue( Q, D );
	SequenceTravel( Input, Q, Output );
	for(i=0;i<N-1;i++) printf("%d ",Input[Output[i]]);
	printf("%d",Input[Output[i]]);
	//
	return 0;
}

Data CreateData( int left, int right )
{
	Data D = (Data)malloc(sizeof(struct D));
	D->Left = left;
	D->Right = right;
	return D;
}

Queue CreateQue()
{
	Queue Q = (Queue)malloc(sizeof(struct HR));
	Q->Front = NULL;
	Q->Rear = NULL;
	return Q;
}

Queue InsertQue( Queue Q, Data X )
{
	PtrToQNode P = (PtrToQNode)malloc(sizeof(struct QNode));
	P->Node = X;
	P->Next = NULL;
	if( !Q->Front ) Q->Front = P;
	if( !Q->Rear ) {
		Q->Rear = P;
	}else{
		Q->Rear->Next = P;
		Q->Rear = Q->Rear->Next; 
	}
	return Q;
}

int IsEmpty( Queue Q )
{
	if ( !Q->Front ){
		return true;
	}else{
		return false;
	}
}

PtrToQNode DeleteQue( Queue Q )
{
	PtrToQNode ret;
	if ( !IsEmpty(Q) ){
		ret = Q->Front;
		Q->Front = Q->Front->Next;
		return ret;
	}else{
		printf("\nQUEUE EMPTY\n");
		return;
	}
}

int NumofHeight( int X )
{
	int j=1, k=1;
	int i=1, ctr=0;
	while( k <= X ){
		j = j<<1;
		k = k|j;
		i++;
	}
	return i-1;
}

void SequenceTravel( int Input[], Queue Q, int Output[] )
{
	
	PtrToQNode Y = DeleteQue( Q );
	Data X = Y->Node;
	if ( X->Left > X->Right ) return;
	int N = X->Right - X->Left + 1;
	int h = NumofHeight( N ); //N���ڵ���Է�h������������
	int Nh = N - ( pow(2,h) - 1 );//��h+1���ж��ٽڵ㣿
	int Nhl = ( pow(2,h) ) / 2;	//��h+1��һ����ԷŶ��ٽڵ㣿
	int root;
	if ( !Nh ){
		root = ( X->Right + X->Left  ) / 2;
	}else {
		if ( Nh - Nhl > 0 ){
			int Nhr = Nh - Nhl;
			root = (X->Left+Nhl+X->Right-Nhr)/2;
		}else{
			root = (X->Left+Nh+X->Right)/2 ;
		}
		/*�Ҵ�ʱ�ĸ��ڵ��λ�ã�Nh�����һ��ڵ��������
								��1��Nh-Nhl>0 ˵�����һ���ұ�Ҳ�нڵ㣬��Nhr��ʾ���һ���Ұ벿�ֽڵ�������
								���ڵ㣺(X->Left+Nhl+X->Right+Nhr)/2 
								��2��Nh-Nhl<0˵���ڵ�ȫ����ߣ� 
								���ڵ㣺(X->Left+Nhl+X->Right)/2 
		*/						
	}
	*Output = root;
	Output++;
	
	Data XL = CreateData( X->Left, root - 1 );
	Data XR = CreateData( root + 1, X->Right );
	Q = InsertQue( Q, XL );
	Q = InsertQue( Q, XR );
	SequenceTravel( Input, Q, Output );
	return;
} 
