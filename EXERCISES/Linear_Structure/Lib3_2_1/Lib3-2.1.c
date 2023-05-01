#include<stdio.h>
#include<stdlib.h>

int main(int agc,const char* agv[])
{
	int* N = (int*)malloc(1000*sizeof(int));
	int i=0,F,gc;
	while( (F = scanf("%d",&N[i++]) == 1 ) ){
		if( (gc = getchar()) == '\n' ) break;
	}
	int j;
	if ( i == 2 ){
		printf("0 0");
	}else{
		for(j=0;j<i;j+=2){
			N[j] *= N[j+1];
			N[j+1]--;
		}
		printf("%d %d",N[0],N[1]);
		for(j=2;j<i;j+=2){
			if( N[j+1] < 0 ) break;
			else printf(" %d %d",N[j],N[j+1]);
		}
	}	
	return 0;
}

