#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

struct HotWord {
    char* Word;
    int Times;
    int LastI;
};
typedef struct HotWord ElementofHash;

typedef struct HashNode* PtrToHashNode;
struct HashNode {
    ElementofHash Data;
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
    H->Heads = (PtrToHashNode*)malloc(H->TableSize * (sizeof(struct HashNode)));
    for (int i = 0; i < H->TableSize; i++) {
        H->Heads[i] = (PtrToHashNode)malloc(sizeof(struct HashNode));
        H->Heads[i]->Next = NULL;
    }
    return H;
}
int Hash(ElementofHash X)
{
    int len = strlen(X.Word);
    int hashvalue = 0;
    for (int i = 0; i < len; i++) {
        if (X.Word[i] >= 'A' && X.Word[i] <= 'Z') hashvalue += X.Word[i] - 'A';
        else if (X.Word[i] >= 'a' && X.Word[i] <= 'z') hashvalue += X.Word[i] - 'a';
    }
    return hashvalue;
}
PtrToHashNode FindH(HashTable H, ElementofHash X)
{
    int Pos = Hash(X);
    PtrToHashNode p = H->Heads[Pos]->Next;
    while (p && strcmp(p->Data.Word, X.Word) != 0) p = p->Next;
    return p;
}
void InsertH(HashTable H, ElementofHash X)
{
    PtrToHashNode p = FindH(H, X);
    if (!p) {
        int Pos = Hash(X);
        PtrToHashNode NewNode = (PtrToHashNode)malloc(sizeof(struct HashNode));
        NewNode->Data = X;
        NewNode->Next = H->Heads[Pos]->Next;
        H->Heads[Pos]->Next = NewNode;
    }
    else if (p->Data.LastI != X.LastI) {
        p->Data.Times++;
        p->Data.LastI = X.LastI;
    }
}
char Atochar(char a)
{
    if (a >= 'A' && a <= 'Z') return a + 32;
    else if (a >= 'a' && a <= 'z') return a;
    else if (a >= '0' && a <= '9') return a;
    else if (a == '#') return a;
    else if (a == ' ') return -1;
    else return -2;
}
void FindHotWord(char tmp[], HashTable H, int j)
{
    int len = strlen(tmp), crt = 0;
    char* hotword = (char*)malloc(141 * sizeof(char));
    memset(hotword, '\0', len + 1);
    char* p = hotword;
    for (int i = 0; i < len + 1; i++) {
        char t = Atochar(tmp[i]); // Fillter char
        if (crt == 1 && t == '#') {
            ElementofHash* x = (ElementofHash*)malloc(sizeof(ElementofHash));
            x->Word = (char*)malloc(141 * sizeof(char));
            memset(x->Word, '\0', 141);
            for (int k = 0; k < strlen(hotword) + 1; k++) x->Word[k] = hotword[k];
            for (int k = 0; k < strlen(hotword) + 1; k++) {
                if (x->Word[k] != ' ') {
                    x->Word[k] -= 32;
                    break;
                }
            }
            x->Times = 1;
            x->LastI = j;
            InsertH(H, *x);
            free(x);
            memset(hotword, '\0', len + 1);
            p = hotword;
            crt = 0;
            continue;
        }

        if (crt == 1) {
            if (t == -1) *(p++) = ' ';
            else if(t == -2){
                if (*(p - 1) == ' ' || tmp[i+1] == '#') continue;
                else *(p++) = ' ';
            }
            else if (t == '#') {
                continue;
            }
            else {
                *(p++) = t;
            }
        }

        if (crt == 0 && t == '#')crt = 1;
    }
    free(hotword);
}
void FindmaxAndOut(HashTable H)
{
    ElementofHash* max = (ElementofHash*)malloc(sizeof(ElementofHash));
    int i;
    for (i=0; i < 100000; i++) {
        if (H->Heads[i]->Next != NULL) {
            *max = H->Heads[i]->Next->Data;
            break;
        }
    }
    int cnt = 0;
    for (i=0; i < 100000; i++) {
        PtrToHashNode p = H->Heads[i]->Next;
        while (p) {
            if ((*max).Times < p->Data.Times) *max = p->Data;
            else if ((*max).Times == p->Data.Times) {
                if (strncmp((*max).Word, p->Data.Word, 141) > 0) {
                    *max = p->Data;
                }
            }
            p = p->Next;
        }
    }
    for (i = 0; i < 100000; i++) {
        PtrToHashNode p = H->Heads[i]->Next;
        while (p) {
            if ((*max).Times == p->Data.Times) {
                cnt++;
            }
            p = p->Next;
        }
    }
    cnt--;
    printf("%s\n%d\n", (*max).Word, (*max).Times);
    if (cnt != 0)printf("And %d more ...\n", cnt);
}
int main()
{
    int N;
    scanf("%d\n", &N);
    HashTable H = CreateH(100000);
    for (int i = 0; i < N; i++) {
        char* tmp = (char*)malloc(141 * sizeof(char));
        memset(tmp, '\0', sizeof(tmp));
        scanf("%[^\n]", tmp);
        getchar();
 
        FindHotWord(tmp, H, i);
    }
    FindmaxAndOut(H);
    return 0;
}