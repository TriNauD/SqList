#include <stdio.h>
#include <stdlib.h>

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
void initList(struct SqList *L) {
    L->elem = (char *) malloc(LIST_INIT_SIZE * sizeof(char));
    if (!L->elem) {
        printf("分配存储空间时错误");
    }
    L->length = 0;
    L->size = LIST_INIT_SIZE;
}

/**
 * @brief:在线性表第i位（1<=i<=length+1）前插入元素e
 * @param:SqList *L,int i,char e
 * @return:None
 * */
void insertElem(struct SqList *L, int i, char e) {
    if (i < 1 || i > L->length + 1) {
        printf("插入序号不合法");
    }
    /*如果存储空间不够用，则分配新的空间*/
    if (L->length >= L->size) {
        char *newBase = (char *) realloc(L->elem, (L->size + LIST_INCREMENT) * sizeof(char));
        if (!newBase) {
            printf("分配新的存储空间时错误");
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
 * @brief:在顺序表第i位（1<=i<=length+1）前插入元素e
 * @param:SqList *L,int i,char e
 * @return:None
 * */
void deleteElem(struct SqList *L, int i, char *e) {
    if (i < 1 || i > L->length + 1) {
        printf("删除序号不合法");
    }
    /*p指向被删除元素位置*/
    char *p = &(L->elem[i - 1]);
    /*e保存删除的元素*/
    e = *p;
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
void printList(struct SqList L) {
    for (int i = 0; i < L.length; ++i) {
        printf("%d\t", L.elem[i]);
    }
}

int main() {
    struct SqList L;
    int e;
    initList(&L);
    insertElem(&L, 1, 5);
    insertElem(&L, 2, 3);
    deleteElem(&L, 1, &e);
    printList(L);
    return 0;
}

