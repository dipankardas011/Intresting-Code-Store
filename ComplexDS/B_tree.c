#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define M 3
#define Ml M/2

BTree *createNode(int);
int searchPosition(BTree *, int key);
void *displayBTree(BTree *);

typedef struct nodes{
    int keys[M+1];
    struct nodes *childrens[M+1];
    int availableKeys;
}BTree;

BTree* createNode(int x){
    BTree *temp = (BTree *)malloc(sizeof(BTree));
    assert(temp);

    temp->availableKeys = 1;
    for (int i = 0; i <= M;i++)
        temp->childrens[i] = NULL;

    temp->keys[1] = x;

    return temp;
}

int main(int argc, char **argv) {
    BTree *root = NULL;
    remove(argv[0]);
    return EXIT_SUCCESS;
}