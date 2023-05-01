#include<stdio.h>
#include<stdlib.h>

typedef struct Node* p;
struct Node{
	int Ad;
	int Data;
	int Next;
};

void Swap ( p n, p m );

int main(int agc,const char* agv[])
{
	//Input
	int head, N, K;
	scanf("%d %d %d",&head,&N,&K);
	
	struct Node n[N];
	p np[N];
	int i;
	for(i=0;i<N;i++) {
		np[i] = n + i;
		scanf(" %d %d %d",&n[i].Ad,&n[i].Data,&n[i].Next);
	}
	//
	
	//Sort
	for(i=0;i<N;i++){
		int j;
		for(j=i;j<N;j++) {
			if( np[j]->Ad == ( i ? np[i-1]->Next : head ) ){
				Swap ( np[i], np[j] );
				break;
			}		
		}
		if ( np[i]->Next == -1 )
		N = i + 1;
	}
	//
	
	//KSort
	for( i=0;i<N/K;i++){
		p* l;
		l = np + i * K;
		int j;
		for( j=0;j<K/2;j++){
			Swap( l[j], l[K-j-1] );
		}
	}
	//
	
	//Output
	for(i=0;i<N-1;i++){
		printf("%05d %d %05d\n",np[i]->Ad,np[i]->Data,np[i+1]->Ad);
	}
	printf("%05d %d -1",np[i]->Ad,np[i]->Data,np[i]->Next);
	//
	return 0;
}

void Swap ( p n , p m)
{
	struct Node x;
	p  l = &x;
	*l = *n;
	*n = *m;
	*m = *l;
	return;
}
