#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
#define OK 1
#define ERROR -1
#define OVERFLOW -2
#include<stdio.h>
typedef int ElemType;

typedef int Status;

typedef struct list
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

Status InitList(SqList *L)
{
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem)
        exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e){
    if (i < 1 || i >= L->length) exit(ERROR);
    if (L->length >= L->listsize) Relocal(&L);
    ElemType *cur = L + i-1;
    for (ElemType *p = L + L->length - 1; p >= cur; p--){
        *(p+1) = *p;
    }
    *cur = e;
    L->length ++;
    return OK;
}   

Status Relocal(SqList *L){
    if (L->length >= L->listsize){
        ElemType *newbase = (ElemType *)realloc(L->elem, (L->listsize + LIST_INCREMENT)*sizeof(ElemType));
        if (!newbase) exit(OVERFLOW);
        L->listsize += LIST_INCREMENT;
        return OK;
    }
}

Status ListDelete_Sq(SqList *L, int i, ElemType *e){
    if (i< 1 || i > L->length) return ERROR;
    ElemType *p = L->elem + i-1;
    ElemType *q = L->elem + L->length-1;
    for (++p;p<=q;++p){
        *(p-1) = *p;
    }
    L->length --;
    return OK;
}

Status Locate_Elem(SqList *L, ElemType e, Status (*compare)(ElemType, ElemType)){
    int i = 1;
    ElemType *p = L->elem;
    while( i <= L->length && !(*compare)(*p++, e)) i++;
    if (i<= L->length) return i;
    return 0;
}

Status compare(ElemType e1, ElemType e2){
    return e1 == e2;
}