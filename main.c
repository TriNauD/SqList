#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIST_INIT_SIZE 100      /*线性表初始化的大小*/
#define LIST_INCREMENT 10       /*线性表增量，每次加LIST_INCREMENT个元素的空间*/

struct SqList {
    char *elem;     /*存储空间基址*/
    int length;     /*当前长度*/
    int size;       /*当前分配的存储容量*/
};

/**
 * @brief:初始化线性表
 * @param:SqList* L
 * @return：None
 */
void InitList(struct SqList *L) {
    L->elem = (char *) malloc(LIST_INIT_SIZE * sizeof(char));
    if (!L->elem) {
        printf("分配存储空间时错误\n");
    }
    L->length = 0;
    L->size = LIST_INIT_SIZE;
}

/**
 * @brief:销毁一个已经存在的顺序表
 * @param:Sqlist *L
 * @return:None
 * */
void DestroyList(struct SqList *L) {
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->size = 0;
}

/**
 * @brief:清空顺序表
 * @param：Sqlist *L
 * @return:None
 * */
void ClearList(struct SqList *L) {
    L->length = 0;
}

/**
 * @brief:判断顺序表是否空
 * @param：SqList L
 * @return:true/false
 * */
bool IsListEmpty(struct SqList L) {
    if (L.length == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief:得到顺序表长度
 * @param:SqList L
 * @return:L.length
 * */
int GetListLength(struct SqList L) {
    return (L.length);
}

/**
 * @brief:在线性表第i位（1<=i<=length+1）前插入元素e
 * @param:SqList *L,int i,char e
 * @return:None
 * */
void InsertElem(struct SqList *L, int i, char e) {
    if (i < 1 || i > L->length + 1) {
        printf("插入序号%d不合法\n", i);
        return;
    }
    /*如果存储空间不够用，则分配新的空间*/
    if (L->length >= L->size) {
        char *newBase = (char *) realloc(L->elem, (L->size + LIST_INCREMENT) * sizeof(char));
        if (!newBase) {
            printf("分配新的存储空间时错误\n");
        }
    }
    /*插入位置*/
    char *q = &(L->elem[i - 1]);
    /*从表最后一位向前直到插入位置，每一位往后移动一位*/
    for (char *p = &(L->elem[L->length - 1]); p >= q; p--) {
        *(p + 1) = *(p);
    }
    *q = e;
    L->length++;
}

/**
 * @brief:删除顺序表中第i位序的元素，并把它保存到e中
 * @param:SqList *L,int i,char *e
 * @return:None
 * */
void DeleteElem(struct SqList *L, int i, char *e) {
    if (i < 1 || i > L->length + 1) {
        printf("删除序号%c不合法\n", i);
        return;
    }
    /*p指向被删除元素位置*/
    char *p = &(L->elem[i - 1]);
    /*e保存删除的元素*/
    *e = *p;
    /*从被删除的那一位开始直到倒数第二个，每一位都等于后一位*/
    for (p; p < &(L->elem[L->length - 1]); p++) {
        *p = *(p + 1);
    }
    L->length--;
}

/**
 * @brief:打印一个顺序表
 * @param:SqList L
 * @return:None
 * */
void PrintList(struct SqList L) {
    for (int i = 0; i < L.length; ++i) {
        printf("%c\t", L.elem[i]);
    }
    printf("\n");
}

/**
 * @brief:在L中找到元素e的位序
 * @param:SqList L,char e
 * @return:int i(e的位序)/-1(没有找到)
 * */
int LocateElem(struct SqList L, char e) {
    for (int i = 0; i < L.length; ++i) {
        if (e == L.elem[i]) {
            return (i + 1);
        }
    }
    return -1;
}

/**
 * @brief:得到顺序表中第i位序的元素，保存在e中
 * @param:SqList L, int i, char *e
 * return:None
 * */
void GetElem(struct SqList L, int i, char *e) {
    if (i < 1 || i > L.length + 1) {
        printf("输入序号不合法\n");
        return;
    }
    *e = (L.elem[i - 1]);
}


int main() {
    struct SqList L;
    int i;              /*locate到的位序*/
    char e1, e2;        /*保存删除的元素*/
    InitList(&L);
    InsertElem(&L, 1, 'a');
    InsertElem(&L, 2, 'b');
    InsertElem(&L, 3, 'c');
    InsertElem(&L, 4, 'd');
    PrintList(L);
    i = LocateElem(L, 'c');
    DeleteElem(&L, 3, &e1);
    PrintList(L);
    GetElem(L, 2, &e2);
    printf("locate到的位序是：%d\n", i);
    printf("delete的元素是: %c\n", e1);
    printf("get到的元素是: %c\n", e2);
    return 0;
}

