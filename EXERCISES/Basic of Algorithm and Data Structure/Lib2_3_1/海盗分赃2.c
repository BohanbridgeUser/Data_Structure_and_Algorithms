#include<stdio.h>

#define MAXSIZE 10

void Divid( int method[MAXSIZE], int round, int D, int P );

int main(int agc,const char* agv[])
{
	int D,P;
	scanf("%d %d",&D,&P);
	
	int method[MAXSIZE] = {0};
	Divid( method, P, D, P );
	printf("%d", method[0]);
	return 0;
}

void Divid( int method[MAXSIZE], int round, int D, int P )
{
	int row = round - 2, col = round - 1;  
	if ( row == 0 ) {
		method[P-1] = D;
		method[P-2] = 0;
	} else {
		round -= 1;
		Divid ( method, round, D, P );
		int i,sum=0,x=0;;
		for(i=P-round;i<P;i++){
			if ( method[i] == 0 ) {
				method[i] = 1;
				sum += 1;
			} else if ( x == 0 && method[i] == 1){
				method[i] = 2;
				sum += 2;
				x = 1;
			} else if ( method[i] == 1 ){
				method[i] = 0;
			} else if ( method[i] >= 2 ){
				method[i] = 0;
			}
		}
		method[P-round-1] = D - sum;
	}
}
