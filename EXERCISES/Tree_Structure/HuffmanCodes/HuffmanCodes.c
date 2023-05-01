/*
	思路一：
	1.根据提供的编码建树——计算带权路径长度 
	2.判断是否为哈夫曼树 
	思路二：	
	1.求哈夫曼编码最优值
	2.判断是否是哈夫曼编码
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h> 
#include<string.h>

/* input */
typedef struct Input* In;
struct Input{
	char Data[63];
	
};

/* Huffman Tree */
typedef struct HFNode* PtrToHFNode;
struct HFNode{
	int Weight;
	PtrToHFNode Left;
	PtrToHFNode Right;
	int Flag;
};
typedef PtrToHFNode HuffTree;

/* Heap */
#define MAXHEAP 63
typedef PtrToHFNode ElementTypeofHeap;
typedef struct HNode* Heap;
struct HNode{
	ElementTypeofHeap *Data;
	int Size;
	int Capacity;
}; 

Heap CreateHeap()
{
	Heap H = (Heap)malloc(sizeof( struct HNode ));
	H->Data = (ElementTypeofHeap*)malloc((MAXHEAP+1)*sizeof(ElementTypeofHeap));
	H->Size = 0;
	H->Capacity = MAXHEAP;
	H->Data[0] = (PtrToHFNode)malloc(sizeof(struct HFNode));
	H->Data[0]->Weight = -1;
	return H; 
}
bool IsFullHeap( Heap H )
{
	if ( H->Size == H->Capacity ) return true;
	else return false;
}
bool InsertHeap( Heap H, ElementTypeofHeap X )
{
	if ( IsFullHeap( H ) ){
		printf("FULL HEAP\n");
		return false;
	}else{
		int i = ++H->Size;
		for(;H->Data[i/2]->Weight > X->Weight;i/=2){
			H->Data[i] = H->Data[i/2];
		}
		H->Data[i] = X;
		return true;
	}
}
bool IsEmptyHeap( Heap H )
{
	if ( !H->Size ) return true;
	else return false;
}
ElementTypeofHeap DeleteHeap( Heap H )
{
	if ( IsEmptyHeap(H) ) {
		printf("EMPTY HEAP\n");
		return NULL;
	}else{
		ElementTypeofHeap RET = H->Data[1];
		ElementTypeofHeap Last = H->Data[H->Size--];
		int Parent,Child;
		for(Parent=1;Parent*2<=H->Size;Parent = Child){
			Child = Parent*2;
			if (!(Child==H->Size) && H->Data[Child]->Weight > H->Data[Child+1]->Weight )
				Child += 1;
			if ( Last->Weight > H->Data[Child]->Weight ) 
				H->Data[Parent] = H->Data[Child];
			else break;
		}
		H->Data[Parent] = Last;
		return RET;
	}
}

/* Build Huffman Tree */
HuffTree BuildHuffTree( Heap H )
{
	if ( IsEmptyHeap(H) ) return NULL;
	while( !IsEmptyHeap(H) ){
		PtrToHFNode T = (PtrToHFNode)malloc(sizeof(struct HFNode));
		T->Left = DeleteHeap( H );
		T->Right = DeleteHeap( H );
		T->Weight = T->Left->Weight + T->Right->Weight;
		if ( IsEmptyHeap(H) ) return T;
		InsertHeap( H, T );
	}	
}

/* WPL LevelTraversal calculate */
#define ElementTypeofStack PtrToHFNode
typedef struct SNode* PtrToSNode;
struct SNode{
	ElementTypeofStack Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
Stack Push( Stack S, ElementTypeofStack X )
{
	PtrToSNode P = (PtrToSNode)malloc(sizeof(struct SNode));
	P->Data = X;
	P->Next = S->Next;
	S->Next = P;
	return S; 
}
bool IsEmptyS( Stack S )
{
	if( !S->Next ) return true;
	else return false;
}
ElementTypeofStack Pop( Stack S )
{
	if( IsEmptyS(S) ) return NULL;
	else{
		ElementTypeofStack RET = S->Next->Data;
		PtrToSNode TEMP = S->Next;
		S->Next = S->Next->Next;
		free(TEMP);
		return RET;
	}	
}
HuffTree Peek( Stack S, int* cnt )
{
	if( IsEmptyS(S) ) return NULL;
	else{
		HuffTree TEMP = Pop( S );
		while( TEMP && TEMP->Flag ){
			TEMP = Pop(S);
		    (*cnt)--;
		}
		if ( TEMP && !TEMP->Flag ) {
			TEMP->Flag = 1;
			S = Push(S,TEMP);
		}
		return TEMP;
	}	
}
int WPL( HuffTree T )
{
	int WPL = 0, cnt = 0;
	if ( !T ) return 0;
	Stack S = CreateS();
	HuffTree P = T;
	while( P || !IsEmptyS(S) ){
		for(;P;P=P->Left){
			S = Push( S, P );
			cnt++; 
		}
		P = Peek( S, &cnt );
		if ( P ) {
			if ( P->Flag ==1 &&!P->Left &&  !P->Right ) WPL += (cnt-1) * P->Weight;
			P = P->Right;	
		}
	}
	return WPL;
}
void PreorderTraversal( HuffTree T )
{
	if ( !T ) return ;
	Stack S = CreateS();
	HuffTree P = T;
	while( P || !IsEmptyS(S) ){
		for(;P;P=P->Left){
			printf("%d ",P->Weight);
			S = Push( S, P );
		}
		P = Pop(S)->Right;		
	}
}
In StudentInput( int N )
{
	In IN = (In)malloc(N*sizeof(struct Input));
	int i;
	for(i=0;i<N;i++){
		char c;
		scanf(" %c %s",&c,&IN[i].Data);
	}
	return IN;
}
int CalculateWPL( int Weight[], In IN, int N )
{
	int wpl=0;
	int i;
	for(i=0;i<N;i++){
		wpl += strlen(IN[i].Data) * Weight[i];
	}
	return wpl;
}
bool Judge( In IN, int N, int* Weight )
{
	int i;
	HuffTree Root = (HuffTree)malloc(sizeof(struct HFNode));
	Root->Weight = -1;
	for(i=0;i<N;i++){
		HuffTree root = Root;
		int j;
		for(j=0;j<strlen(IN[i].Data);j++){
			if( j < strlen(IN[i].Data) - 1 ){
				if ( IN[i].Data[j] == '0'){
					if ( !root->Left ){
						HuffTree Left = (HuffTree)malloc(sizeof(struct HFNode));
						Left->Weight = -1;
						root->Left = Left;
					}
					root = root->Left;	
				}else if ( IN[i].Data[j] == '1' ){
					if ( !root->Right ){
						HuffTree Right = (HuffTree)malloc(sizeof(struct HFNode));
						Right->Weight = -1;
						root->Right = Right;
					}
					root = root->Right;	
				}
			}else{
				if ( IN[i].Data[j] == '0'){
					if ( !root->Left ){
						HuffTree Left = (HuffTree)malloc(sizeof(struct HFNode));
						Left->Weight = Weight[i];
						root->Left = Left;
					}else {
						return false;
					}
					root = root->Left;	
				}else if ( IN[i].Data[j] == '1' ){
					if ( !root->Right ){
						HuffTree Right = (HuffTree)malloc(sizeof(struct HFNode));
						Right->Weight = Weight[i];
						root->Right = Right;
					}else {
						return false;
					}
					root = root->Right;	
				}
			}
		}
	}
	return true;
}
int main(int agc,const char* agv[])
{
	/* Calculate wpl */
	int N;
	scanf("%d",&N);
	int Weight[N];
	int i;
	char c;
	Heap H = CreateHeap();
	for(i=0;i<N;i++) Weight[i] = 0;
	for(i=0;i<N;i++) {
		scanf(" %c %d",&c,&Weight[i]);
		PtrToHFNode F = (PtrToHFNode)malloc(sizeof(struct HFNode));
		F->Weight = Weight[i];
		F->Flag = 0;
		InsertHeap( H, F );
	}
	HuffTree T = BuildHuffTree( H );
	int wpl = WPL( T );
	
	/* Judge */
	int M;
	scanf("%d ",&M);
	for(i=0;i<M;i++){
		In IN = StudentInput( N );
		int wplofin = CalculateWPL( Weight, IN, N );
		if( wplofin != wpl) printf("No\n");
		else{
			if( Judge( IN, N, Weight ) ) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
}


