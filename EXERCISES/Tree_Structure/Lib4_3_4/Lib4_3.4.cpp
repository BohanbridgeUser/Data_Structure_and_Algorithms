#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct TNode* PtrToTNode;
struct TNode {
    int K1;
    int K2;
    int Left;
    int Right;
};

struct DTNode {
    PtrToTNode* Tree;
};
typedef struct DTNode* DTree;

PtrToTNode CreateNode()
{
    PtrToTNode NewNode = new TNode;
    cin >> NewNode->K1;
    cin >> NewNode->K2;
    cin >> NewNode->Left;
    cin >> NewNode->Right;
    return NewNode;
}
int JudgeK1(DTree Input, int root, int* max, int* min)
{
    int lmin, lmax, rmin, rmax, left_flag = 0, right_flag = 0;
    if (Input->Tree[root]->Left == -1 && Input->Tree[root]->Right == -1) {
        *max = *min = Input->Tree[root]->K1;
        return 1;
    }

    if ((Input->Tree[root]->Left != -1 && JudgeK1(Input,Input->Tree[root]->Left,&lmax,&lmin) && Input->Tree[root]->K1 > lmax)
         || Input->Tree[root]->Left == -1) {
        left_flag = 1;
    }
    if ((Input->Tree[root]->Right != -1 && JudgeK1(Input, Input->Tree[root]->Right, &rmax, &rmin) && Input->Tree[root]->K1 < rmin)
        || Input->Tree[root]->Right == -1) {
        right_flag = 1;
    }

    if (left_flag && right_flag) {
        if (Input->Tree[root]->Left != -1) {
            *min = lmin;
        }
        else {
            *min = Input->Tree[root]->K1;
        }
        if (Input->Tree[root]->Right != -1) {
            *max = rmax;
        }
        else {
            *max = Input->Tree[root]->K1;
        }
        return 1;
    }
    else {
        return 0;
    }
}
int Judge(DTree Input, int root, int* path, int nofp)
{
    path[nofp] = root;
    if (Input->Tree[root]->Left != -1 && Input->Tree[root]->Right != -1) {
        if (Input->Tree[root]->K1 > Input->Tree[Input->Tree[root]->Left]->K1 
            && Input->Tree[root]->K1 < Input->Tree[Input->Tree[root]->Right]->K1
            && Input->Tree[root]->K2 < Input->Tree[Input->Tree[root]->Left]->K2
            && Input->Tree[root]->K2 < Input->Tree[Input->Tree[root]->Right]->K2) {
            if (Judge(Input, Input->Tree[root]->Left,path,nofp+1) == 1 && Judge(Input, Input->Tree[root]->Right,path,nofp+1) == 1) return 1;
            else  return 0;
        }
        else {
            return 0;
        }
    }
    else if (Input->Tree[root]->Left != -1 && Input->Tree[root]->Right == -1) {
        if (Input->Tree[root]->K1 > Input->Tree[Input->Tree[root]->Left]->K1
            && Input->Tree[root]->K2 < Input->Tree[Input->Tree[root]->Left]->K2) {
            if (Judge(Input, Input->Tree[root]->Left,path,nofp+1) == 1) return 1;
            else return 0;
        }
        else {
            return 0;
        }
    }
    else if (Input->Tree[root]->Left == -1 && Input->Tree[root]->Right != -1) {
        if (Input->Tree[root]->K1 < Input->Tree[Input->Tree[root]->Right]->K1
            && Input->Tree[root]->K2 < Input->Tree[Input->Tree[root]->Right]->K2) {
            if (Judge(Input, Input->Tree[root]->Right,path,nofp+1) == 1) return 1;
            else return 0;
        }
        else {
            return 0;
        }
    }
    else {
        return 1;
    }
}

int main()
{
    int N;
    cin >> N;

    DTree Input = new DTNode;
    Input->Tree = (PtrToTNode*)malloc(N*sizeof(struct TNode));
    int* cnt = new int[N];
    for (int i = 0; i < N; i++) cnt[i] = 0;
    for (int i = 0; i < N; i++) {
        Input->Tree[i] = CreateNode();
        if (Input->Tree[i]->Left > -1) cnt[Input->Tree[i]->Left] = 1;
        if (Input->Tree[i]->Right > -1) cnt[Input->Tree[i]->Right] = 1;
    }
    int root;
    for (int i = 0; i < N; i++) {
        if (cnt[i] == 0) {
            root = i;
            break;
        }
    }
    
    int* path = new int[N+10];
    int max = -1, min = -1;
    
    if (Judge(Input, root,path,0) == 1 && JudgeK1(Input,root,&max,&min) == 1) cout << "YES"<< endl;
    else cout << "NO" << endl;

    return 0;
}

