#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int SetName;

int Max( int Set[], int c1, int c2 );
int Min( int Set[], int c1, int c2 );
int Find( int Set[], int i );

int main(int agc,const char* agv[])
{
	int N;
	scanf("%d",&N);
	int Set[N+1];
	int i;
	for(i=0;i<=N;i++) Set[i] = -1;
	char c = '0';
	while( c != 'S'){
		int c1, c2;
		scanf(" %c",&c);
		if ( c != 'S' ){
			scanf(" %d %d",&c1,&c2);
			if ( c == 'I'){
				c1 = Find(Set,c1);
				c2 = Find(Set,c2);
				Set[Max(Set,c1,c2)] = Set[c1] + Set[c2];
				Set[Min(Set,c1,c2)] = Max(Set, c1,c2);
			}else if ( c == 'C' ){
				c1 = Find(Set,c1);
				c2 = Find(Set,c2);
				if ( c1 == c2 ){
					printf("yes\n");
				}else{
					printf("no\n");
				}
			}
		}else{
			int cnt = 0;
			for(i=1;i<=N;i++){
				if ( Set[i] < 0 ) cnt++;
			}
			if ( cnt == 1 ) printf("The network is connected.\n");
			else if ( cnt != 1 ) printf( "There are %d components.\n",cnt);
		}
		
	}
	return 0;
}

int Max( int Set[], int c1, int c2 )
{
	if ( Set[c1] <= Set[c2] ){
		return c1;
	}else {
		return c2;
	}
}

int Min( int Set[], int c1, int c2 )
{
	if ( Set[c1] >= Set[c2] ){
		return c1;
	}else {
		return c2;
	}
}

int Find( int Set[], int i )
{
	if( Set[i] < 0 ){
		return i;
	}else{
		return Set[i] = Find( Set, Set[i]) ;
	}
}
