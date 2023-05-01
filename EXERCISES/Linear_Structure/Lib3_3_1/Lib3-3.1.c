#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef double ElementType;
typedef struct SNode* Stack;
struct SNode{
	ElementType* Data;
	int Size;
	int Top;
};

Stack CreateS()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType*)malloc(1000*sizeof(ElementType));
	S->Top = -1;
	S->Size = 1000;
	return S;
}
bool IsFullS( Stack S )
{
	if ( S->Top + 1 == S->Size ) return true;
	else return false;
}
void Push( Stack S, ElementType X )
{
	if ( !IsFullS( S ) ){
		S->Data[++S->Top] = X;
	}
}
bool IsEmptyS( Stack S )
{
	if ( S->Top == -1 )return true;
	else return false;
}
ElementType Pop( Stack S )
{
	ElementType RET;
	if ( !IsEmptyS(S) ) {
		RET = S->Data[S->Top--];
	}else{
		RET = -1;
	}
	return RET;
}

/* Input2Int*/
double C2I( char* figure )
{
	char* i = strchr(figure,'\0') - 1;
	double RET = 0, F = 1;
	char* j;
	if( strchr(figure,'.') ){
		j = strchr(figure,'.');
		if( figure[0] == '-' ){
			char* k;
			for(k=j+1;k<=i;k++){
				F *= 0.1;
				RET += ( *k - 48 ) * F;
			}
			F = 1;
			for(k=j-1;k>figure;k--){
				RET += ( *k - 48 ) * F;
				F *= 10;
			}
			return -RET;
		}else if ( figure[0] == '+' ){
			char* k;
			for(k=j+1;k<=i;k++){
				F *= 0.1;
				RET += ( *k - 48 ) * F;
			}
			F = 1;
			for(k=j-1;k>figure;k--){
				RET += ( *k - 48 ) * F;
				F *= 10;
			}
			return +RET;
		}else{
			char* k;
			for(k=j+1;k<=i;k++){
				F *= 0.1;
				RET += ( *k - 48 ) * F;
			}
			F = 1;
			for(k=j-1;k>figure;k--){
				RET += ( *k - 48 ) * F;
				F *= 10;
			}
			return RET;
		}	
	}else{
		if( figure[0] == '-' ){
			for(;i>figure;i--){
				RET += ( *i - 48 ) * F;
				F *= 10;
			}
			return -RET;
		}else if ( figure[0] == '+' ){
			for(;i>figure;i--){
				RET += ( *i - 48 ) * F;
				F *= 10;
			}
			return +RET;
		}else{
			for(;i>=figure;i--){
				RET += ( *i - 48 ) * F;
				F *= 10;
			}
			return RET;
		}	
	}	
}
double S2I( char* Input, int* Beg, int* End )
{
	while( Input[*End] != ' ' && *End >= 0 ) (*End)--;
	char* figure = (char*)malloc(30*sizeof(char));
	int i,j;
	for(i=*End+1,j=0;i<=*Beg;i++,j++){
		figure[j] = Input[i];
	}
	
	double RET = 0;
	if( strlen(figure) <= 1 ){
		char character = figure[0];
		switch (character){
			case '+':
				RET = -1;
				break;
			case '-':
				RET = -2;
				break;
			case '*':
				RET = -3;
				break;
			case '/':
				RET = -4;
				break;
			default:
				RET = character - 48;
				break;
		}
	}else{
		RET = C2I( figure );
	}
	
	
	if ( *End == -1 ) return RET;
	else{
		*Beg = *End - 1;
		*End = *Beg;
		return RET;	
	}
}
/* End Input */

int main(int agc,const char* agv[])
{
	char* Input = (char*)malloc(100*sizeof(char));
	scanf("%[^\n]",Input);
	int LenS = strlen(Input);
	int Beg = LenS - 1, End = Beg;
	Stack S = CreateS();
	while( End != -1 ){
		double TMP,a,b;
		double character = S2I( Input, &Beg, &End );
		int c = (int)character;
		switch ( c ){
			case -1:
				a = Pop(S);
				if ( !IsEmptyS(S) ){
					b = Pop(S);
					TMP = a + b;
					Push( S, TMP );
					break;
				}else{
					Push( S, a );
					break;
				}	
			case -2:
				a = Pop(S), b = Pop(S);
				TMP = a - b;
				Push( S, TMP );
				break; 
			case -3:
				a = Pop(S), b = Pop(S);
				TMP = a * b;
				Push( S, TMP );
				break;
			case -4:
				a = Pop(S), b = Pop(S);
				if( b == 0 ) {
					printf("ERROR\n");
					return 0;
				}else{
					Push( S, a / b );
					break;
				}
			default:
				Push( S, character );
				break;
		}
	}
	printf("%.1lf\n",Pop(S));
	return 0;
}

