#include<stdio.h>

int main(int agc,const char* agv[])
{
	int N,i;
	scanf("%d",&N);
	
	int a[N];
	for( i=0; i<N; i++ ) scanf(" %d",&a[i]);
	int Sum=0;
	for( i=0; i<N; i++) {
		int j;
		for(j=0;j<N;j++){
			if ( j != i ) Sum +=  a[i] * 10 + a[j];
		}
	}
	printf("%d",Sum);
	return 0;
}

