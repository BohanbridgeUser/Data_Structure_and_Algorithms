#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

typedef struct Input ElementofHash;
typedef struct RowNode* PtrToRow;
typedef struct FileNode* PtrToFile;
typedef struct HashNode* Cell;
typedef struct FileLNode* FileList;
typedef struct FileRNode* FileRow;
typedef struct HashT* HashTable;
typedef struct FileHeadNode* PtrToFileHeadNode;
struct FileHeadNode {
    char* File;
    FileRow RowHead;
    FileRow RowRear;
    int RowN;
    FileList FileHead;
};
struct FileLNode {
    Cell Word;
    FileList Next;
};
struct FileRNode {
    char* Row;
    FileRow Next;
};
struct Input{
    char* Word;
    int File;
    int Row;
};

struct HashNode {
    char* Word;
    PtrToRow RowH;
};
struct HashT {
    int TableSize;
    Cell* Cells;
};
struct RowNode {
    int Row;
    int File;
    PtrToRow Next;
};

HashTable CreateH(int TableSize)
{
    HashTable H = (HashTable)malloc(sizeof(struct HashT));
    H->TableSize = TableSize;
    H->Cells = (Cell*)malloc(H->TableSize * sizeof(Cell));
    for (int i = 0; i < H->TableSize; i++) H->Cells[i] = NULL;
    return H;
}
int HashValue(char* Word)
{
    int hash = 0;
    int len = strlen(Word);
    for (int i = 0; i < 3 && i < len; i++) {
        hash = (hash << 5) + (Word[i] - 'a');
    }
    return hash;
}
int FindH(HashTable H, ElementofHash X)
{
    int Pos = HashValue(X.Word);
    if (H->Cells[Pos] == NULL) {
        return Pos;
    }
    else {
        int NewPos, CurrentPos, CNum = 0;
        NewPos = CurrentPos = Pos;
        while (H->Cells[NewPos] != NULL && strcmp(H->Cells[NewPos]->Word, X.Word) != 0) {
            if (++CNum % 2) {
                NewPos = CurrentPos + (CNum + 1) * (CNum + 1) / 4;
                if (NewPos >= H->TableSize) NewPos %= H->TableSize;
            }
            else {
                NewPos = CurrentPos - (CNum * CNum) / 4;
                while (NewPos < 0) NewPos += H->TableSize;
            }
        }
        return NewPos;
    }
}
void InsertH(HashTable H, ElementofHash X, PtrToFileHeadNode* FileHead)
{
    int Pos = FindH(H, X);
    if (H->Cells[Pos] == NULL) {
        H->Cells[Pos] = (Cell)malloc(sizeof(struct HashNode));
        H->Cells[Pos]->Word = (char*)malloc((strlen(X.Word) + 1) * sizeof(char));
        H->Cells[Pos]->RowH = (PtrToRow)malloc(sizeof(struct RowNode));
        H->Cells[Pos]->RowH->Next = NULL;
        strncpy(H->Cells[Pos]->Word, X.Word, strlen(X.Word) + 1);
        PtrToRow NewRNode = (PtrToRow)malloc(sizeof(struct RowNode));
        NewRNode->Row = X.Row;
        NewRNode->File = X.File;
        NewRNode->Next = H->Cells[Pos]->RowH->Next;
        H->Cells[Pos]->RowH->Next = NewRNode;
        FileList NewFLNode = (FileList)malloc(sizeof(struct FileLNode));
        NewFLNode->Word = H->Cells[Pos];
        NewFLNode->Next = FileHead[X.File]->FileHead->Next;
        FileHead[X.File]->FileHead->Next = NewFLNode;
    }
    else {
        PtrToRow p = H->Cells[Pos]->RowH->Next;
        int crtf = 1, crtr = 1;
        while (p) {
            if (p->File == X.File) {
                crtf = 0;
                if (p->Row == X.Row) {
                    crtr = 0;
                    break;
                }
            }
            p = p->Next;
        }
        if (crtf == 1) {
            PtrToRow NewRNode = (PtrToRow)malloc(sizeof(struct RowNode));
            NewRNode->Row = X.Row;
            NewRNode->File = X.File;
            NewRNode->Next = H->Cells[Pos]->RowH->Next;
            H->Cells[Pos]->RowH->Next = NewRNode;
            FileList NewFLNode = (FileList)malloc(sizeof(struct FileLNode));
            NewFLNode->Word = H->Cells[Pos];
            NewFLNode->Next = FileHead[X.File]->FileHead->Next;
            FileHead[X.File]->FileHead->Next = NewFLNode;
        }
        else {
            if (crtr == 1) {
                PtrToRow NewRNode = (PtrToRow)malloc(sizeof(struct RowNode));
                NewRNode->Row = X.Row;
                NewRNode->File = X.File;
                NewRNode->Next = H->Cells[Pos]->RowH->Next;
                H->Cells[Pos]->RowH->Next = NewRNode;
            }
        }
    }
}
char* InputRow(int N)
{
    char* Input = (char*)malloc(N * sizeof(char));
    memset(Input, '\0', N);
    char c;
    int j = 0;
    while ((c = getchar()) != '\n') {
        Input[j++] = c;
    }
    return Input;
}
int CtoI(char c)
{
    if (c >= 'A' && c <= 'Z') return 1;
    else if (c >= 'a' && c <= 'z') return 2;
    else return 3;
}

int* CreateSet(int N)
{
    int* Set = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) Set[i] = -1;
    return Set;
}
int FindSet(int* Set, int X)
{
    int i = X;
    while (Set[i] >= 0) {
        i = Set[i];
    }
    if (i == X) return i;
    else {
        Set[X] = i;
        return i;
    }
}
void MergeSet(int* Set, int X, int Y)
{
    int i, j;
    i = FindSet(Set, X);
    j = FindSet(Set, Y);
    if (i < j) {
        Set[Y] = i;
        Set[i]--;
    }
    else {
        Set[X] = j;
        Set[j]--;
    }
}
int main()
{
    int N;
    scanf("%d\n", &N);
    HashTable H = CreateH(30007);
    PtrToFileHeadNode* FileHead = (PtrToFileHeadNode*)malloc(N * sizeof(PtrToFileHeadNode));
    for (int i = 0; i < N; i++) {
        FileHead[i] = (PtrToFileHeadNode)malloc(sizeof(struct FileHeadNode));
        FileHead[i]->File = (char*)malloc(4 * sizeof(char));
        FileHead[i]->RowN = 0;
        FileHead[i]->RowHead = (FileRow)malloc(sizeof(struct FileRNode));
        FileHead[i]->RowHead->Row = NULL;
        FileHead[i]->RowHead->Next = NULL;
        FileHead[i]->RowRear = FileHead[i]->RowHead;
        FileHead[i]->FileHead = (FileList)malloc(sizeof(struct FileLNode));
        FileHead[i]->FileHead->Next = NULL;
        char* file = FileHead[i]->File;
        memset(file, '\0', 4);
        scanf("%s\n", file);
        while (1) {
            char* Input = InputRow(51);
            //printf("Input = %s\n", Input);
            if (Input[0] == '#' && Input[1] == '\0') {
                free(Input);
                break;
            }
            else {
                FileHead[i]->RowN++;
                FileRow NewRNode = (FileRow)malloc(sizeof(struct FileRNode));
                NewRNode->Row = Input;
                NewRNode->Next = NULL;
                FileHead[i]->RowRear->Next = NewRNode;
                FileHead[i]->RowRear = NewRNode;
                int p = 0;
                if (Input[0] == '#') p++;
                while (Input[p] != '\0') {
                    char* word = (char*)malloc(11 * sizeof(char));
                    memset(word, '\0', 11);
                    char* q = word;
                    while (CtoI(Input[p]) < 3) {
                        if (CtoI(Input[p]) == 1) *(q++) = Input[p++] - 'A' + 'a';
                        else *(q++) = Input[p++];
                    }
                    ElementofHash X = { word, i, FileHead[i]->RowN };
                    InsertH(H, X, FileHead);
                    if (Input[p] != '\0') p++;
                    free(word);
                }
            }
        }
    }
    int M;
    scanf("%d\n", &M);
    for (int i = 0; i < M; i++) {
        char* find = (char*)malloc(121 * sizeof(char));
        memset(find, '\0', 121);
        find = InputRow(121);
        //printf("find = %s\n", find);
        int p = 0;
        
        int* count = (int*)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) count[i] = 0;
        int cntword = 0;
        while (find[p] != '\0') {
            char* findw = (char*)malloc(11 * sizeof(char));
            memset(findw, '\0', 11);
            int q = 0;
            while (CtoI(find[p]) < 3) {
                if (CtoI(find[p]) == 1) findw[q++] = find[p++] - 'A' + 'a';
                else findw[q++] = find[p++];
            }
            findw[q] = '\0';
            //printf("%s\n", findw);
            cntword++;
            int pos = HashValue(findw);
            if (H->Cells[pos] != NULL) {
                PtrToRow p = H->Cells[pos]->RowH->Next;
                while (p) {
                    count[p->File]++;
                    p = p->Next;
                }
            }
            if(find[p] != '\0') p++;
            free(findw);
        }
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (count[i] >= cntword) cnt++;
        }
        if (cnt == 0) {
            printf("%d\nNot Found\n", cnt);
        }
        else {
            printf("%d\n", cnt);
            for (int j = 0; j < N; j++) {
                int* cRow = (int*)malloc(FileHead[j]->RowN *sizeof(int));
                for (int k = 0; k < FileHead[j]->RowN; k++) cRow[k] = 0;
                if (count[j] >= cntword) {
                    printf("%s\n", FileHead[j]->File);
                    p = 0;
                    while (find[p] != '\0') {
                        char* findw = (char*)malloc(11 * sizeof(char));
                        memset(findw, '\0', 11);
                        int q = 0;
                        while (CtoI(find[p]) < 3) {
                            if (CtoI(find[p]) == 1) findw[q++] = find[p++] - 'A' + 'a';
                            else findw[q++] = find[p++];
                        }
                        findw[q] = '\0';
                        int pos = HashValue(findw);
                        if (H->Cells[pos] != NULL) {
                            PtrToRow q = H->Cells[pos]->RowH->Next;
                            while (q) {
                                if (q->File == j) {
                                    cRow[q->Row - 1] = 1;
                                }
                                q = q->Next;
                            }
                        }
                        if (find[p] != '\0') p++;
                        free(findw);
                    }
                    for (int k = 0; k < FileHead[j]->RowN; k++) {
                        if (cRow[k] == 1) {
                            int c = 0;
                            FileRow p = FileHead[j]->RowHead;
                            while (c <= k) { 
                                p = p->Next;
                                c++;
                            }
                            printf("%s\n", p->Row);
                        }
                    }
                }
                free(cRow);
            }
        }
        free(count);
        free(find);
    }
    return 0;
}
