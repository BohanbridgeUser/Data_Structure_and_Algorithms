#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

struct InputFile {
    char* Word;
    int File;
};
typedef struct InputFile ElementofHash;

typedef struct HashNode* PtrToHashNode;
struct HashNode {
    ElementofHash Data;
    int* Files;
    PtrToHashNode Next;
};
struct HashT {
    int TableSize;
    PtrToHashNode* Heads;
};
typedef struct HashT* HashTable;

HashTable CreateH(int TableSize)
{
    HashTable H = (HashTable)malloc(sizeof(struct HashT));
    H->TableSize = TableSize;
    H->Heads = (PtrToHashNode*)malloc(H->TableSize * sizeof(PtrToHashNode));
    for (int i = 0; i < H->TableSize; i++) {
        H->Heads[i] = (PtrToHashNode)malloc(sizeof(struct HashNode));
        H->Heads[i]->Next = NULL;
    }
    return H;
}
int Hash(ElementofHash X)
{
    int ret = 0;
    for (int i = 0; i < 3; i++) {
        ret = ret * 32 + (X.Word[i] - 'a');
    }
    return ret;
}
PtrToHashNode FindH(HashTable H, ElementofHash X)
{
    int Pos = Hash(X);
    PtrToHashNode p = H->Heads[Pos]->Next;
    while (p && strcmp(p->Data.Word, X.Word) != 0) p = p->Next;
    return p;
}
void InsertH(HashTable H, ElementofHash X, int N)
{
    PtrToHashNode p = FindH(H, X);
    if (!p) {
        int Pos = Hash(X);
        PtrToHashNode NewNode = (PtrToHashNode)malloc(sizeof(struct HashNode));
        NewNode->Data.Word = (char*)malloc(20 * sizeof(char));
        for (int i = 0; i < strlen(X.Word) + 1; i++) NewNode->Data.Word[i] = X.Word[i];
        NewNode->Data.File = X.File;
        NewNode->Files = (int*)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) NewNode->Files[i] = 0;
        NewNode->Files[X.File] = 1;
        NewNode->Next = H->Heads[Pos]->Next;
        H->Heads[Pos]->Next = NewNode;
    }
    else {
        p->Files[X.File] = 1;
    }
}
int atoi(char c)
{
    if (c >= 'a' && c <= 'z') return 1;
    else if (c >= 'A' && c <= 'Z') return 2;
    else return 3;
}
char* scan() {
    static char temp[11];
    static int Flag_br = 0;//何时结束标记 
    int i = 0;
    char c;
    while (1) //结束条件只有return  
    {
        c = getchar();
        switch (c)
        {
        case '#'://? 
            if (Flag_br == 1)
            {
                c = getchar();
                if (c == '\n') //如果回车了应该是真结束了 
                {
                    temp[0] = '#';
                    temp[1] = '\0';
                    return temp;//剩下的交给main函数去判断 
                }
            }
        default:
            switch (c)
            {
            case 'a'...'z':
                if (i < 10)
                    temp[i++] = c;
                break;
            case 'A'...'Z':
                if (i < 10)
                    temp[i++] = c - 'A' + 'a';
                break;

            default:
                if (c == '\n')Flag_br = 1;//下次再出现#就说明这次结束了 
                //else Flag_br=0;

                temp[i] = '\0';
                //控制小于10的在前面 
                if (i > 2) return temp;//读入了一个单词 
                else return NULL;

                //break;
            }
            // break;
        }
    }
}
int main()
{
    int N;
    scanf("%d\n", &N);
    HashTable H = CreateH(30000);
    for (int i = 0; i < N; i++) {
        ElementofHash* tmp = (ElementofHash*)malloc(sizeof(struct HashNode));
        tmp->File = i;
        while (1) {
            tmp->Word = scan();
            if (tmp->Word) {
                if (tmp->Word[0] == '#')
                    break;

                InsertH(H, *tmp, N);
            }
        }

        /*tmp->Word = (char*)malloc(11 * sizeof(char));
        for (int j = 0; j < 11; j++) tmp->Word[j] = '\0';
        char* p = tmp->Word;
        tmp->File = i;
        char c = '\0';
        int cnt = 0;
        while ((c = getchar()) != '#') {
            if (cnt < 10) {
                int flag = atoi(c);
                if (flag == 1) {
                    *(p++) = c;
                    cnt++;
                }
                else if (flag == 2) {
                    *(p++) = c -'A' + 'a';
                    cnt++;
                }
                else {
                    if (p == tmp->Word) continue;
                    else {
                        if (strlen(tmp->Word) >= 3) InsertH(H, *tmp, N);
                        for (int j = 0; j < 11; j++) tmp->Word[j] = '\0';
                        p = tmp->Word;
                        cnt = 0;
                    }
                }
            }
            else {
                if (strlen(tmp->Word) >= 3) InsertH(H, *tmp, N);
                for (int j = 0; j < 11; j++) tmp->Word[j] = '\0';
                p = tmp->Word;
                cnt = 0;
                while (atoi((c = getchar())) != 3);
            }
        }*/
    }
    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int f1, f2;
        scanf("%d %d", &f1, &f2);
        f1--;
        f2--;
        int total = 0;
        int common = 0;
        double per = 0;
        for (int j = 0; j < H->TableSize; j++) {
            PtrToHashNode p = H->Heads[j]->Next;
            while (p) {
                if (p->Files[f1] == 1 && p->Files[f2] == 1) {
                    common++;
                    total++;
                }
                else if ((p->Files[f1] == 1 && p->Files[f2] == 0) ||
                    (p->Files[f1] == 0 && p->Files[f2] == 1)) {
                    total++;
                }
                p = p->Next;
            }
        }
        per = 1.0 * common / total;
        printf("%.1lf%%\n", per * 100);
    }
    return 0;
}