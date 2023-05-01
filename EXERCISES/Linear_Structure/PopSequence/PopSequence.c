/* �Ƿ���Ҫ������ջ���ܷ�ֱ�Ӹ�����Թ�ϵ�жϣ�
	1.����ֱ�Ӹ�����Թ�ϵ�ж�
	  ��1��pop������������һ������С��pop��һ������С��pop-1
	  ��3����ջ����������������������������λ��һ����������pop-M+1
	  ʧ�ܣ��޷����������ܽ�
	2.��Ȼʧ�ܣ����Ƿ���ÿһ�����Ƿ�����뵱ǰ������أ����Եݹ顣
		���磬��ǰ����Ϊ7��������ֲ�����7��6
		�����3��ʣ�� 1 2 4 5 6 7 ��������һ����3�־�������һ��������1 
		˼·��������
	3.��˼·���������һ�����ֵ�ʱ��ȷ���˶�ջ��һ��������Щ���֣������һ�����3�����ջһ����
	  1��2����һ������ֻ����5��4��2���������Ϊ��ջ����Ϊ5���ɸ��ݴ�˼·���ԡ�
	   ��1����һ�����ֲ��ܴ��ڣ�M-In+LastN)����С��LastN-1; 
	   ��2����һ�����������ȷ����ջ���ʣ������ �������6�����ջ����1��2��4��5��ʣ��һ��λ�� �������2����ʣ��4��λ�� 
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
