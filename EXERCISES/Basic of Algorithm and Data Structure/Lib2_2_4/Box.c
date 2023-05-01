#include<stdio.h>

int main(int agc,const char* agv[])
{
	int N;
	scanf("%d",&N);
	int Num[N],Box[N];
	int i;
	
	for(i=0;i<N;i++) Box[i] = 100;
	scanf(" %d",&Num[0]);
	Box[0] -= Num[0];
	printf("%d %d\n",Num[0],1);
	for(i=1;i<N;i++) {
		scanf(" %d",&Num[i]);
		int j;
		for (j=0;j<=i;j++){
			if ( Box[j] >= Num[i] ) {
				Box[j] -= Num[i], printf("%d %d\n",Num[i],j+1);
				break;
			}
		} 
	}
	for(i=0;i<N;i++){
		if( Box[i] == 100 ) break;
	}
	printf("%d",i);
	return 0;
}

