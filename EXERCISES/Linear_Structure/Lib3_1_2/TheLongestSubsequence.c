#include<stdio.h>
#include<stdlib.h>
/*
	1.我的思路，两个顺序线性表分别记录当前最大和上一个最大，最后输出
	2.参考思路，记录当前最大的起点和终点以及长度，最后输出。 
*/
#define MAXSIZE 10001
typedef int ElementType;
typedef int Position;
typedef struct LNode* List;
struct LNode{
	ElementType Data[MAXSIZE];
	Position Last;
};

List Create();
List Add( List L, ElementType X );

int main(int agc,const char* agv[])
{
	int N;
	scanf("%d", &N);
	
	List nowmax,lastmax;
	nowmax = Create();
	lastmax = Create();
	int i,last;
	int n;
	scanf(" %d",&n);
	nowmax = Add(nowmax,n);	
	last = n;
	int j;
	for(i=1;i<N;i++){
		scanf(" %d",&n);
		if ( last < n ) {
			nowmax = Add(nowmax,n);	
			last = n;
		} else {
			if ( nowmax->Last > lastmax->Last ) {
				List tmp;
				tmp = lastmax;
				lastmax = nowmax;
				free(tmp);
				nowmax = Create();
				Add(nowmax,n);
			} else {
				nowmax->Last = -1;
				Add(nowmax,n);
			}
			last = n;
		}
	}
	if ( nowmax->Last > lastmax->Last ){
		for(i=0;i<nowmax->Last;i++) printf("%d ",nowmax->Data[i]);
		printf("%d",nowmax->Data[i]);
	} else {
		for(i=0;i<lastmax->Last;i++) printf("%d ",lastmax->Data[i]);
		printf("%d",lastmax->Data[i]);
	}
	return 0;
}

List Create()
{
	List L = (List)malloc(sizeof(struct LNode));
	L->Last = -1;
	return L;
}

List Add( List L, ElementType X )
{
	if ( L->Last == -1 ){
		L->Data[++L->Last] = X;
	}else{
		L->Data[++L->Last] = X;
	}
	return L;
}
