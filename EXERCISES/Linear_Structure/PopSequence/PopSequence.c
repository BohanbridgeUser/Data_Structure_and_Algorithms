/* 是否需要建立堆栈？能否直接根据相对关系判断？
	1.尝试直接根据相对关系判断
	  （1）pop出来的数后面一个数若小于pop则一定不能小于pop-1
	  （3）堆栈的总量限制了输出的数最早输出的位置一定不能早于pop-M+1
	  失败，无法规律难以总结
	2.虽然失败，但是发现每一个数是否可能与当前总数相关，尝试递归。
		例如，当前总数为7，这个数字不能是7和6
		已输出3，剩余 1 2 4 5 6 7 ，但是上一个数3又决定了下一个不能是1 
		思路又有问题
	3.新思路，当输出第一个数字的时候，确定了堆栈里一定会有哪些数字，例如第一个输出3，则堆栈一定是
	  1和2，下一个数字只能在5、4和2中输出，因为堆栈容量为5，可根据此思路尝试。
	   （1）下一个数字不能大于（M-In+LastN)并且小于LastN-1; 
	   （2）下一个数字输出后确定堆栈里的剩余数字 例如输出6，则堆栈中有1、2、4、5，剩下一个位置 若是输出2，则剩下4个位置 
*/ 

#include<stdio.h>

int Check( int Num[], int LastN, int Stack[], int M, int N, int LastPush );

int main( int agc, const char* agv[] )
{
	int M,N,K;
	scanf("%d %d %d",&M,&N,&K);
	
	int i;
	for(i=0;i<K;i++){
		int Num[N], Stack[M];
		int x;
		for(x=0;x<M;x++) Stack[x] = 0;
		int j;
		for(j=0;j<N;j++) scanf(" %d",&Num[j]);
		if ( Num[0] > M ) printf("NO\n");
		else {
			int k;
			for(k=0;k<Num[0]-1;k++) Stack[k] = k + 1;
			int LastPush = k + 1;
			if ( Check( Num, Num[0], Stack, M, N, LastPush ) == 1 ) printf("YES\n");
		} 
	} 
	return 0;
}

int Check( int Num[], int LastN, int Stack[], int M, int N, int LastPush )
{
	int i=0,ret;
	while ( Num[i++] != LastN );
	if (i == N) return 1;
	int k=0;
	while ( Stack[k] != 0 ) k++;
	int In = k;
	if ( Num[i] < Stack[k-1] ) {
		printf("NO\n", Num[i]);
		ret = -1;
	}else if ( Num[i] - LastPush > M - In ) {
		printf("NO\n",Num[i]);
		ret = -1;
	}else {
		if ( Num[i] == Stack[k-1] ) {
			Stack[k-1] = 0;
		} else {
			int x;
			for(x=LastPush+1;x<Num[i];x++,k++) Stack[k] = x;
			LastPush = x;
		} 
		ret = Check ( Num, Num[i], Stack, M, N, LastPush );
	}
	return ret;	
}
