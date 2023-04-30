#include<stdio.h>
#include<stdbool.h>
#include<math.h>

typedef int Mid;
Mid findmid1( int S1[], int S2[], int N);
Mid findmid2( int S1[], int S2[], int N);
Mid findmid3( int S1[], int S2[], int N);
int Binary( int S[], int* left, int* right );

int main(int agc,const char* agv[])
{
	//Input
	int N = 0;
	if( scanf("%d",&N) == 0) printf("false\n"); 
	int S1[N],S2[N];
	int i;
	for(i=0;i<N;i++){
		if( scanf(" %d",&S1[i] ) == 0) printf("Input S1[%d] false\n",i);
	}
	for(i=0;i<N;i++){
		if( scanf(" %d",&S2[i] ) == 0) printf("Input S2[%d] false\n",i);
	}
	//
	
	//find mid case 1
	Mid mid;
	//mid = findmid1 ( S1, S2, N );
	//
	
	//find mid case 2
//	mid = findmid2 ( S1, S2, N );
	//
	
	//find mid case 3
	mid = findmid3 ( S1, S2, N );
	
	//Output
	printf("%d\n",mid);
	//
	return 0;
}

Mid findmid1( int S1[], int S2[], int N)
{
	int S3[2*N];
	int i=0,j=0,k=0;
	while ( k < 2 * N){
		if ( i == N ){
			S3[k++] = S2[j++];
		} else if ( j == N ){
			S3[k++] = S1[i++];
		} else {
			if ( S1[i] < S2[j] ){
				S3[k++] = S1[i++];
			}else if ( S1[i] > S2[j] ){
				S3[k++] = S2[j++];
			}else /* S1[i] == S2[j] */{
				S3[k++] = S1[i++];
				S3[k++] = S2[j++];
			}
		}		
	}
	return S3[(2 * N + 1) / 2];
}

Mid findmid2( int S1[], int S2[], int N)
{
	int cnt = ( 2 * N ) / 2 - 1;
	Mid max=0;
	int i=0,j=0;
	while ( cnt > -1){
		if ( S1[i] > S2[j] ){
			max = S1[i];
			if ( cnt == 0) max = S2[j];
			j++;
			cnt--;
		} else if ( S1[i] < S2[j]){
			max = S2[j];
			if ( cnt == 0) max = S1[i];
			i++;
			cnt--;
		} else /* S1[i] == S2[j] */{
			max = S1[i];
			j++;
			cnt--;	
		}
	}
	return max;
}

Mid findmid3( int S1[], int S2[], int N ) 
{
	int l1= 0, r1=N-1, l2 = 0, r2=N-1, mid1, mid2;
	int cntr = 0;
	int ret;
	int cnt=0;
	
	if ( (l1 + r1) % 2 != 0 ){
		mid1 = ( l1 + r1 ) / 2;
		mid2 = ( l2 + r2 ) / 2 + 1;
	} else {
		mid1 = ( l1 + r1 ) / 2;
		mid2 = ( l2 + r2 ) / 2;
	}
	
	while( cntr == 0 ){
//		printf("mid1 = %d mid2 = %d ",mid1,mid2);
//		printf("l1 = %d r1 = %d l2 = %d r2 = %d \n",l1,r1,l2,r2);
		if ( S1[mid1] < S2[mid2] ) {
			l1 = mid1;
			r2 = mid2;
			if ( ( l1 + r1 ) % 2 != 0 && fabs(l2 - r2) != 1 ){
				mid1 = ( l1 + r1 ) / 2;
				mid2 = ( l2 + r2 ) / 2 + 1;
			} else if ( ( l1 + r1 ) % 2 == 0 && fabs(l2 - r2) != 1 ){
				mid1 = ( l1 + r1 ) / 2;
				mid2 = ( l2 + r2 ) / 2;
			} else if ( fabs(l2 - r2) == 1 ){
				mid1 = r1;
				l1 = r1;
				mid2 = l2;
				r2 = l2;
			}
		} else if ( S1[mid1] > S2[mid2] ) {
			r1 = mid1;
			l2 = mid2;
			mid1 = ( l1 + r1 ) / 2 + 1;
			mid2 = ( l2 + r2 ) / 2;
			if ( ( l2 + r2 ) % 2 != 0 && fabs(l2 - r2) != 1 ){
				mid1 = ( l1 + r1 ) / 2 + 1;
				mid2 = ( l2 + r2 ) / 2;
			} else if ( ( l2 + r2 ) % 2 == 0 && fabs(l2 - r2) != 1 ){
				mid1 = ( l1 + r1 ) / 2;
				mid2 = ( l2 + r2 ) / 2;
			} else if ( fabs(l1 - r1) == 1 ){
				mid1 = l1;
				r1 = l1;
				mid2 = r2;
				l2 = r2;
			}
		} else {
			ret = S1[mid1];
			cntr = 1;
		}
		
		if( l1 == r1 ){
			if ( S1[mid1] < S2[mid2] ){
				ret = S1[mid1];
				cntr = 1;
			} else {
				ret = S2[mid2];
				cntr = 1;
			}
		}
		cnt++;
	}
	return ret;	
}



