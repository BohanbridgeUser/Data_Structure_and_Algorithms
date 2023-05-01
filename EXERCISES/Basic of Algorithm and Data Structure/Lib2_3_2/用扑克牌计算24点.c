/*
	4个数，4种运算符 对4个数进行排列，A44 = 24种情况
	4的3次方 ，共24*64种 
	第一个想法，穷举，不断循环试探，显然有些笨，但是书上这么解的。
	第二个想法，递归考虑，首先终值为24，写一个函数，这个函数的功能是
	判断剩下的数字可否通过加减乘除得到输入值，递归调用这个函数（似乎是一样的）
	1.生成24种数字排列
	2.生成64种符号排列
	3.依次选取数字排列和符号排列，按可能的运算顺序计算 :1 2 3, 1 3 2, 2 1 3, 2 3 1 , 3 2 1
*/ 


#include<stdio.h>

#define MAXDIG 24
#define MAXOPT 64

double Func( double a, double b, char c );

int main(int agc,const char* agv[])
{
	//input 
	double N[4]={0};
	char Opt[4]={'+','-','*','/'}; 
	int i;
	for(i=0;i<4;i++) scanf(" %lf",&N[i]);
	//
	
	//generate combination and permutation
	double Com[MAXDIG][4]={0};
	int row=0;
	for(i=0;i<4;i++){
		int j;
		for(j=0;j<4;j++){
			if ( j == i ) continue;
			else {
				int k;
				for(k=0;k<4;k++){
					if ( k == j || k == i ) continue;
					else {
						int l;
						for(l=0;l<4;l++){
							if ( l == i || l == j || l == k ) continue;
							else {
								Com[row][0] = N[i];
								Com[row][1] = N[j];
								Com[row][2] = N[k];
								Com[row][3] = N[l];
								row++;
							}
						}
					}
				}
			}
		}
	}
	
	char ComOpt[MAXOPT][3];
	row = 0;
	for(i=0;i<4;i++){
		int j;
		for(j=0;j<4;j++){
			int k;
			for(k=0;k<4;k++){
				ComOpt[row][0] = Opt[i];
				ComOpt[row][1] = Opt[j];
				ComOpt[row][2] = Opt[k];
				row++;
			}
		}
	}
	//
	
	//calculate
	int j,ctr=0,method=0;
	double value=0;
	for(i=0;i<24;i++){
		if ( ctr == 1 ) {
			i--;
			break;
		}
		for(j=0;j<64;j++) {
			// Com[i][all] ComOpt[j][all] 
				double mid1,mid2;
				mid1 = Func(Com[i][0],Com[i][1],ComOpt[j][0]);
				mid2 = Func(mid1,Com[i][2],ComOpt[j][1]);
				value = Func(mid2,Com[i][3],ComOpt[j][2]);
				if ( value == 24 ) {
					ctr = 1;
					method = 1;
					break;
				}
				
				mid1 = Func(Com[i][0],Com[i][1],ComOpt[j][0]);
				mid2 = Func(Com[i][2],Com[i][3],ComOpt[j][2]);
				value = Func(mid1,mid2,ComOpt[j][1]);
				if ( value == 24 ) {
					ctr = 1;
					method = 2;
					break;
				}
				
				mid1 = Func(Com[i][1],Com[i][2],ComOpt[j][1]);
				mid2 = Func(Com[i][0],mid1,ComOpt[j][0]);
				value = Func(mid2,Com[i][3],ComOpt[j][2]);
				if ( value == 24 ) {
					ctr = 1;
					method = 3;
					break;
				}	
				
				mid1 = Func(Com[i][1],Com[i][2],ComOpt[j][1]);
				mid2 = Func(mid1,Com[i][3],ComOpt[j][2]);
				value = Func(Com[i][0],mid2,ComOpt[j][0]);
				if ( value == 24 ) {
					ctr = 1;
					method = 4;
					break;
				}	
				
				mid1 = Func(Com[i][2],Com[i][3],ComOpt[j][2]);
				mid2 = Func(Com[i][1],mid1,ComOpt[j][1]);
				value = Func(Com[i][0],mid2,ComOpt[j][0]);
				if ( value == 24 ) {
					ctr = 1;
					method = 5;
					break;
				}		
		}
	}
	//
	
	//Output
	if ( method == 1 ) printf("((%.0f%c%.0f)%c%.0f)%c%.0f",Com[i][0],ComOpt[j][0],Com[i][1],ComOpt[j][1],Com[i][2],ComOpt[j][2],Com[i][3]);
	else if ( method == 2 ) printf("(%.0f%c%.0f)%c(%.0f%c%.0f)",Com[i][0],ComOpt[j][0],Com[i][1],ComOpt[j][1],Com[i][2],ComOpt[j][2],Com[i][3]);
	else if ( method == 3 ) printf("(%.0f%c(%.0f%c%.0f))%c%.0f",Com[i][0],ComOpt[j][0],Com[i][1],ComOpt[j][1],Com[i][2],ComOpt[j][2],Com[i][3]);
	else if ( method == 4 ) printf("%.0f%c((%.0f%c%.0f)%c%.0f)",Com[i][0],ComOpt[j][0],Com[i][1],ComOpt[j][1],Com[i][2],ComOpt[j][2],Com[i][3]);
	else if ( method == 5 ) printf("%.0f%c(%.0f%c(%.0f%c%.0f))",Com[i][0],ComOpt[j][0],Com[i][1],ComOpt[j][1],Com[i][2],ComOpt[j][2],Com[i][3]);
	else printf("-1");
	//
	return 0;
}

double Func( double a, double b, char c )
{
	if ( b == 0 && c == '/') return 0; 
	double ret = 0;
	switch (c) {
		case '+': 
			ret = a + b;
			break;
		case '-':
			ret = a - b;
			break;
		case '*':
			ret = a * b;
			break;
		case '/':
			ret = a / b;
			break;
	}
	return ret;
}

