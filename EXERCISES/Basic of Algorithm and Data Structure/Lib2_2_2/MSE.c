#include<stdio.h>
#include<math.h>


int main(int agc,const char* agv[])
{
	int N,i;
	scanf("%d",&N);
	double a[N];
	double Sum=0;
	for (i=0;i<N;i++) scanf(" %lf",&a[i]), Sum += a[i];
	double Avg, Mse;
	Avg = Sum / (1.0*N);
	Sum=0.0;
	for ( i=0;i<N;i++ ) Sum = Sum * 1.0 + pow(a[i] - Avg,2);
	Mse = sqrt ( Sum / (1.0*N) );
	printf("%.5lf",Mse);
	return 0;
}

