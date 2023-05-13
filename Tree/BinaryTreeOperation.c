#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT )/* ����������ɲ���ʵ�֣�ϸ�ڲ���? */
{
	if ( BT ){
		printf("%d ",BT->Data);
		PreorderTraversal( BT->Left );
		PreorderTraversal( BT->Right );
	}
}
void InorderTraversal( BinTree BT )  /* ����������ɲ���ʵ�֣�ϸ�ڲ���? */
{
	if ( BT ){
		PreorderTraversal( BT->Left );
		printf("%d ",BT->Data);
		PreorderTraversal( BT->Right );
	}
}

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
        printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

BinTree Insert( BinTree BST, ElementType X )
{
	if ( BST ){
		if ( X < BST->Data )  BST->Left = Insert( BST->Left, X );
		else if ( X > BST->Data ) BST->Right = Insert( BST->Right, X );
		return BST;
	}else{
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = NULL;
		BST->Right = NULL;
		return BST; 
	}
}
BinTree Delete( BinTree BST, ElementType X )
{
	Position TEMP;
	if ( BST ){
		if ( X < BST->Data ) BST->Left = Delete( BST->Left, X );
		else if ( X > BST->Data ) BST->Right = Delete( BST->Right, X );
		else{
			if ( !BST->Left && !BST->Right ){
				TEMP = BST;
				free(TEMP);
				BST = NULL;
			}else if ( !BST->Left && BST->Right ){
				TEMP = BST;
				BST = BST->Right;
				free(TEMP);
			}else if ( !BST->Right && BST->Left ){
				TEMP = BST;
				BST = BST->Left;
				free(TEMP);
			}else if ( BST->Left && BST->Right ){
				TEMP = FindMax( BST->Left );
				BST->Data = TEMP->Data;
				BST->Left = Delete( BST->Left, TEMP->Data);
			}	
		}
		return BST;
	}else{
		printf("Not Found\n");
		return NULL;
	}
}
Position Find( BinTree BST, ElementType X )
{
	if ( BST ){
		if( X < BST->Data ) return Find( BST->Left, X );
		else if ( X > BST->Data ) return Find ( BST->Right, X );
		else return BST;
	}
	return NULL;
}
Position FindMin( BinTree BST )
{
	if ( BST ) {
		if ( BST->Left ) return FindMin( BST->Left );
		else return BST;
	}else return NULL;
}
Position FindMax( BinTree BST )
{
	if ( BST ){
		if ( BST->Right ){
			return FindMax(BST->Right);
		}else{
			return BST;
		}
	}
	return NULL;
}

//BinTree Insert( BinTree BST, ElementType X )
//{
//	if(BST){
//		if( X < BST->Data ){
//			BST->Left = Insert( BST->Left , X );
//		}else if ( X > BST->Data ){
//			BST->Right = Insert( BST->Right, X );
//		}
//	}else{
//		BST = (BinTree)malloc(sizeof(struct TNode));
//		BST->Data = X;
//		BST->Left = NULL;
//		BST->Right = NULL;
//	}
//	return BST;
//}
//
//BinTree Delete( BinTree BST, ElementType X )
//{
//	Position Tmp;
//	if(!BST){
//		printf("Not Found\n");
//	}else{
//		if( X < BST->Data ){
//			BST->Left = Delete( BST->Left, X );
//		}else if ( X > BST->Data){
//			BST->Right = Delete( BST->Right, X );
//		}else{
//			if ( BST->Left && BST->Right ){
//				Tmp = FindMin( BST-> Right );
//				BST ->Data = Tmp->Data;
//				BST->Right = Delete( BST->Right, BST->Data );
//			}else{
//				Tmp = BST;
//				if ( !BST->Left ){
//					BST = BST->Right;
//				}else {
//					BST = BST->Left;
//				}
//				free(Tmp);
//			}
//		}
//	}
//	return BST;
//}
//
//Position Find( BinTree BST, ElementType X )
//{
//	Position RET;
//	if(BST){
//		if( BST->Data == X ){
//			RET = BST;
//		}else{
//			if( X < BST->Data ){
//				RET = Find( BST->Left, X );
//			}else{
//				RET = Find( BST->Right, X );
//			}
//		}
//	}else{
//		RET = NULL;
//	}
//	return RET;
//}
//
//Position FindMin( BinTree BST )
//{
//	Position RET;
//    if ( BST ){
//        if( BST->Left ){
//		RET = FindMin(BST->Left);
//        }else{
//            RET = BST;
//        }
//        return RET;
//    }else{
//        return NULL;
//    }
//}
//
//Position FindMax( BinTree BST )
//{
//	Position RET;
//    if (BST){
//        if( BST->Right ){
//            RET = FindMax(BST->Right);
//        }else{
//            RET = BST;
//        }
//        return RET;
//    }else{
//        return NULL;
//    }     
//}
