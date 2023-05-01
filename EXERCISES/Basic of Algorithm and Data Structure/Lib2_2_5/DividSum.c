#include<stdio.h>

void Divid( int a[], int N, int len );

int main(int agc,const char* agv[])
{
	int N;
	scanf("%d",&N);
	int a[N];
	int k;
	for(k=0;k<N;k++) a[k] = 0;
	Divid( a, N, N );
	printf("\b ");
	return 0;
}

void Divid( int a[], int N, int len )
{
	static cnt=0;
	int beg = len - N;
	int i;
	for(i=1;i<=N;i++){
		a[beg] = i;
		if ( beg != 0 && a[beg] < a[beg-1]) {
			a[beg] = 0;
			continue;
		}
//		printf("a[0] = %d a[1] = %d a[2] = %d\n",a[0],a[1],a[2]);
		int sum=0,j;
		for(j=0;j<len;j++) sum+=a[j];
		
		if ( sum < len ) {
			Divid( a, N-1, len );
		} else if ( sum == len ) {
			printf("%d=",len);
			int s=a[0];
			for(j=0;j<len;j++){
				if ( a[j] && s < len ) printf("%d+",a[j]),s+=a[j+1];
				else if ( a[j] && s == len && cnt < 3 ) printf("%d;",a[j]),cnt++;
				else if ( a[j] && s == len && cnt == 3 ) printf("%d\n",a[j]),cnt=0;
			}
			a[beg]=0;
		} else if ( sum > len ) {
			a[beg]=0;
		}
//		for(j=0;j<len;j++) printf("%d ",a[j]);
//		printf("\n");
	}
}
