//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//
//using namespace std;
//
//int Compare(const void* a, const void* b)
//{
//    return *(int*)a - *(int*)b;
//}
//int FindAncestor(int* preorder, int* midorder, int M,int rootp, int pl, int pr, int ml, int mr, int a, int b, int* pa, int* pb)
//{
//    int lbp, lep, rbp, rep, rootm, lbm, lem, rbm, rem;
//    int* p = (int*)bsearch(&preorder[rootp], midorder, M, sizeof(int), Compare);
//    rootm = p - midorder;
//    lbp = pl + 1, lep = pl + rootm - ml, rbp = lep + 1, rep = pr;
//    lbm = ml, lem = rootm - 1, rbm = rootm + 1, rem = mr;
//    if (pa == NULL && pb == NULL) {
//        printf("ERROR: %d and %d are not found.\n",a,b);
//        return -1;
//    }
//    else if (pa == NULL && pb != NULL) {
//        printf("ERROR: %d is not found.\n", a);
//        return -1;
//    }
//    else if (pa != NULL && pb == NULL) {
//        printf("ERROR: %d is not found.\n", b);
//        return -1;
//    }
//    else {
//        int loca = pa - midorder, locb = pb - midorder;
//        if (loca == rootm) {
//            printf("%d is an ancestor of %d.\n", a, b);
//            return -1;
//        }
//        else if (locb == rootm) {
//            printf("%d is an ancestor of %d.\n", b, a);
//            return -1;
//        }
//        if (loca >= lbm && loca <= lem && locb >= lbm && locb <= lem) {
//            return FindAncestor(preorder, midorder, M, lbp, lbp, lep, lbm, lem, a, b, pa, pb);
//        }
//        else if (loca >= lbm && loca <= lem && (locb < lbm || locb >lem)) {
//            return rootp;
//        }
//        else if ((loca < lbm || loca > lem) && locb >= lbm && loca <= lem) {
//            return rootp;
//        }
//        else if (loca >= rbm && loca <= rem && locb >= rbm && locb <= rem) {
//            return FindAncestor(preorder, midorder, M, rbp, rbp, rep, rbm, rem, a, b, pa, pb);
//        }
//        else if (loca >= rbm && loca <= rem && (locb < rbm || locb > rem)) {
//            return rootp;
//        }
//        else if ((loca < rbm || loca > rem) && locb >= rbm && locb <= rem) {
//            return rootp;
//        }
//    }
//    return 0;
//}
//int main()
//{
//    int N, M;
//    scanf("%d %d\n", &N, &M);
//    int* preorder = new int[M];
//    int* midorder = new int[M];
//    for (int i = 0; i < M; i++) {
//        scanf("%d", &preorder[i]);
//        midorder[i] = preorder[i];
//    }
//    qsort(midorder, M, sizeof(int), Compare);
//    for (int i = 0; i < N; i++) {
//        int a, b;
//        scanf("%d %d", &a, &b);
//        int* pa = (int*)bsearch(&a, midorder, M, sizeof(int), Compare);
//        int* pb = (int*)bsearch(&b, midorder, M, sizeof(int), Compare);
//        int ret = FindAncestor(preorder, midorder, M, 0, 0, M - 1, 0, M - 1, a, b, pa, pb);
//        if (ret > -1) {
//            printf("LCA of %d and %d is %d.\n", a, b, preorder[ret]);
//        }
//    }
//    return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int Compare(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

typedef int ElementofBinTree;
typedef struct TNode* PtrToTNode;
struct TNode {
	ElementofBinTree Data;
	PtrToTNode Left;
	PtrToTNode Right;
};
typedef PtrToTNode BinTree;

BinTree CreateT(int* preorder, int* inorder, int M, int lp, int rp, int lm, int rm) 
{
	if (lp > rp || lm > rm) return NULL;
	else {
		BinTree T = new struct TNode;
		int rootp = lp;
		int* p = (int*)bsearch(&preorder[rootp], inorder, M, sizeof(int), Compare);
		int rootm = p - inorder;
		int lbp = lp + 1, lep = lp + (rootm - lm), rbp = lep + 1, rep = rp;
		int lbm = lm, lem = rootm - 1, rbm = rootm + 1, rem = rm;
		T->Data = preorder[rootp];
		T->Left = CreateT(preorder, inorder, M, lbp, lep, lbm, lem);
		T->Right = CreateT(preorder, inorder, M, rbp, rep, rbm, rem);
		return T;
	}
}
void InorderTraversal(BinTree T)
{
	if (T) {
		InorderTraversal(T->Left);
		printf("%d\n", T->Data);
		InorderTraversal(T->Right);
	}
}
int AncestorCheck(BinTree T, int a, int b)
{
	if (T->Data > a && T->Data > b) {
		return AncestorCheck(T->Left, a, b);
	}
	else if (T->Data < a && T->Data < b) {
		return AncestorCheck(T->Right, a, b);
	}
	else if(T->Data == a){
		return a;
	}
	else if (T->Data == b) {
		return b;
	}
	else {
		return T->Data;
	}
}
int main()
{
	int N, M;
	scanf("%d %d\n", &N, &M);
	int* preorder = new int[M];
	int* inorder = new int[M];
	for (int i = 0; i < M; i++) {
	    scanf("%d", &preorder[i]);
	    inorder[i] = preorder[i];
	}
	qsort(inorder, M, sizeof(int), Compare);
	BinTree T = CreateT(preorder, inorder, M, 0, M - 1, 0, M - 1);
	//InorderTraversal(T);
	for (int i = 0; i < N; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		int* pa = (int*)bsearch(&a, inorder, M, sizeof(int), Compare);
		int* pb = (int*)bsearch(&b, inorder, M, sizeof(int), Compare);
		if (pa == NULL && pb == NULL) printf("ERROR: %d and %d are not found.\n", a, b);
		else if (pa != NULL && pb == NULL) printf("ERROR: %d is not found.\n", b);
		else if (pa == NULL && pb != NULL) printf("ERROR: %d is not found.\n", a);
		else {
			int ret = AncestorCheck(T, a, b);
			if (ret == a) printf("%d is an ancestor of %d.\n", a, b);
			else if (ret == b) printf("%d is an ancestor of %d.\n", b, a);
			else printf("LCA of %d and %d is %d.\n", a, b, ret);
		}
	}
	return 0;
}