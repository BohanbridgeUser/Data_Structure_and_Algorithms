#include<stdio.h>

int main(int agc,const char* agv[])
{
	//input
    int N;
	scanf("%d",&N);
	int Num[N],i;
//	for(i=0;i<N;i++) scanf(" %d",&Num[i]);
//	for(i=0;i<N;i++) printf("%d ",Num[i]);
	//
    
    //A1 A2 A3
    int cnt=0,A1=0,A2=0,a1[N],j=0;
    double A3=0,sum=0;
	for(i=0;i<N;i++) {
		scanf(" %d",&Num[i]);
        switch ( Num[i] % 3) {
            case 0:A1++, a1[j]=Num[i], j++;
                   break;
            case 1:if ( Num[i] <= 50 ) A2++;
                   break;
            case 2:if ( !(Num[i] % 2) ) A3++,sum+=Num[i];  
                   break;
        }
    }
    
    if ( j ) {
    	int min = a1[0];
    	for(i=0;i<A1;i++) if ( min > a1[i] ) min = a1[i];
   		A1 = min;
    }
    //
    
    //output
    if ( A1 ) printf("%d ",A1);
    else printf("NONE ");
    if ( A2 ) printf("%d ",A2);
    else printf("NONE ");
    if ( A3 ) printf("%.1lf",sum/A3);
    else printf("NONE");
    //
	return 0;
}
