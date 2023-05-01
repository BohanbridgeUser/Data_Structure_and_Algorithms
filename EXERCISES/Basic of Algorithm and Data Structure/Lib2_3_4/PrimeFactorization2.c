#include<stdio.h>
#include<math.h>

#define MAXSIZE 10000

int IsPrime( long i );

int main(int agc,const char* agv[])
{
	//Input
	long N;
	scanf("%d",&N);
	//
	
	//main
	long Fac[MAXSIZE], e[MAXSIZE], x=0;
	printf("%d=",N);
	if ( N == 1) {
		printf("1");
	}
	else{
		int j=2,i=N;
		for(j;j<=i;j++){
			if ( i % j == 0 && IsPrime(j) == 1 ){
				Fac[x] = j;
				int k=0;
				while ( i % j == 0 ){
					i /= j;
					k++;
				}
				e[x] = k;
				x++;
			} 
		}
		
		for(i=0;i<x-1;i++){
			if ( e[i] == 1) {
				printf("%ld*",Fac[i],e[i]);
			} else {
				printf("%ld^%ld*",Fac[i],e[i]);
			}				
		}
		if ( e[i] == 1) {
			printf("%ld",Fac[i],e[i]);
		} else {
			printf("%ld^%ld",Fac[i],e[i]);
		}
	}
	//
	
	return 0;
}

int IsPrime( long i )
{
	long j;
	int isprime = 1;
	for(j=2;j < i;j++){
		if ( i % j == 0 ) {
			isprime = 0;
			break;
		}
	}
	return isprime;
}

