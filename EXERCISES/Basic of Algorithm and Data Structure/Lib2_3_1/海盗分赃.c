#include<stdio.h>

#define MAXSIZE 100

void Divid( int method[][MAXSIZE], int round, int D, int P );

int main(int agc,const char* agv[])
{
	int D,P;
	scanf("%d %d",&D,&P);
	
	int method[MAXSIZE][MAXSIZE] = {0};
	Divid( method, P, D, P );
	printf("%d", method[P-2][0]);
	return 0;
}

void Divid( int method[][MAXSIZE], int round, int D, int P )
{
	int row = round - 2, col = round - 1;  
	if ( row == 0 ) {
		method[row][P-1] = D;
		method[row][P-2] = 0;
	} else {
		round -= 1;
		Divid ( method, round, D, P );
		int i,sum=0,x=0;;
		for(i=P-round;i<P;i++){
			if ( method[row-1][i] == 0 ) {
				method[row][i] = 1;
				sum += 1;
			} else if ( x == 0 && method[row-1][i] == 1){
				method[row][i] = 2;
				sum += 2;
				x = 1;
			} else if ( method[row-1][i] == 1 ){
				method[row][i] = 0;
			}
		}
		method[row][P-round-1] = D - sum;
	}
}
